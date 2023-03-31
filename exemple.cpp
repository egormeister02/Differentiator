#include "tree.h"
#include "dump.h"
#include "Calc.h"

int main()
{
    FILE* Out = fopen("outfile.txt", "a+");
    Tree tree = {};

    char* str = NULL;
    str = (char*)calloc(100, sizeof(char));
    scanf("%s", str);
    tree.root = GetG(str);
    free(str);

/*
    val.number = Add;
    tree.root = CreateNode(&tree, IS_FUNC, val);
    val.value = 5;
    tree.root->left_child = CreateNode(&tree, IS_VAL, val);
    val.value = 10;
    tree.root->right_child = CreateNode(&tree, IS_VAL, val);
*/
    TreeDump(&tree);
    PrintTree(Out, &tree, IN);
    fputc('\n', Out);
    //TreeDump(&tree);
    //TreeDump(&tree);

    tree_dtor(&tree);

    return 0;
}