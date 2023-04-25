#include "differ.h"
#include "Rec_read.h"

int main()
{
    FILE* In = fopen("file.in", "r");
    FILE* Out = fopen("file.out", "w");
    TEXT text = {};
    Tree tree = {};

    CreateText(&text, In);
    tree.root = GetG(text.buf, &tree);
    DtorText(&text);

/*
    val.number = Add;
    tree.root = CreateNode(&tree, IS_FUNC, val);
    val.value = 5;
    tree.root->left_child = CreateNode(&tree, IS_VAL, val);
    val.value = 10;
    tree.root->right_child = CreateNode(&tree, IS_VAL, val);
*/
    TreeDump(&tree);

    Simplifier(&tree, tree.root);
     
    TreeDump(&tree);

    PrintTree(Out, &tree, IN);
    //TreeDump(&tree);
    //TreeDump(&tree);

    tree_dtor(&tree);

    return 0;
}