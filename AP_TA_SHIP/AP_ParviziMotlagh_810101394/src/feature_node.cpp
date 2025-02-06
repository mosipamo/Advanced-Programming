#include "../include/feature_node.hpp"

FeatureNode::FeatureNode(const string& name, char relation, vector<shared_ptr<FeatureNode>> children, shared_ptr<FeatureNode> parent, int level) {
    this->name = name;
    this->relation = relation;
    this->parent = parent;
    this->children = children;
    this->level = level;
}

bool FeatureNode::validate_node(const vector<string>& selected_features) {
    const shared_ptr<FeatureNode>& parent = this->get_parent();
    const string& parent_name = parent->get_name();
    auto it = find(selected_features.begin(), selected_features.end(), parent_name);
    if (it == selected_features.end()) {
        return false;
    }
    return true;
}

const string FeatureNode::get_name() const {
    return name;
}

void FeatureNode::set_parent(shared_ptr<FeatureNode> parent_node) {
    this->parent = parent_node;
}

shared_ptr<FeatureNode> FeatureNode::get_parent() const {
    return parent;
}

const vector<shared_ptr<FeatureNode>>& FeatureNode::get_children() const {
    return children;
}

void FeatureNode::set_children(vector<shared_ptr<FeatureNode>> children) {
    this->children = children;
}

const char FeatureNode::get_relation() const {
    return relation;
}

void FeatureNode::set_level(int level) {
    this->level = level;
}

const int FeatureNode::get_level() const {
    return level;
}