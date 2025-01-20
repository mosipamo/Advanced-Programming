#ifndef FEATURE_TREE_HPP
#define FEATURE_TREE_HPP

#include "../include/feature_node.hpp"
#include "../include/manual.hpp"

class FeatureTree {
private:
    shared_ptr<FeatureNode> root;
    vector<shared_ptr<FeatureNode>> tree;
    vector<string> tree_inputs;
    vector<string> config_inputs;
    map<string, int> config_level;
    vector<map<shared_ptr<FeatureNode>, vector<shared_ptr<FeatureNode>>>> nodes;
    vector<shared_ptr<FeatureNode>> mandatoryNodes;
    map<shared_ptr<FeatureNode>, vector<shared_ptr<FeatureNode>>> xorNodes_with_parent;
    map<shared_ptr<FeatureNode>, vector<shared_ptr<FeatureNode>>> orNodes_with_parent;

public:
    FeatureTree();
    void make_coffee_shop();
    void handle_tree();
    void get_feature_tree(const string& line);
    void get_configurations();
    void built_tree();
    void set_root(const shared_ptr<FeatureNode>& root_node);
    shared_ptr<FeatureNode> get_root();
    bool validate_configuration(const string& config);
    void validate_all_configurations();
    void clear_all();
    bool check_xor(const vector<string>& selected_features);
    bool check_or(const vector<string>& selected_features);
    bool check_mandatory(const vector<string>& selected_features);
    void make_feature_node(vector< pair<string, char> > node_names);
    void make_tree_nodes(vector< map<string, vector<string>> > parent_child_list);
    void make_child_and_parent();
    void set_level_nodes(vector< map<string, vector<string>> > parent_child_list);
    void set_xor_nodes();
    void set_or_nodes();
    void set_mandatory_nodes();
};

#endif