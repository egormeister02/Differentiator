#include "tree.h"
#include "dump.h"

const double EPSILON = 0.000000001;

#define IS_ZERO(val) (abs(val) < EPSILON)

node_type Simplifier(Tree*, Node*);

Node* Diff_Tree(const Node*, Tree*);

Node* Make_tree_for_pow(const Node*);


