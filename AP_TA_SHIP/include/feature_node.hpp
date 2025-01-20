#ifndef FEATURE_NODE_HPP
#define FEATURE_NODE_HPP

#include "../include/manual.hpp"

class FeatureNode {
protected:
    string name;
    char relation;
    vector<shared_ptr<FeatureNode>> children;
    shared_ptr<FeatureNode> parent;
    int level;

public:
    FeatureNode(const string& name, char relation, vector<shared_ptr<FeatureNode>> children = {}, shared_ptr<FeatureNode> parent = nullptr, int level = -1);
    const string get_name() const;
    void set_parent(shared_ptr<FeatureNode> parent_node);
    shared_ptr<FeatureNode> get_parent() const;
    const char get_relation() const;
    void set_children(vector<shared_ptr<FeatureNode>> children);
    const vector<shared_ptr<FeatureNode>>& get_children() const;
    void set_level(int level);
    const int get_level() const;
    bool validate_node(const vector<string>& selected_features);
};


class MandatoryNode : public FeatureNode {
public:
    MandatoryNode(const string& name);
};

class OptionalNode : public FeatureNode {
public:
    OptionalNode(const string& name);
};

class OrNode : public FeatureNode {
public:
    OrNode(const string& name);
};

class XorNode : public FeatureNode {
public:
    XorNode(const string& name);
};

#endif // FEATURE_NODE_H