#include "Rec_read.h"

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
    Node* node_ch_1 = GetP(s);
    while (**s == '*' || **s == '/')
    {
        char op = **s;
        *s += 1;

        Node* node = (Node*)calloc(1, sizeof(Node));
        node->type = IS_FUNC;

        node->left_child  = node_ch_1;
        node->right_child =   GetP(s);

        if (op == '*')
            node->data.number = Mul; 
        else
            node->data.number = Div; 
        node_ch_1 = node;
    }
    return node_ch_1;
}

Node* GetP(const char** s)
{
    Node* node_ch_1 = GetB(s);
    while (**s == '^')
    {
        *s += 1;

        Node* node = (Node*)calloc(1, sizeof(Node));
        node->type = IS_FUNC;

        node->left_child  = node_ch_1;
        node->right_child =   GetB(s);

        node->data.number = Pow; 

        node_ch_1 = node;
    }
    return node_ch_1;
}

Node* GetB(const char** s)
{
    Node* node = NULL;
    if (**s== '(')
    {
        *s += 1;
        node = GetE(s);
        ASSERT(**s== ')');
        *s += 1;
    }
    else 
        node = GetS(s);
    
    return node;
}

Node* GetS(const char** s)
{
    Node* node = NULL;
    const char* sOld = *s;
    if ('0' <= **s && **s <= '9')
        node = GetF(s);
    else 
    {
        char in_str[5] = {};

        #define DEF_FUNC(name, code, str)                   \
        if (code > 4 && name != Log)                        \
        {                                                   \
            memset(in_str, 0, 5);                           \
            strncpy(in_str, *s, strlen(str));               \
            if (strcasecmp(in_str, str) == 0)               \
                {                              \
                    node = (Node*)calloc(1, sizeof(Node));  \
                    node->type = IS_FUNC;                   \
                    node->data.number = code;               \
                    *s += strlen(str);                      \
                }                                           \
        }                                                   \
        else if (name == Log)                               \
        {                                                   \
            memset(in_str, 0, 5);                           \
            strncpy(in_str, *s, strlen(str));               \
            if (strcasecmp(in_str, str) == 0)               \
                {                                           \
                    node = GetLog(s);                       \
                }                                           \
        }                      
        #include "def_cmd.h"
        #undef DEF_FUNC 

        if (node == NULL)
            node = GetV(s); 

        else if (**s == '(')
            node->left_child = GetB(s); 

    }
    ASSERT(*s > sOld);
    return node;
}

Node* GetV(const char** s)
{
    Node* node = (Node*)calloc(1, sizeof(Node));
    node->type = IS_VARIB;
    node->data.number = (size_t)**s;
    *s += 1;
    return node;
}

Node* GetLog(const char** s)
{
    Node* node = (Node*)calloc(1, sizeof(Node));
    node->type = IS_FUNC;
    node->data.number = Log;

    *s += 3;

    if (**s == '(')
    {     
        *s += 1;
        node->left_child = GetE(s);
        ASSERT(**s == ',');
        *s += 1;
        node->right_child = GetE(s);
        ASSERT(**s == ')');
        *s += 1;
    }
    
    return node;
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
