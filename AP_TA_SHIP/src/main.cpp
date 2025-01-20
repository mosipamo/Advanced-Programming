#include "../include/feature_tree.hpp"
#include "../include/manual.hpp"

int main() {
    shared_ptr<FeatureTree> coffee_shop = make_shared<FeatureTree> ();
    coffee_shop->make_coffee_shop();
    return 0;
}