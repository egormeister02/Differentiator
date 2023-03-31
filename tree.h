#ifndef TREE
#define TREE
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

const size_t TREE_POISON = 0xffdeedff;

union node_data
{    
    double            value;
    size_t       number = 0;
};

enum functions
{
    #define DEF_FUNC(name, code) name = code,
    #include "def_cmd.h"
    #undef DEF_FUNC
};

enum error_codes
{
    TREE_OK                = 0,
    ERR_TO_CALLOC_NODE     = 1 << 0,
    ERR_TO_OPEN_GRAPH_TXT  = 1 << 1,
    ERR_TO_CLOSE_GRAPH_TXT = 2 << 2
};


enum node_type
{
    IS_VAL   = 0,
    IS_VARIB = 1,
    IS_FUNC  = 2
};

struct Node
{
    node_data      data        =      {};   
    node_type      type        =  IS_VAL;    
    Node*          left_child  = nullptr;
    Node*          right_child = nullptr;
};

struct Tree
{
    Node*        root         = nullptr;
    size_t       status       = TREE_OK;
};

Node* CreateNode(Tree*, node_type, node_data);

void  tree_dtor(Tree* tree_ptr);

void  dtor_childs(Node* node_ptr);

#endif