#include "colors.h"

#define StatPrint_(STATUS,text)                 \
    if (tree->status & STATUS)                  \
    {                                           \
        fprintf(LogList, "\t"#text "\n");       \
    }

const char    NAME_LOG_FILE[]   =     "TreeLog.html";
const char    NAME_DOT_FOLDER[] =        "dot_files";


void TreeDump(Tree*);      

size_t print_tree_data(Tree* tree, Node* node_ptr, FILE* DumpFile);

size_t print_tree_links(Tree* tree, Node* node_ptr, FILE* DumpFile);

FILE* StartLog(void);

void MakePngName(char* name, char num);
