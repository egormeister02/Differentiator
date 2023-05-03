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
        if (type_l_ch == IS_FUNC && type_r_ch == IS_FUNC && root->left_child->data.number == Mul && root->right_child->data.number == Mul)
        {
            if (root->left_child->right_child->type == IS_VARIB && root->right_child->right_child->type == IS_VARIB)
            {
                if (root->left_child->right_child->data.number == root->right_child->right_child->data.number)
                {
                    Node* old_l_child = root->left_child;
                    Node* old_r_child = root->right_child;
                    root->data.number = Mul;

                    root->right_child = CreateNode(tree, IS_VARIB, old_l_child->right_child->data);

                    node_data oper {};
                    oper.number = Add;
                    root->left_child = CreateNode(tree, IS_FUNC, oper);

                    root->left_child->left_child = old_l_child->left_child;
                    root->left_child->right_child = old_r_child->left_child;

                    free(old_l_child->right_child);
                    free(old_r_child->right_child);
                    free(old_l_child);
                    free(old_r_child);   

                    Simplifier(tree, root->left_child);                 
                }
            }
        }
        else if (type_l_ch == IS_VAL && IS_ZERO(root->left_child->data.value)) root = root->right_child;
        else if (type_r_ch == IS_VAL && IS_ZERO(root->right_child->data.value)) root = root->left_child;

        else if (type_l_ch == IS_VAL && type_r_ch == IS_VAL)
        {
            root->type = IS_VAL;
            root->data.value = root->left_child->data.value + root->right_child->data.value;
            free(root->left_child);
            free(root->right_child);root->left_child  = nullptr;
            root->right_child = nullptr;
             
        }
        break;

    case Sub:
        if (type_l_ch == IS_FUNC && type_r_ch == IS_FUNC && root->left_child->data.number == Mul && root->right_child->data.number == Mul)
        {
            if (root->left_child->right_child->type == IS_VARIB && root->right_child->right_child->type == IS_VARIB)
            {
                if (root->left_child->right_child->data.number == root->right_child->right_child->data.number)
                {
                    Node* old_l_child = root->left_child;
                    Node* old_r_child = root->right_child;
                    root->data.number = Mul;

                    root->right_child = CreateNode(tree, IS_VARIB, old_l_child->right_child->data);

                    node_data oper {};
                    oper.number = Sub;
                    root->left_child = CreateNode(tree, IS_FUNC, oper);

                    root->left_child->left_child = old_l_child->left_child;
                    root->left_child->right_child = old_r_child->left_child;

                    free(old_l_child->right_child);
                    free(old_r_child->right_child);
                    free(old_l_child);
                    free(old_r_child);   

                    Simplifier(tree, root->left_child);                 
                }
            }
        }
        else if (type_r_ch == IS_VAL && IS_ZERO(root->right_child->data.value)) root = root->left_child;

        else if (type_l_ch == IS_VAL && type_r_ch == IS_VAL)
        {
            root->type = IS_VAL;
            root->data.value = root->left_child->data.value - root->right_child->data.value;
            free(root->left_child);
            free(root->right_child);root->left_child  = nullptr;
            root->right_child = nullptr;
             
        }
        break;

    case Mul:
        if (type_r_ch == IS_VAL && type_l_ch != IS_VAL)
        {
            Node* l_child = root->left_child;
            root->left_child = root->right_child;
            root->right_child = l_child;

            node_type temp_type = type_l_ch;
            type_l_ch = type_r_ch;
            type_r_ch = temp_type;
        }

        if (type_l_ch == IS_VARIB && type_r_ch == IS_FUNC)
        {
            Node* l_child = root->left_child;
            root->left_child = root->right_child;
            root->right_child = l_child;

            node_type temp_type = type_l_ch;
            type_l_ch = type_r_ch;
            type_r_ch = temp_type;
        }

        if (type_l_ch == IS_FUNC && root->left_child->data.number == Ln)
        {
            root->data.number = Ln;
            root->left_child->data.number = Pow;
            root->left_child->right_child = root->right_child;
            root->right_child = nullptr;
        }

        else if (type_r_ch == IS_FUNC && root->right_child->data.number == Ln)
        {
            root->data.number = Ln;
            Node* old_l_child = root->left_child;

            node_data oper = {};
            oper.number = Pow;
            root->left_child = CreateNode(tree, IS_FUNC, oper);
            
            root->left_child->left_child = root->right_child->left_child;
            root->left_child->right_child = old_l_child;

            free(root->right_child);
            root->right_child = nullptr;
        }

        else if ((type_l_ch == IS_VAL && IS_ZERO(root->left_child->data.value)) || (type_r_ch == IS_VAL && IS_ZERO(root->right_child->data.value)))
        {
            root->type = IS_VAL;
            root->data.value = 0;  
            free(root->left_child);
            free(root->right_child);
            root->left_child  = nullptr;
            root->right_child = nullptr;
        }
        else if (type_l_ch == IS_VAL && type_r_ch == IS_VAL)
        {
            root->type = IS_VAL;
            root->data.value = root->left_child->data.value * root->right_child->data.value;           
            free(root->left_child);
            free(root->right_child); 
            root->left_child  = nullptr;
            root->right_child = nullptr;
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
            free(root->left_child);
            free(root->right_child);root->left_child  = nullptr;
            root->right_child = nullptr;
             
        }
        else if (type_l_ch == IS_VAL && type_r_ch == IS_VAL)
        {
            root->type        = IS_VAL;
            root->data.value  = root->left_child->data.value / root->right_child->data.value;

            free(root->left_child);
            free(root->right_child);
            root->left_child  = nullptr;
            root->right_child = nullptr;             
        }

        break;

    case Pow:

        if (type_r_ch == IS_VAL && IS_ZERO(root->right_child->data.value)) 
        {
            root->type        =  IS_VAL;
            root->data.value  =       1;   

            free(root->left_child);
            free(root->right_child);
            root->left_child  = nullptr;
            root->right_child = nullptr;              
        }

        else if (type_l_ch == IS_VAL && IS_ZERO(root->left_child->data.value)) 
        {
            root->type        = IS_VAL;
            root->data.value  = 0;

            free(root->left_child);
            free(root->right_child);
            root->left_child  = nullptr;
            root->right_child = nullptr;             
        }

        else if (type_l_ch == IS_VAL && type_r_ch == IS_VAL)
        {
            root->type = IS_VAL;
            root->data.value = pow(root->left_child->data.value, root->right_child->data.value);

            free(root->left_child);
            free(root->right_child);
            root->left_child  = nullptr;
            root->right_child = nullptr;             
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

            free(root->left_child);
            free(root->right_child);
            root->left_child  = nullptr;
            root->right_child = nullptr;             
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

            free(root->left_child);
            free(root->right_child);
            root->left_child  = nullptr;
            root->right_child = nullptr;             
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

            free(root->left_child);
            free(root->right_child);
            root->left_child  = nullptr;
            root->right_child = nullptr;             
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

            free(root->left_child);
            free(root->right_child);
            root->left_child  = nullptr;
            root->right_child = nullptr;             
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

            free(root->left_child);
            free(root->right_child);
            root->left_child  = nullptr;
            root->right_child = nullptr;             
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

            free(root->left_child);
            free(root->right_child);
            root->left_child  = nullptr;
            root->right_child = nullptr;
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

            free(root->left_child);
            free(root->right_child);
            root->left_child  = nullptr;
            root->right_child = nullptr;             
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

            free(root->left_child);
            free(root->right_child);
            root->left_child  = nullptr;
            root->right_child = nullptr;             
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

            free(root->left_child);
            free(root->right_child);
            root->left_child  = nullptr;
            root->right_child = nullptr;             
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

int Diff_Tree(const Node* root, Node* diff_node, Tree* diff_tree)
{
    if (root->type == IS_VAL)
    {
        node_data data = {};
        data.value = 0;
        diff_node = CreateNode(diff_tree, IS_VAL, data);
        return 0;
    }

    else if (root->type == IS_VARIB)
    {
        node_data data = {};
        data.value = 1;
        diff_node = CreateNode(diff_tree, IS_VAL, data);
        return 0;
    }

    else
    {
        node_data oper = {};
        switch (root->data.number)
        {
        case Add:            
            oper.number = Add; 
            diff_node = CreateNode(diff_tree, IS_FUNC, oper);
            Diff_Tree(root->left_child, diff_node->left_child, diff_tree);
            Diff_Tree(root->right_child, diff_node->right_child, diff_tree);
            break;

        case Sub:
            oper.number = Sub; 
            diff_node = CreateNode(diff_tree, IS_FUNC, oper);
            Diff_Tree(root->left_child, diff_node->left_child, diff_tree);
            Diff_Tree(root->right_child, diff_node->right_child, diff_tree);
            break;

        case Mul:
            oper.number = Add;
            diff_node = CreateNode(diff_tree, IS_FUNC, oper);

            oper.number = Mul;
            diff_node->left_child = CreateNode(diff_tree, IS_FUNC, oper);
            diff_node->right_child = CreateNode(diff_tree, IS_FUNC, oper);

            Diff_Tree(root->left_child, diff_node->left_child->left_child, diff_tree);
            diff_node->left_child->right_child = Copy_Tree(diff_tree, root->right_child);

            Diff_Tree(root->right_child, diff_node->right_child->left_child, diff_tree);
            diff_node->right_child->right_child = Copy_Tree(diff_tree, root->left_child);

            break;

        case Div:
            oper.number = Div;
            diff_node = CreateNode(diff_tree, IS_FUNC, oper);

            oper.number = Sub;            
            diff_node->left_child = CreateNode(diff_tree, IS_FUNC, oper);

            oper.number = Mul;
            diff_node->left_child->left_child = CreateNode(diff_tree, IS_FUNC, oper);
            diff_node->left_child->right_child = CreateNode(diff_tree, IS_FUNC, oper);

            Diff_Tree(root->left_child, diff_node->left_child->left_child->left_child, diff_tree);
            diff_node->left_child->left_child->right_child = Copy_Tree(diff_tree, root->right_child);

            Diff_Tree(root->right_child, diff_node->left_child->right_child->left_child, diff_tree);
            diff_node->left_child->right_child->right_child = Copy_Tree(diff_tree, root->left_child);

            oper.number = Pow;
            diff_node->right_child = CreateNode(diff_tree, IS_FUNC, oper);

            diff_node->right_child->left_child = Copy_Tree(diff_tree, root->right_child);

            oper.value = 2;
            diff_node->right_child->right_child = CreateNode(diff_tree, IS_VAL, oper);

            break;

        case Pow:

            
        default:
            break;
        }
    }
    
}

