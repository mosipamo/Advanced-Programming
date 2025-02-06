#ifndef FEATURE_TREE_HPP
#define FEATURE_TREE_HPP

#include "../include/feature_node.hpp"
#include "../include/mandatory_node.hpp"
#include "../include/optional_node.hpp"
#include "../include/or_node.hpp"
#include "../include/xor_node.hpp"
#include "../include/manual.hpp"

class FeatureTree {
private:
    shared_ptr<FeatureNode> root;
    vector<shared_ptr<FeatureNode>> tree_nodes;
    vector<map<shared_ptr<FeatureNode>, vector<shared_ptr<FeatureNode>>>> node_with_parents;
    vector<string> tree_inputs;
    vector<string> config_inputs;
    map<string, int> nodes_depth;
    vector<shared_ptr<FeatureNode>> mandatory_nodes;
    map<shared_ptr<FeatureNode>, vector<shared_ptr<FeatureNode>>> xor_nodes_with_parent;
    map<shared_ptr<FeatureNode>, vector<shared_ptr<FeatureNode>>> or_nodes_with_parent;

public:
    FeatureTree();
    void make_coffee_shop();
    void get_feature_tree(const string& line);
    void get_configurations();
    void handle_tree();
    void built_tree();
    void set_root(const shared_ptr<FeatureNode>& root_node);
    void make_feature_nodes_types(vector<pair<string, char>> node_names_with_relation);
    void make_tree_nodes(vector<map<string, vector<string>>> parent_child_list);
    void set_nodes(char relation);
    void make_child_and_parent();
    void set_level_nodes(vector< map<string, vector<string>>> parent_child_list);
    bool check_mandatory(const vector<string>& selected_features);
    bool check_relation(const vector<string>& selected_features, const map<shared_ptr<FeatureNode>, vector<shared_ptr<FeatureNode>>>& nodes_with_parent, condition cond);
    bool validate_configuration(const string& config);
    void validate_all_configurations();
    void clear_all();
};

#endif