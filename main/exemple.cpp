#include "differ.h"
#include "Rec_read.h"
#include "filename.h"

int main(int argc, char *argv[]) 
{
    // Проверка наличия аргумента командной строки (имени входного файла)
    if (argc != 2) {
        printf("Use: %s <input_file>\n", argv[0]);
        return 1;
    }

    char* in_filename = argv[1];

    if (FileNameVerify(in_filename, ".txt")) return 1;

    FILE* in_file = fopen(in_filename, "r+b");

    if (in_file == nullptr)
    {
        printf("Error: file does not exist\n");
        return 1;
    }

    //FILE* Out = fopen("file.out", "w");
    TEXT text = {};
    Tree tree = {};

    CreateText(&text, in_file);
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

    Tree diff_tree = {};

    diff_tree.root = Diff_Tree(tree.root, &diff_tree);

    TreeDump(&diff_tree);

    Simplifier(&diff_tree, diff_tree.root);
    Simplifier(&diff_tree, diff_tree.root);

    TreeDump(&diff_tree);

    //PrintTree(Out, &tree, IN);
    //TreeDump(&tree);
    //TreeDump(&tree);

    tree_dtor(&tree);
    tree_dtor(&diff_tree);
    fclose(in_file);

    return 0;
}