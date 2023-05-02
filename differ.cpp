#include "differ.h"

node_type Simplifier(Tree* tree, Node* root)
{
    if (root == nullptr) return IS_FUNC;
    if (root->type == IS_VAL || root->type == IS_VARIB) return root->type;

    node_type type_l_ch = Simplifier(tree, root->left_child);
    node_type type_r_ch = Simplifier(tree, root->right_child);

    switch (root->data.number)
    {
    case Add:

        if (type_l_ch == IS_VAL && IS_ZERO(root->left_child->data.value)) root = root->right_child;
        else if (type_r_ch == IS_VAL && IS_ZERO(root->right_child->data.value)) root = root->left_child;

        else if (type_l_ch == IS_VAL && type_r_ch == IS_VAL)
        {
            root->type = IS_VAL;
            root->data.value = root->left_child->data.value + root->right_child->data.value;
            root->left_child  = nullptr;
            root->right_child = nullptr;
            free(root->left_child);
            free(root->right_child); 
        }
        break;

    case Sub:

        if (type_r_ch == IS_VAL && IS_ZERO(root->right_child->data.value)) root = root->left_child;

        else if (type_l_ch == IS_VAL && type_r_ch == IS_VAL)
        {
            root->type = IS_VAL;
            root->data.value = root->left_child->data.value - root->right_child->data.value;
            root->left_child  = nullptr;
            root->right_child = nullptr;
            free(root->left_child);
            free(root->right_child); 
        }
        break;

    case Mul:

        if ((type_l_ch == IS_VAL && IS_ZERO(root->left_child->data.value)) || (type_r_ch == IS_VAL && IS_ZERO(root->right_child->data.value)))
        {
            root->type = IS_VAL;
            root->data.value = 0;
            root->left_child  = nullptr;
            root->right_child = nullptr;
            free(root->left_child);
            free(root->right_child); 
        }
        else if (type_l_ch == IS_VAL && type_r_ch == IS_VAL)
        {
            root->type = IS_VAL;
            root->data.value = root->left_child->data.value * root->right_child->data.value;
            root->left_child  = nullptr;
            root->right_child = nullptr;
            free(root->left_child);
            free(root->right_child); 
        }
        break;

    case Div:

        if (type_r_ch == IS_VAL && IS_ZERO(root->right_child->data.value))
        {
            printf("EROOR: division by zero.\n Node pointer = %p", root);
            TreeDump(tree);
        }
        else if (type_l_ch == IS_VAL && IS_ZERO(root->left_child->data.value)) 
        {
            root->type = IS_VAL;
            root->data.value = 0;
            root->left_child  = nullptr;
            root->right_child = nullptr;
            free(root->left_child);
            free(root->right_child); 
        }
        else if (type_l_ch == IS_VAL && type_r_ch == IS_VAL)
        {
            root->type        = IS_VAL;
            root->data.value  = root->left_child->data.value / root->right_child->data.value;
            root->left_child  = nullptr;
            root->right_child = nullptr;
            free(root->left_child);
            free(root->right_child);  
        }

        break;

    case Pow:

        if (type_r_ch == IS_VAL && IS_ZERO(root->right_child->data.value)) 
        {
            root->type        =  IS_VAL;
            root->data.value  =       1;            
            root->left_child  = nullptr;
            root->right_child = nullptr;
            free(root->left_child);
            free(root->right_child);  
        }

        else if (type_l_ch == IS_VAL && IS_ZERO(root->left_child->data.value)) 
        {
            root->type        = IS_VAL;
            root->data.value  = 0;
            root->left_child  = nullptr;
            root->right_child = nullptr;
            free(root->left_child);
            free(root->right_child); 
        }

        else if (type_l_ch == IS_VAL && type_r_ch == IS_VAL)
        {
            root->type = IS_VAL;
            root->data.value = pow(root->left_child->data.value, root->right_child->data.value);
            root->left_child  = nullptr;
            root->right_child = nullptr;
            free(root->left_child);
            free(root->right_child); 
        }
        break;

    case Cos:

        if (type_l_ch == IS_FUNC && root->left_child->data.number == Acos)
        {
            Node* child1 = root->left_child;
            Node* child2 = child1->left_child;
            *root = *(root->left_child->left_child);
            free(child1);
            free(child2);
        }

        else if (type_l_ch == IS_VAL)
        {
            root->type        = IS_VAL;
            root->data.value  = cos(root->left_child->data.value);
            root->left_child  = nullptr;
            root->right_child = nullptr;
            free(root->left_child);
            free(root->right_child); 
        }
        break;

    case Sin:

        if (type_l_ch == IS_FUNC && root->left_child->data.number == Asin)
        {
            Node* child1 = root->left_child;
            Node* child2 = child1->left_child;
            *root = *(root->left_child->left_child);
            free(child1);
            free(child2);
        }

        else if (type_l_ch == IS_VAL)
        {
            root->type        = IS_VAL;
            root->data.value  = sin(root->left_child->data.value);
            root->left_child  = nullptr;
            root->right_child = nullptr;
            free(root->left_child);
            free(root->right_child); 
        }
        break; 

    case Tan:

        if (type_l_ch == IS_FUNC && root->left_child->data.number == Atan)
        {
            Node* child1 = root->left_child;
            Node* child2 = child1->left_child;
            *root = *(root->left_child->left_child);
            free(child1);
            free(child2);
        }

        else if (type_l_ch == IS_VAL)
        {
            root->type        = IS_VAL;
            root->data.value  = tan(root->left_child->data.value);
            root->left_child  = nullptr;
            root->right_child = nullptr;
            free(root->left_child);
            free(root->right_child); 
        }
        break;

    case Acos:

        if (type_l_ch == IS_FUNC && root->left_child->data.number == Cos)
        {
            Node* child1 = root->left_child;
            Node* child2 = child1->left_child;
            *root = *(root->left_child->left_child);
            free(child1);
            free(child2);
        }

        else if (type_l_ch == IS_VAL)
        {
            root->type        = IS_VAL;
            root->data.value  = acos(root->left_child->data.value);
            root->left_child  = nullptr;
            root->right_child = nullptr;
            free(root->left_child);
            free(root->right_child); 
        }
        break;

    case Asin:

        if (type_l_ch == IS_FUNC && root->left_child->data.number == Sin)
        {
            Node* child1 = root->left_child;
            Node* child2 = child1->left_child;
            *root = *(root->left_child->left_child);
            free(child1);
            free(child2);
        }

        else if (type_l_ch == IS_VAL)
        {
            root->type        = IS_VAL; 
            root->data.value  = asin(root->left_child->data.value);
            root->left_child  = nullptr;
            root->right_child = nullptr;
            free(root->left_child);
            free(root->right_child); 
        }
        break;

    case Atan:

        if (type_l_ch == IS_FUNC && root->left_child->data.number == Tan)
        {
            Node* child1 = root->left_child;
            Node* child2 = child1->left_child;
            *root = *(root->left_child->left_child);
            free(child1);
            free(child2);
        }

        else if (type_l_ch == IS_VAL)
        {
            root->type        = IS_VAL;
            root->data.value  = atan(root->left_child->data.value);
            root->left_child  = nullptr;
            root->right_child = nullptr;
            free(root->left_child);
            free(root->right_child); 
        }
        break;

    case Sqrt:

        if (type_l_ch == IS_VAL)
        {
            if (root->left_child->data.value < 0)
            {
                printf("EROOR: root of a negative number.\n Node pointer = %p", root);
                TreeDump(tree);
            }
            else
            {
                root->type        = IS_VAL;
                root->data.value  = sqrt(root->left_child->data.value);
                root->left_child  = nullptr;
                root->right_child = nullptr;
            }
        }
        break;

    case Exp:
        if (type_l_ch == IS_FUNC && root->left_child->data.number == Ln)
        {
            Node* child1 = root->left_child;
            Node* child2 = child1->left_child;
            *root = *(root->left_child->left_child);
            free(child1);
            free(child2);
        }

        else if (type_l_ch == IS_VAL)
        {
            root->type        = IS_VAL;
            root->data.value  = exp(root->left_child->data.value);
            root->left_child  = nullptr;
            root->right_child = nullptr;
            free(root->left_child);
            free(root->right_child); 
        }
        break;

    case Ln:

        if (type_l_ch == IS_FUNC && root->left_child->data.number == Exp)
        {
            Node* child1 = root->left_child;
            Node* child2 = child1->left_child;
            *root = *(root->left_child->left_child);
            free(child1);
            free(child2);
        }

        else if (type_l_ch == IS_VAL)
        {
            if (root->left_child->data.value <= 0)
            {
                printf("EROOR: logarithm of a negative number or zero.\n Node pointer = %p", root);
                TreeDump(tree);
            }
            root->type        = IS_VAL;
            root->data.value  = log(root->left_child->data.value);
            root->left_child  = nullptr;
            root->right_child = nullptr;
            free(root->left_child);
            free(root->right_child); 
        }
        break;

    case Lg:

        if (type_l_ch == IS_VAL)
        {
            if (root->left_child->data.value <= 0)
            {
                printf("EROOR: logarithm of a negative number or zero.\n Node pointer = %p", root);
                TreeDump(tree);
            }
            root->type        = IS_VAL;
            root->data.value  = log10(root->left_child->data.value);
            root->left_child  = nullptr;
            root->right_child = nullptr;
            free(root->left_child);
            free(root->right_child); 
        }
        break;

    case Log:
        Node* l_child = root->left_child;
        Node* r_child = root->right_child;

        node_data oper_ln =  {};
        oper_ln.number    = Ln;
        root->data.number  = Div;

        root->left_child  = CreateNode(tree, IS_FUNC, oper_ln);
        root->right_child = CreateNode(tree, IS_FUNC, oper_ln);

        root->left_child->left_child  = r_child;
        root->right_child->left_child = l_child;

        Simplifier(tree, root);

        break;

    }

    return root->type;
}
/*
int Diff_Tree(Node* root, Node* diff)
{

}
*/