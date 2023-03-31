#include "Calc.h"

Node* GetG(const char* str)
{
    const char* s = str;
    Node* root = GetE(&s);
    ASSERT(*s == 0);
    return root;
}

Node* GetE(const char** s)
{
    Node* node_ch_1 = GetT(s);
    while (**s == '+' || **s == '-')
    {
        char op = **s;
        *s += 1;

        Node* node = (Node*)calloc(1, sizeof(Node));
        node->type = IS_FUNC;

        node->left_child  = node_ch_1;
        node->right_child =   GetT(s);

        if (op == '+')
            node->data.number = Add; 
        else
            node->data.number = Sub; 
        node_ch_1 = node;
    }
    return node_ch_1;
}

Node* GetT(const char** s)
{
    Node* node_ch_1 = GetF(s);
    while (**s == '*' || **s == '/')
    {
        char op = **s;
        *s += 1;

        Node* node = (Node*)calloc(1, sizeof(Node));
        node->type = IS_FUNC;

        node->left_child  = node_ch_1;
        node->right_child =   GetF(s);

        if (op == '*')
            node->data.number = Mul; 
        else
            node->data.number = Div; 
        node_ch_1 = node;
    }
    return node_ch_1;
}

Node* GetF(const char** s)
{
    Node* node = (Node*)calloc(1, sizeof(Node));
    node->type = IS_VAL;

    double val = GetN(s);
    if (**s == '.')
    {
        *s += 1;
        const char* s1 = *s;
        double val2 = GetN(s);
        val += (double)(val2/pow(10,*s - s1));
    }
    
    node->data.value = val;

    return node;
}

double GetN(const char** s)
{
    double val = 0;
    const char* sOld = *s;
    while ('0' <= **s && **s <= '9')
    {
        val = val*10 + **s - '0';
        *s += 1;
    }
    ASSERT(*s > sOld);
    return val;
}

/*
double GetB(const char** s)
{
    double val = 0;
    if (**s== '(')
    {
        *s += 1;
        val = GetE(s);
        ASSERT(**s== ')');
        *s += 1;
    }
    else 
        val = GetP(s);
    
    return val;
}

double GetP(const char** s)
{
    double val;
    if (**s == '(')
        val = GetB(s);
    else
        val = GetF(s);
    if (**s == '^')
    {
        *s += 1;
        double val1 = GetB(s);
        val = pow(val, val1);
    }
    return val;
}
*/