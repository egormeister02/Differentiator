#include "tree.h"

Node* CreateNode(Tree* tree, node_type type, node_data data)
{
    if (tree == NULL) 
    {
        printf("ERROR: Tree* == NULL in func 'CreateNode'\n");
        return NULL;
    }

    Node* new_node = (Node*)calloc(1, sizeof(Node));
    if (new_node == NULL)
    {
        tree->status |= ERR_TO_CALLOC_NODE;
        return NULL;
    }

    if (type == IS_VAL)
        new_node->data.value = data.value;
    else    
        new_node->data.number = data.number;

    new_node->type = type;

    return new_node;
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
    
    default:
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

    tree_ptr->root = NULL;
    tree_ptr->status |= TREE_OK;
}

void  dtor_childs(Node* node_ptr)
{
    if(node_ptr->left_child != NULL)
    {
        dtor_childs(node_ptr->left_child);
        node_ptr->left_child = NULL;
    }
    if(node_ptr->right_child != NULL)
    {
        dtor_childs(node_ptr->right_child);
        node_ptr->right_child = NULL;
    }

    node_ptr->data.number = TREE_POISON;

    free(node_ptr);
    node_ptr = NULL;
}

