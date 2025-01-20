#include "../include/feature_tree.hpp"

string trim(const string& str) {
    size_t start = str.find_first_not_of(TAB_LINE);
    size_t end = str.find_last_not_of(TAB_LINE);
    return (start == string::npos) ? EMPTY_STRING : str.substr(start, end - start + 1);
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
    for (auto it = begin; it != end; ++it) {
        features.push_back(it->str());
    }

    string result = EMPTY_STRING;
    for (int i = 0; i < features.size(); i++) {
        if (i == features.size() - 1)
            result += features[i];
        else
            result += features[i] + SPACE_STRING;
    }
    return result;
}

vector<string> make_apart(string line_of_file, char separator = SPACE)
{
    string file_element;
    vector<string> inputs;
    vector<string> result;
    istringstream line(line_of_file);
    while (getline(line, file_element, separator))
        inputs.push_back(file_element);
    for (int i = 0; i < inputs.size(); i++) {
        if (inputs[i] != EMPTY_STRING)
            result.push_back(inputs[i]);
    }
    return result;
}

vector<string> sort_config(vector<string>& strings, map<string, int> config_level) {
    vector<pair<string, int>> combined;
    for (const auto& str : strings) {
        combined.emplace_back(str, config_level[str]);
    }
    
    sort(combined.begin(), combined.end(), [](const pair<string, int>& a, const pair<string, int>& b) {
        return a.second < b.second;
    });
    
    for (size_t i = 0; i < strings.size(); ++i) {
        strings[i] = combined[i].first;
    }

    return strings;
}

FeatureTree::FeatureTree() {
    this->root = nullptr;
}

void FeatureTree::set_root(const shared_ptr<FeatureNode>& root_node) {
    this->root = root_node;
    root->set_parent(root);
    root->set_level(ZERO_LEVEL);
}

shared_ptr<FeatureNode> FeatureTree::get_root() {
    return root;
}

void FeatureTree::clear_all() {
    tree.clear();
    tree_inputs.clear();
    config_inputs.clear();
    nodes.clear();

    mandatoryNodes.clear();
    xorNodes_with_parent.clear();
    orNodes_with_parent.clear();

    config_level.clear();
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
    inputs = make_apart(norm, SPACE);
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
        inputs = make_apart(features, SPACE);
    }
}

void find_manadatory_and_optional_nodes(vector<string> &children, map<string, vector<string>>& my_map, vector< map<string, vector<string>>>& parent_child_list, vector< pair<string, char> >& node_names, vector<string> part_string) {
    children.clear();
    my_map.clear();
    for (int j = 1; j < part_string.size(); j++) {
        if (part_string[j] == MANDATORY_STRING or part_string[j] == EQUAL_STRING)
            continue;
        
        if (part_string[j].substr(START_OPTIONAL_INDEX, END_OPTIONAL_INDEX) == OPTIONAL_STRING) {
            node_names.push_back({part_string[j].substr(END_OPTIONAL_INDEX, part_string[j].size()), OPTIONAL});
            children.push_back(part_string[j].substr(END_OPTIONAL_INDEX, part_string[j].size()));
        }
        else {
            node_names.push_back({part_string[j], MANDATORY});
            children.push_back(part_string[j]);
        }
    }
    my_map[part_string[ROOT_INDEX]] = children;
    parent_child_list.push_back(my_map);
}

void find_xor_nodes(vector<string> &children, map<string, vector<string>>& my_map, vector< map<string, vector<string>>>& parent_child_list, vector< pair<string, char> >& node_names, vector<string> part_string) {
    children.clear();
    my_map.clear();
    for (int j = 1; j < part_string.size(); j++) {
        if (part_string[j] == XOR_STRING or part_string[j] == EQUAL_STRING)
            continue;
        node_names.push_back({part_string[j], XOR});
        children.push_back(part_string[j]);
    }
    my_map[part_string[ROOT_INDEX]] = children;
    parent_child_list.push_back(my_map);
}

void find_or_nodes(vector<string> &children, map<string, vector<string>>& my_map, vector< map<string, vector<string>>>& parent_child_list, vector< pair<string, char> >& node_names, vector<string> part_string) {
    children.clear();
    my_map.clear();
    for (int j = 1; j < part_string.size(); j++) {
        if (part_string[j] == OR_STRING or part_string[j] == EQUAL_STRING)
            continue;
        node_names.push_back({part_string[j], OR}); 

        children.push_back(part_string[j]);
    }
    my_map[part_string[ROOT_INDEX]] = children;
    parent_child_list.push_back(my_map);
}

void FeatureTree::make_feature_node(vector< pair<string, char> > node_names) {
    for (int i = 0; i < node_names.size(); i++) {
        shared_ptr<FeatureNode> node;
        if (node_names[i].second == MANDATORY) {
            node = make_shared<MandatoryNode>(node_names[i].first);

        }
        else if (node_names[i].second == OPTIONAL) {
            node = make_shared<OptionalNode>(node_names[i].first);
        }
        else if (node_names[i].second == OR) {
            node = make_shared<OrNode>(node_names[i].first);
        }
        else if (node_names[i].second == XOR) {
            node = make_shared<XorNode>(node_names[i].first);
        }
        tree.push_back(node);
        if (i == ROOT_INDEX)
            set_root(node);
    }
}

void FeatureTree::make_child_and_parent() {
    for (int i = 0; i < nodes.size(); i++) {
        for (const auto& entry : nodes[i]) {
            entry.first->set_children(entry.second);
            for (const auto& value: entry.second) {
                value->set_parent(entry.first);
            }
        }
    }
}

void FeatureTree::make_tree_nodes(vector< map<string, vector<string>> > parent_child_list) {
    for (int i = 0; i < parent_child_list.size(); i++) {
        map<shared_ptr<FeatureNode>, vector<shared_ptr<FeatureNode>>> my_map_node;
        vector<shared_ptr<FeatureNode>> children_node;
        for (const auto& entry : parent_child_list[i]) {
            shared_ptr<FeatureNode> temp;
            for (int j = 0; j < tree.size(); j++) {
                if (entry.first == tree[j]->get_name()) {
                    temp = tree[j];
                    break;
                }
            }

            for (const auto& value : entry.second) {
                for (int j = 0; j < tree.size(); j++){
                    if (value == tree[j]->get_name()) {
                        children_node.push_back(tree[j]);
                    }
                }
            }
            my_map_node[temp] = children_node;
            nodes.push_back(my_map_node);
        }
    }
}

void FeatureTree::set_level_nodes(vector< map<string, vector<string>> > parent_child_list) {
    config_level[root->get_name()] = 0;
    for (int i = 0; i < tree.size(); i++) {
        vector<shared_ptr<FeatureNode>> children = tree[i]->get_children();
        for (int j = 0; j < children.size(); j++) {
            if (children[j]->get_level() == -1) {
                int level = tree[i]->get_level() + 1;
                string children_name = children[j]->get_name();
                children[j]->set_level(level);
                config_level[children_name] = level;
            }
            else
                continue;
        }
    }
}

void FeatureTree::set_mandatory_nodes() {
    for (int i = 0; i < tree.size(); i++) {
        if (tree[i]->get_relation() == MANDATORY) {
            mandatoryNodes.push_back(tree[i]);
        }
    }
}

void FeatureTree::set_xor_nodes() {
    for (int i = 0; i < tree.size(); i++) {
        vector<shared_ptr<FeatureNode>> temp = tree[i]->get_children();
        for (const auto& child: temp) {
            if (child->get_relation() == XOR) {
                xorNodes_with_parent[tree[i]] = temp;
                break;
            }
        }
    }
}

void FeatureTree::set_or_nodes() {
    for (int i = 0; i < tree.size(); i++) {
        vector<shared_ptr<FeatureNode>> temp = tree[i]->get_children();
        for (const auto& child: temp) {
            if (child->get_relation() == OR) {
                this->orNodes_with_parent[tree[i]] = temp;
                break;
            }
        }
    }
}

void find_nodes_based_on_relation(string temp, vector<string> &children, map<string, vector<string>>& my_map, vector< map<string, vector<string>>>& parent_child_list, vector< pair<string, char> >& node_names, vector<string> part_string) {
    bool found = false;
    for (const auto& pair: operators) {
        int ind = temp.find(pair.second);
        if (temp[ind] == MANDATORY) {
            found = true;
            find_manadatory_and_optional_nodes(children, my_map, parent_child_list, node_names, part_string);
        }
        else if (temp[ind] == XOR){
            found = true;
            find_xor_nodes(children, my_map, parent_child_list, node_names, part_string);
        }
        else if (temp[ind] == OR) {
            found = true;
            find_or_nodes(children, my_map, parent_child_list, node_names, part_string);
        }
        if (found) {
            break;
        }
        
    }
    if (!found) {
        find_manadatory_and_optional_nodes(children, my_map, parent_child_list, node_names, part_string);
    }
}

void find_root(int num, vector<string> part_string, vector< pair<string, char>>& node_names) {
    if (num == ROOT_INDEX) {
        node_names.push_back({part_string[num], MANDATORY});
    }
}

void FeatureTree::built_tree() {
    vector< pair<string, char> > node_names;
    vector< map<string, vector<string>> > parent_child_list;
    map<string, vector<string>> my_map;
    vector<string> children;

    for (int i = 0; i < tree_inputs.size(); i++) {
        string temp = tree_inputs[i];
        vector<string> part_string = make_apart(temp);
        find_root(i, part_string, node_names);
        find_nodes_based_on_relation(temp, children, my_map, parent_child_list, node_names, part_string);
    }
    make_feature_node(node_names);
    make_tree_nodes(parent_child_list);
    make_child_and_parent();
    set_level_nodes(parent_child_list);
    set_xor_nodes();
    set_or_nodes();
    set_mandatory_nodes();
}

bool FeatureTree::check_xor(const vector<string>& selected_features) {
    for (const auto& pair: this->xorNodes_with_parent) {
        auto it = find(selected_features.begin(), selected_features.end(), pair.first->get_name());
        if (it != selected_features.end()) {
            int cnt = 0;
            for (const auto& child: pair.second) { 
                auto it = find(selected_features.begin(), selected_features.end(), child->get_name());
                if (it != selected_features.end()) {
                    cnt++;
                }
            }
            if (cnt > 1 || cnt == 0) {
                return 0;
            }
        }
    }
    return 1;
}

bool FeatureTree::check_or(const vector<string>& selected_features) {
    for (const auto& pair: this->orNodes_with_parent) {
        auto it = find(selected_features.begin(), selected_features.end(), pair.first->get_name());
        if (it != selected_features.end()) {
            int cnt = 0;
            for (const auto& child: pair.second) { 
                auto it = find(selected_features.begin(), selected_features.end(), child->get_name());
                if (it != selected_features.end()) {
                    cnt++;
                }
            }
            if (cnt == 0) {
                return 0;
            }
        }
    }
    return 1;
}

bool FeatureTree::check_mandatory(const vector<string>& selected_features) {
    for (const auto& m_node: mandatoryNodes) {
        auto it = find(selected_features.begin(), selected_features.end(), m_node->get_parent()->get_name());
        if (it != selected_features.end()) {
            auto it = find(selected_features.begin(), selected_features.end(), m_node->get_name());
            if (it != selected_features.end()) {
                continue;
            }
            else {
                return false;
            }
        }
    }
    return true;
}

bool FeatureTree::validate_configuration(const string& config) {
    vector<string> selected_features = make_apart(config, SPACE);
    selected_features = sort_config(selected_features, config_level);
    
    if (find(selected_features.begin(), selected_features.end(), root->get_name()) == selected_features.end()) {
        return false;
    }

    for (const auto& feature : selected_features) {
        shared_ptr<FeatureNode> selected_node = nullptr;
        for (const auto& node : tree) {
            if (node->get_name() == feature) {
                selected_node = node;
                break;
            }
        }
        if (!selected_node) {
            return false;
        }
        if (selected_node->get_name() == root->get_name()) {
            continue;
        }
        int ans = selected_node->validate_node(selected_features);
        if (ans) {
            continue;
        }
        else {

            return false;
        }
    }
    if (check_mandatory(selected_features) && check_xor(selected_features) && check_or(selected_features)) {
        return true;
    }
    else {
        return false;
    }
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