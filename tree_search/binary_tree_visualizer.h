/*
  Generate a dot file from a binary search tree (BST).
  Reimplementation in C from examples on BST plots using Graphviz
  that will correctly plot repeated tree values in a BST.
    -- by Swee Mok, on Dec 14, 2015

  Simple Demo to:
    -- Create a BST
    -- Print a sorted BST
    -- Generate a dot file for visualization using Graphviz

  Original idea and C & C# codes were posted at websites:
    http://eli.thegreenplace.net/2009/11/23/visualizing-binary-trees-with-graphviz
    -- by Eli Bendersky
    http://codepad.org/iWi3uqeV
    -- by Mr.eXoDia
*/


void bst_print_dot_null(int curtree, int nullcount, FILE* stream);
void bst_print_dot_aux(struct tree* tree, int* nullcount, int* treecount, FILE* stream);
void bst_print_dot(struct tree* tree, FILE* stream);