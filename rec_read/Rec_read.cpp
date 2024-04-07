#include "Rec_read.h"

int CreateText(TEXT* text, FILE* file) 
{
    ASSERT(text != nullptr);
    ASSERT(file != nullptr);

    fseek(file, 0, SEEK_END);
    text->size = ftell(file);
    rewind(file);

    text->buf = (char*)calloc(text->size + 1, sizeof(char));
    if (text->buf == nullptr) return -1;

    text->size = fread(text->buf,sizeof(char), text->size, file);

    return 0;
}

void DtorText(TEXT* text)
{
    ASSERT(text != nullptr);

    free(text->buf);
    text->buf = nullptr;
    
}


Node* GetG(const char* str, Tree* tree)
{
    const char* s = str;
    Node* root = GetE(&s, tree);
    ASSERT(*s == 0);
    return root;
}

Node* GetE(const char** s, Tree* tree)
{
    Node* node_ch_1 = GetT(s, tree);
    while (**s == '+' || **s == '-')
    {
        char op = **s;
        *s += 1;

        node_data node_oper = {};
        Node* node = nullptr;

        if (op == '+')
            node_oper.number = Add; 
        else
            node_oper.number = Sub; 

        node = CreateNode(tree, IS_FUNC, node_oper);

        node->left_child  = node_ch_1;
        node->right_child =   GetT(s, tree);
        
        node_ch_1 = node;
    }
    return node_ch_1;
}

Node* GetT(const char** s, Tree* tree)
{
    Node* node_ch_1 = GetP(s, tree);
    while (**s == '*' || **s == '/')
    {
        char op = **s;
        *s += 1;

        node_data node_oper = {};
        Node* node = nullptr;

        if (op == '*')
            node_oper.number = Mul; 
        else
            node_oper.number = Div; 

        node = CreateNode(tree, IS_FUNC, node_oper);

        node->left_child  = node_ch_1;
        node->right_child =   GetP(s, tree);

        node_ch_1 = node;
    }
    return node_ch_1;
}

Node* GetP(const char** s, Tree* tree)
{
    Node* node_ch_1 = GetB(s, tree);
    while (**s == '^')
    {
        *s += 1;

        node_data node_oper = {};
        Node* node = nullptr;
        node_oper.number = Pow; 
        node = CreateNode(tree, IS_FUNC, node_oper);

        node->left_child  = node_ch_1;
        node->right_child =   GetB(s, tree);

        node_ch_1 = node;
    }
    return node_ch_1;
}

Node* GetB(const char** s, Tree* tree)
{
    Node* node = nullptr;
    if (**s== '(')
    {
        *s += 1;
        node = GetE(s, tree);
        ASSERT(**s== ')');
        *s += 1;
    }
    else 
        node = GetS(s, tree);
    
    return node;
}

Node* GetS(const char** s, Tree* tree)
{
    Node* node = nullptr;
    const char* sOld = *s;
    if ('0' <= **s && **s <= '9')
        node = GetF(s, tree);
    else 
    {
        char in_str[5] = {};

        #define DEF_FUNC(name, code, str)                           \
        if (code > 4 && name != Log)                                \
        {                                                           \
            memset(in_str, 0, 5);                                   \
            strncpy(in_str, *s, strlen(str));                       \
            if (strcasecmp(in_str, str) == 0)                       \
                {                                                   \
                    node_data node_oper =   {};                     \
                    node_oper.number    = code;                     \
                    node = CreateNode(tree, IS_FUNC, node_oper);    \
                    *s += strlen(str);                              \
                }                                                   \
        }                                                           \
        else if (name == Log)                                       \
        {                                                           \
            memset(in_str, 0, 5);                                   \
            strncpy(in_str, *s, strlen(str));                       \
            if (strcasecmp(in_str, str) == 0)                       \
                {                                                   \
                    node = GetLog(s, tree);                         \
                }                                                   \
        }                      
        #include "def_cmd.h"
        #undef DEF_FUNC 

        if (node == nullptr)
            node = GetV(s, tree); 

        else if (**s == '(')
            node->left_child = GetB(s, tree); 

    }
    ASSERT(*s > sOld);
    return node;
}

Node* GetV(const char** s, Tree* tree)
{
    node_data node_code = {};
    Node* node = nullptr;
    node_code.number = (size_t)**s;
    node = CreateNode(tree, IS_VARIB, node_code);
    *s += 1;
    return node;
}

Node* GetLog(const char** s, Tree* tree)
{
    node_data node_oper = {};
    Node* node = nullptr;
    node_oper.number = Log;
    node = CreateNode(tree, IS_FUNC, node_oper);

    *s += 3;

    if (**s == '(')
    {     
        *s += 1;
        node->left_child = GetE(s, tree);
        ASSERT(**s == ',');
        *s += 1;
        node->right_child = GetE(s, tree);
        ASSERT(**s == ')');
        *s += 1;
    }
    
    return node;
}

Node* GetF(const char** s, Tree* tree)
{
    node_data node_val = {};
    Node* node = nullptr;

    node_val.value = GetN(s);
    if (**s == '.')
    {
        *s += 1;
        const char* s1 = *s;
        double val2 = GetN(s);
        node_val.value += (double)(val2/pow(10,*s - s1));
    }
    
    node = CreateNode(tree, IS_VAL, node_val);

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
