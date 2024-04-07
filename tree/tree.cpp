#include "tree.h"

Node* CreateNode(Tree* tree, node_type type, node_data data)
{
    if (tree == nullptr) 
    {
        printf("ERROR: Tree* == nullptr in func 'CreateNode'\n");
        return nullptr;
    }

    Node* new_node = (Node*)calloc(1, sizeof(Node));
    if (new_node == nullptr)
    {
        tree->status |= ERR_TO_CALLOC_NODE;
        return nullptr;
    }

    if (type == IS_VAL)
        new_node->data.value = data.value;
    else    
        new_node->data.number = data.number;

    new_node->type = type;

    return new_node;
}

Node* Copy_Tree(Tree* tree, const Node* root)
{
    if (root == nullptr)
        return nullptr;

    else if (root->type != IS_FUNC)
        return CreateNode(tree, root->type, root->data);

    else
    {
        Node* node = CreateNode(tree, root->type, root->data);
        node->left_child = Copy_Tree(tree, root->left_child);
        node->right_child = Copy_Tree(tree, root->right_child);
        return node;
    }
}

void PrintTree(FILE* OutFile, Tree* tree, PrintMode mode)
{
    char* func_str[NUMBER_FUNC] = {};

    #define DEF_FUNC(name, code, str) char name[5] = str; func_str[code] = name;
    #include "def_cmd.h"
    #undef DEF_FUNC

    switch (mode)
    {
    case IN:
        print_inorder(OutFile, tree->root, func_str);
        break;

    case PRE:
        print_preorder(OutFile, tree->root, func_str);
        break;
    
    case POST:
        print_postorder(OutFile, tree->root, func_str);
        break;
    }
}

void print_preorder(FILE* OutFile, Node* node_ptr, char** func_str)
{
    if(node_ptr == nullptr)
    {
        return;
    }
    fprintf(OutFile, "(");
    if (node_ptr->type == IS_VAL)
    {
        fprintf(OutFile, "%.3f", node_ptr->data.value);
    }
    else if (node_ptr->type == IS_FUNC)
    {
        fprintf(OutFile, "%s", func_str[node_ptr->data.number]);
    }
    else 
        fprintf(OutFile, "%c", (char)node_ptr->data.number);

    print_preorder(OutFile, node_ptr->left_child, func_str);
    print_preorder(OutFile, node_ptr->right_child, func_str);
    fprintf(OutFile, ")");
}

void print_inorder(FILE* OutFile, Node* node_ptr, char** func_str)
{
    if(node_ptr == nullptr)
    {
        return;
    }
    fprintf(OutFile, "(");
    print_inorder(OutFile, node_ptr->left_child, func_str);
    if (node_ptr->type == IS_VAL)
    {
        fprintf(OutFile, "%.3f", node_ptr->data.value);
    }
    else if (node_ptr->type == IS_FUNC)
    {
        fprintf(OutFile, "%s", func_str[node_ptr->data.number]);
    }
    else
    {
        fprintf(OutFile, "%c", (char)node_ptr->data.number);
    }
    print_inorder(OutFile, node_ptr->right_child, func_str);
    fprintf(OutFile, ")");
}

void print_postorder(FILE* OutFile, Node* node_ptr, char** func_str)
{
    if(node_ptr == nullptr)
    {
        return;
    }
    fprintf(OutFile, "(");
    print_postorder(OutFile, node_ptr->left_child, func_str);
    print_postorder(OutFile, node_ptr->right_child, func_str);
    if (node_ptr->type == IS_VAL)
    {
        fprintf(OutFile, "%.3f", node_ptr->data.value);
    }
    else if (node_ptr->type == IS_FUNC)
    {
        fprintf(OutFile, "%s", func_str[node_ptr->data.number]);
    }
    else
    {
        fprintf(OutFile, "%c", (char)node_ptr->data.number);
    }
    fprintf(OutFile, ")");
}

void  tree_dtor(Tree* tree_ptr)
{
    dtor_childs(tree_ptr->root);

    tree_ptr->root = nullptr;
    tree_ptr->status |= TREE_OK;
}

void  dtor_childs(Node* node_ptr)
{
    if(node_ptr->left_child != nullptr)
    {
        dtor_childs(node_ptr->left_child);
        node_ptr->left_child = nullptr;
    }
    if(node_ptr->right_child != nullptr)
    {
        dtor_childs(node_ptr->right_child);
        node_ptr->right_child = nullptr;
    }

    node_ptr->data.number = TREE_POISON;

    free(node_ptr);
    node_ptr = nullptr;
}

