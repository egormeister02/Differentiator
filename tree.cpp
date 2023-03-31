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

