#include "tree.h"
#include "Dump/dump.h"

int main()
{
    Tree tree = {};
    node_data val = {};

    val.number = Add;
    tree.root = CreateNode(&tree, IS_FUNC, val);
    val.value = 5;
    tree.root->left_child = CreateNode(&tree, IS_VAL, val);
    val.value = 10;
    tree.root->right_child = CreateNode(&tree, IS_VAL, val);

    TreeDump(&tree);
    //TreeDump(&tree);
    //TreeDump(&tree);

    tree_dtor(&tree);

    return 0;
}