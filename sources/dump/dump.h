#ifndef DUMP
#define DUMP

#include "tree.h"
#include "colors.h"

#define StatPrint_(STATUS,text)                 \
    if (tree->status & STATUS)                  \
    {                                           \
        fprintf(LogList, "\t"#text "\n");       \
    }

const char    NAME_LOG_FILE[]   =     "logs/TreeLog.html";
const char    NAME_DOT_FOLDER[] =        "dot_files";


void TreeDump(Tree*, const char* message = nullptr);      

size_t print_tree_data(Tree* tree, Node* node_ptr, FILE* DumpFile);

size_t print_tree_links(Tree* tree, Node* node_ptr, FILE* DumpFile);

FILE* StartLog(void);

void MakePngName(char* name, char num);

#endif