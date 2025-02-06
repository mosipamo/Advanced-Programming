#include "../include/feature_tree.hpp"

string trim(const string& str) {
    size_t start = str.find_first_not_of(WHITESPACE_CHARS);
    size_t end = str.find_last_not_of(WHITESPACE_CHARS);
    return (start == string::npos) ? "" : str.substr(start, end - start + 1);
}

string normalize_input(const string& line) {
    string result = line;
    result = regex_replace(result, regex(ADD_SPACES_AROUND_OPERATORS), SPACED_OPERATOR_REPLACEMENT);
    result = regex_replace(result, regex(REMOVE_SPACES_AFTER_QUESTION_MARK), QUESTION_MARK_WITH_WORD_REPLACEMENT);
    result = regex_replace(result, regex(CONSOLIDATE_WHITESPACE), CONSOLIDATED_SPACE_REPLACEMENT);
    result = trim(result);
    return result;
}

string extract_features(const string& config) {
    regex feature_regex(FEATURE_REGEX);
    sregex_iterator begin(config.begin(), config.end(), feature_regex);
    sregex_iterator end;

    vector<string> features;
    for (auto it = begin; it != end; it++) {
        features.push_back(it->str());
    }

    string result = "";
    for (int i = 0; i < features.size(); i++) {
        if (i == features.size() - 1)
            result += features[i];
        else
            result += features[i] + " ";
    }
    return result;
}

vector<string> make_apart(string line_of_file, char separator = ' ')
{
    string file_element;
    vector<string> inputs;
    vector<string> result;
    istringstream line(line_of_file);
    while (getline(line, file_element, separator))
        inputs.push_back(file_element);
    for (int i = 0; i < inputs.size(); i++) {
        if (inputs[i] != "")
            result.push_back(inputs[i]);
    }
    return result;
}

vector<string> sort_config(vector<string>& features, map<string, int> nodes_depth) {
    vector<pair<string, int>> combined;
    for (const auto& str : features) {
        combined.emplace_back(str, nodes_depth[str]);
    }
    
    sort(combined.begin(), combined.end(), [](const pair<string, int>& a, const pair<string, int>& b) {
        return a.second < b.second;
    });
    
    for (size_t i = 0; i < features.size(); i++) {
        features[i] = combined[i].first;
    }

    return features;
}

FeatureTree::FeatureTree() {
    this->root = nullptr;
}

void FeatureTree::set_root(const shared_ptr<FeatureNode>& root_node) {
    this->root = root_node;
    root->set_parent(root);
    root->set_level(ZERO_LEVEL);
}

void FeatureTree::handle_tree() {
    built_tree();
    validate_all_configurations();
    clear_all();
}

void FeatureTree::make_coffee_shop() {
    string line;
    while (getline(cin, line)) {
        if (line == END_TREE) {
            get_configurations();
        }
        else if (line == END_INPUT) {
            break;
        }
        else {
            get_feature_tree(line);
        }
    }
}

void FeatureTree::get_feature_tree(const string& line) {
    vector<string> inputs;
    string norm = normalize_input(line);
    inputs = make_apart(norm, ' ');
    tree_inputs.push_back(norm);
}

void FeatureTree::get_configurations() {
    string inp;
    vector<string> inputs;
    while (getline(cin, inp)) {
        if (inp == END_CONFIGURATION) {
            handle_tree();
            break;
        }
        string features = extract_features(inp);
        config_inputs.push_back(features);
        inputs = make_apart(features, ' ');
    }
}

void find_nodes(vector<string> &children, map<string, vector<string>> &map_parent_child, vector<map<string, vector<string>>> &parent_child_list, vector<pair<string, char>> &node_names_with_relation, vector<string> &part_string, char node_type) {
    children.clear();
    map_parent_child.clear();
    for (int i = 1; i < part_string.size(); i++) {
        if (part_string[i] == MANDATORY_STRING || part_string[i] == XOR_STRING || part_string[i] == OR_STRING || part_string[i] == EQUAL_STRING) {
            continue;
        }
        if (node_type == MANDATORY && part_string[i].substr(START_OPTIONAL_INDEX, END_OPTIONAL_INDEX) == OPTIONAL_STRING) {
            node_names_with_relation.push_back({part_string[i].substr(END_OPTIONAL_INDEX), OPTIONAL});
            children.push_back(part_string[i].substr(END_OPTIONAL_INDEX));
        } 
        else {
            node_names_with_relation.push_back({part_string[i], node_type});
            children.push_back(part_string[i]);
        }
    }
    map_parent_child[part_string[ROOT_INDEX]] = children;
    parent_child_list.push_back(map_parent_child);
}

void find_nodes_based_on_relation(string temp, vector<string> &children, map<string, vector<string>> &map_parent_child, vector<map<string, vector<string>>> &parent_child_list, vector<pair<string, char>> &node_names_with_relation, vector<string> part_string) {
    bool found = false;
    for (const auto &ops_num : operators) {
        int ind = temp.find(ops_num.second);
        if (ind != string::npos) {
            if (temp[ind] == MANDATORY) {
                find_nodes(children, map_parent_child, parent_child_list, node_names_with_relation, part_string, MANDATORY);
            } 
            else if (temp[ind] == XOR) {
                find_nodes(children, map_parent_child, parent_child_list, node_names_with_relation, part_string, XOR);
            } 
            else if (temp[ind] == OR) {
                find_nodes(children, map_parent_child, parent_child_list, node_names_with_relation, part_string, OR);
            }
            found = true;
            break;
        }
    }
    if (!found) {
        find_nodes(children, map_parent_child, parent_child_list, node_names_with_relation, part_string, MANDATORY);
    }
}

void find_root(int num, vector<string> part_string, vector< pair<string, char>>& node_names_with_relation) {
    if (num == ROOT_INDEX) {
        node_names_with_relation.push_back({part_string[num], MANDATORY});
    }
}

void FeatureTree::make_feature_nodes_types(vector< pair<string, char> > node_names_with_relation) {
    for (int i = 0; i < node_names_with_relation.size(); i++) {
        shared_ptr<FeatureNode> node;
        if (node_names_with_relation[i].second == MANDATORY) {
            node = make_shared<MandatoryNode>(node_names_with_relation[i].first);
        }
        else if (node_names_with_relation[i].second == OPTIONAL) {
            node = make_shared<OptionalNode>(node_names_with_relation[i].first);
        }
        else if (node_names_with_relation[i].second == OR) {
            node = make_shared<OrNode>(node_names_with_relation[i].first);
        }
        else if (node_names_with_relation[i].second == XOR) {
            node = make_shared<XorNode>(node_names_with_relation[i].first);
        }
        tree_nodes.push_back(node);
        if (i == ROOT_INDEX) {
            set_root(node);
        }
    }
}

void FeatureTree::make_tree_nodes(vector< map<string, vector<string>> > parent_child_list) {
    for (int i = 0; i < parent_child_list.size(); i++) {
        map<shared_ptr<FeatureNode>, vector<shared_ptr<FeatureNode>>> map_parent_child;
        vector<shared_ptr<FeatureNode>> children_node;
        for (const auto& parent_child_list : parent_child_list[i]) {
            shared_ptr<FeatureNode> temp;
            for (int j = 0; j < tree_nodes.size(); j++) {
                if (parent_child_list.first == tree_nodes[j]->get_name()) {
                    temp = tree_nodes[j];
                    break;
                }
            }

            for (const auto& child_node : parent_child_list.second) {
                for (int j = 0; j < tree_nodes.size(); j++){
                    if (child_node == tree_nodes[j]->get_name()) {
                        children_node.push_back(tree_nodes[j]);
                    }
                }
            }
            map_parent_child[temp] = children_node;
            node_with_parents.push_back(map_parent_child);
        }
    }
}

void FeatureTree::make_child_and_parent() {
    for (int i = 0; i < node_with_parents.size(); i++) {
        for (const auto& parent_child_list : node_with_parents[i]) {
            parent_child_list.first->set_children(parent_child_list.second);
            for (const auto& child_node: parent_child_list.second) {
                child_node->set_parent(parent_child_list.first);
            }
        }
    }
}

void FeatureTree::set_level_nodes(vector< map<string, vector<string>> > parent_child_list) {
    nodes_depth[root->get_name()] = 0;
    for (int i = 0; i < tree_nodes.size(); i++) {
        vector<shared_ptr<FeatureNode>> children = tree_nodes[i]->get_children();
        for (int j = 0; j < children.size(); j++) {
            if (children[j]->get_level() == -1) {
                int level = tree_nodes[i]->get_level() + 1;
                string children_name = children[j]->get_name();
                children[j]->set_level(level);
                nodes_depth[children_name] = level;
            }
            else {
                continue;
            }
        }
    }
}

void FeatureTree::set_nodes(char relation) {
    for (const auto& node : tree_nodes) {
        vector<shared_ptr<FeatureNode>> children = node->get_children();
        if (relation == MANDATORY && node->get_relation() == MANDATORY) {
            mandatory_nodes.push_back(node);
        } 
        else {
            for (const auto& child : children) {
                if (child->get_relation() == relation) {
                    if (relation == XOR) {
                        xor_nodes_with_parent[node] = children;
                    } 
                    else if (relation == OR) {
                        or_nodes_with_parent[node] = children;
                    }
                    break;
                }
            }
        }
    }
}

void FeatureTree::built_tree() {
    vector<pair<string, char>> node_names_with_relation;
    vector<map<string, vector<string>>> parent_child_list;
    map<string, vector<string>> map_parent_child;
    vector<string> children;

    for (int i = 0; i < tree_inputs.size(); i++) {
        string temp = tree_inputs[i];
        vector<string> part_string = make_apart(temp);
        find_root(i, part_string, node_names_with_relation);
        find_nodes_based_on_relation(temp, children, map_parent_child, parent_child_list, node_names_with_relation, part_string);
    }
    make_feature_nodes_types(node_names_with_relation);
    make_tree_nodes(parent_child_list);
    make_child_and_parent();
    set_level_nodes(parent_child_list);
    set_nodes(XOR);
    set_nodes(OR);
    set_nodes(MANDATORY);
}

bool FeatureTree::check_relation(const vector<string>& selected_features, const map<shared_ptr<FeatureNode>, vector<shared_ptr<FeatureNode>>>& nodes_with_parent, condition cond) {
    for (const auto& pair : nodes_with_parent) {
        auto it = find(selected_features.begin(), selected_features.end(), pair.first->get_name());
        if (it != selected_features.end()) {
            int num_of_children = 0;
            for (const auto& child : pair.second) {
                if (find(selected_features.begin(), selected_features.end(), child->get_name()) != selected_features.end()) {
                    num_of_children += 1;
                }
            }
            if (!cond(num_of_children)) {
                return false;
            }
        }
    }
    return true;
}

bool FeatureTree::check_mandatory(const vector<string>& selected_features) {
    for (const auto& m_node : mandatory_nodes) {
        auto it = find(selected_features.begin(), selected_features.end(), m_node->get_parent()->get_name());
        if (it != selected_features.end()) {
            if (find(selected_features.begin(), selected_features.end(), m_node->get_name()) == selected_features.end()) {
                return false;
            }
        }
    }
    return true;
}

bool FeatureTree::validate_configuration(const string& config) {
    vector<string> selected_features = make_apart(config, ' ');
    selected_features = sort_config(selected_features, nodes_depth);

    auto it = find(selected_features.begin(), selected_features.end(), root->get_name());
    if (it == selected_features.end()) {
        return false;
    }

    for (const auto& feature : selected_features) {
        shared_ptr<FeatureNode> selected_node = nullptr;
        for (const auto& node : tree_nodes) {
            if (node->get_name() == feature) {
                selected_node = node;
                break;
            }
        }
        if (!selected_node) { return false; }
        if (selected_node->get_name() == root->get_name()) { continue; }
        int ans = selected_node->validate_node(selected_features);
        if (ans) { continue; }
        else { return false; }
    }

    bool xor_valid = check_relation(selected_features, xor_nodes_with_parent, [](int count_children) { return count_children == 1; });
    bool or_valid = check_relation(selected_features, or_nodes_with_parent, [](int count_children) { return count_children > 0; });
    bool mandatory_valid = check_mandatory(selected_features);

    return xor_valid && or_valid && mandatory_valid;
}

void FeatureTree::validate_all_configurations() {
    for (const auto& config : config_inputs) {
        if (validate_configuration(config)) {
            cout << VALID << endl;
        } 
        else {
            cout << INVALID << endl;
        }
    }
    cout << DONE << endl;
}

void FeatureTree::clear_all() {
    tree_nodes.clear();
    tree_inputs.clear();
    config_inputs.clear();
    node_with_parents.clear();
    mandatory_nodes.clear();
    xor_nodes_with_parent.clear();
    or_nodes_with_parent.clear();
    nodes_depth.clear();
}