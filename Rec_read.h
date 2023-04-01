#include "tree.h"
#define ASSERT(condition)                                         \
if (!(condition)){                                                \
    fprintf(stdout, "Error in %s:\n"                              \
                    "FILE: %s\n"                                  \
                    "LINE: %d\n"                                  \
                    "FUNCTION: %s\n",                             \
           #condition, __FILE__, __LINE__, __PRETTY_FUNCTION__);  \
    abort();}


Node* GetG(const char*);

Node* GetE(const char**);

Node* GetT(const char**);

Node* GetB(const char**);

Node* GetP(const char**);

double GetN(const char**);

Node* GetF(const char**);

Node* GetV(const char**);

Node* GetS(const char**);

Node* GetLog(const char**);
