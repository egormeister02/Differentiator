#include "tree.h"
#include "Dump/dump.h"

FILE* LogList = StartLog();

void TreeDump(Tree* tree)
{
    if (tree == NULL) 
    {
        fputs("!!!__list == nullptr__!!!", LogList);
        return;
    }

    fprintf(LogList, "\n<pre>\n----------------------------------TreeDump----------------------------------\n\n");

    fprintf(LogList, "-----------------------------------\n");
    if (tree->status == 0)
        fprintf(LogList, "\t>>>List is OK\n");
    else 
    {   
        StatPrint_(ERR_TO_CALLOC_NODE,                >>>Can not to allocate memory for node!!!!!);
        StatPrint_(ERR_TO_OPEN_GRAPH_TXT,             >>>Can not to open Dump file!!!!!);
        StatPrint_(ERR_TO_CLOSE_GRAPH_TXT,            >>>Can not to close Dump file!!!!!);  
    }
    fprintf(LogList, "-----------------------------------\n");

    if (tree->root == NULL) 
    {
        fputs("!!!__list->buf == nullptr__!!!", LogList);
        return;
    }
    else
        fprintf(LogList, "\n    root pointer         = %p\n", tree->root);

    fprintf(LogList, "\n---------------------------------------------------------------------------\n<pre>\n");

    FILE* DumpFile = fopen("dump.dot", "w+");

    fprintf(DumpFile, "\n");
    fprintf(DumpFile, "digraph\n");
    fprintf(DumpFile, "{\n");
    fprintf(DumpFile, "\trankdir=TB;\n");
    fprintf(DumpFile, "\tsplines=true;\n");

    print_tree_data(tree, tree->root, DumpFile);
    print_tree_links(tree, tree->root, DumpFile);

    fprintf(DumpFile, "}\n");
    
    fclose(DumpFile);

    static char pngIndex    = 1;
    char dumpName[40] = "";
    MakePngName(dumpName, pngIndex);

    char buff[100] = "";
    sprintf(buff, "dot -Tsvg -o %s dump.dot", dumpName);
    system(buff);

    fprintf(LogList, "<img src = %s>\n", dumpName);
    pngIndex++;
}

size_t print_tree_data(Tree* tree, Node* node_ptr, FILE* DumpFile)
{
    if(DumpFile == nullptr)
    {
        tree->status |= ERR_TO_OPEN_GRAPH_TXT;
        return ERR_TO_OPEN_GRAPH_TXT;
    }

    if(node_ptr != nullptr)
    {  
        if(node_ptr->type == IS_VAL)
        {
            fprintf(DumpFile, "\tnode_%p[shape = Mrecord, style=\"filled\" fillcolor=\"%s\", label =\" { <f0> left_child = %p } | {{<here> type = VALUE} | { value = %f \\n }} | { <f1> right_child = %p } \"];\n", node_ptr, RED_BG_COLOR_DOT, node_ptr->left_child, node_ptr->data.value, node_ptr->right_child);
        }
        else if(node_ptr->type == IS_FUNC)
        {
            #define DEF_FUNC(name, code)                                                                                \
            if (node_ptr->data.number == code)                                                                          \
            {                                                                                                           \
                fprintf(DumpFile, "\tnode_%p[shape = Mrecord, style=\"filled\" fillcolor=\"%s\", label =\" { <f0> left_child = %p } | {{<here> type = FUNCTION} | {value = %s \\n}} | { <f1> right_child = %p } \"];\n",                           \
                                   node_ptr, PURP_BG_COLOR_DOT, node_ptr->left_child, #name, node_ptr->right_child);    \
            }
            #include "def_cmd.h"
            #undef DEF_FUNC
        }
        else
        {
            fprintf(DumpFile, "\tnode_%p[shape = Mrecord, style=\"filled\" fillcolor=\"%s\", label =\" { <f0> left_child = %p } | {{<here> type = VARIABLE} | {value = %c \\n}} | { <f1> right_child = %p } \"];\n",
                               node_ptr, ORAN_BG_COLOR_DOT, node_ptr->left_child, (char)node_ptr->data.number, node_ptr->right_child);
        }
        
        
        if(node_ptr->left_child != nullptr)
        {
            print_tree_data(tree, node_ptr->left_child, DumpFile);
        }
        if(node_ptr->right_child != nullptr)
        {
            print_tree_data(tree, node_ptr->right_child, DumpFile);
        }
    }

    return 0;
}

size_t print_tree_links(Tree* tree, Node* node_ptr, FILE* DumpFile)
{
    if(DumpFile == nullptr)
    {
        tree->status |= ERR_TO_OPEN_GRAPH_TXT;
        return ERR_TO_OPEN_GRAPH_TXT;
    }

    if(node_ptr->left_child != nullptr)
    {
        fprintf(DumpFile, "\tnode_%p:f0 -> node_%p:here[color=\"blue\", label = \"left_child\"];\n", node_ptr, node_ptr->left_child);
        print_tree_links(tree, node_ptr->left_child, DumpFile);
    }
    if(node_ptr->right_child != nullptr)
    {
        fprintf(DumpFile, "\tnode_%p:f1 -> node_%p:here[color=\"red\", label = \"right_child\"];\n", node_ptr, node_ptr->right_child);
        print_tree_links(tree, node_ptr->right_child, DumpFile);
    }

    return 0;
}

FILE* StartLog(void)
{
    char buff[30] = "";
    sprintf(buff, "cd %s; rm *.svg", NAME_DOT_FOLDER);
    system(buff);
    
    FILE* logfile = fopen(NAME_LOG_FILE, "w");
    fprintf(logfile, "--------------------------------Start Logging--------------------------------\n");
    return logfile;
}

void MakePngName(char* name, char num)
{
	sprintf(name, "%s/dump%03d.svg", NAME_DOT_FOLDER, num);
} 