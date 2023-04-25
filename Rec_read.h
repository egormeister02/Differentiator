#include "tree.h"
#define ASSERT(condition)                                         \
if (!(condition)){                                                \
    fprintf(stdout, "Error in %s:\n"                              \
                    "FILE: %s\n"                                  \
                    "LINE: %d\n"                                  \
                    "FUNCTION: %s\n",                             \
           #condition, __FILE__, __LINE__, __PRETTY_FUNCTION__);  \
    abort();}

struct TEXT {
    char* buf = nullptr;
    size_t size = 0;
};

int CreateText(TEXT*, FILE*);

void DtorText(TEXT*);

Node* GetG(const char*, Tree*);

Node* GetE(const char**, Tree*);

Node* GetT(const char**, Tree*);

Node* GetB(const char**, Tree*);

Node* GetP(const char**, Tree*);

double GetN(const char**);

Node* GetF(const char**, Tree*);

Node* GetV(const char**, Tree*);

Node* GetS(const char**, Tree*);

Node* GetLog(const char**, Tree*);
