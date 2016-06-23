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

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

struct tree {
  int data;
  struct tree* left;
  struct tree* right;
};

void insert(struct tree** rootRef, int data);
void printSorted(struct tree* root);
void bst_print_dot(struct tree* tree, FILE* stream);


void insert(struct tree** rootRef, int data)
{
  struct tree* newtree=(struct tree*)malloc(sizeof(struct tree));

  if (*rootRef==NULL)
  {
    newtree->data=data;
    newtree->left=NULL;
    newtree->right=NULL;
    *rootRef=newtree;
  }
  else
  {
    if (data<=(*rootRef)->data)
      insert(&((*rootRef)->left),data);
    else
      insert(&((*rootRef)->right),data);
  }
}

void printSorted(struct tree* root)
{
  if (root==NULL)
  {
    return;
  }
  else
  {
    printSorted(root->left);
    printf("%d ",root->data);
    printSorted(root->right); 
  }
}

/*
  Used by: bst_print_dot_aux()

  Prints the null trees
  -creates unique null#
  -creates an edge from tree# to null#
*/
void bst_print_dot_null(int curtree, int nullcount, FILE* stream)
{
  fprintf(stream,"    null%d [shape=point];\n",nullcount);
  fprintf(stream,"    tree%d -> null%d;\n", curtree, nullcount);
}

/*
  Used by: bst_print_dot()
     Uses: bst_print_dot_null()

  Recursive calls itself to generate left and right branches
  -creates a label=# for each tree based on its data
  -creates a tree#->tree# if it is not a leaf tree else tree#->null# 
*/
void bst_print_dot_aux(struct tree* tree, int* nullcount, int* treecount, FILE* stream)
{
  int curtree=(*treecount)++;
  fprintf(stream,"    tree%d [label=\"%d\"];\n",curtree,tree->data);

  if (tree->left!=NULL)
  {
    fprintf(stream,"    tree%d -> tree%d;\n", curtree, *treecount);
    bst_print_dot_aux(tree->left, nullcount, treecount, stream); 
  }
  else
  {
    bst_print_dot_null(curtree, (*nullcount)++, stream);
  }

  if (tree->right!=NULL)
  {
    fprintf(stream,"    tree%d -> tree%d;\n", curtree, *treecount);
    bst_print_dot_aux(tree->right, nullcount, treecount, stream);
  }
  else
  {
    bst_print_dot_null(curtree, (*nullcount)++, stream);
  }
}

/*
  Generating a dot file from a binary search tree (BST)
  Reimplementation in C from examples on BST plots using Graphviz
    -- by Swee Mok, on Dec 14, 2015

  Original idea and C & C# codes were posted at websites:
    http://eli.thegreenplace.net/2009/11/23/visualizing-binary-trees-with-graphviz
    -- by Eli Bendersky
    http://codepad.org/iWi3uqeV
    -- by Mr.eXoDia

  ___________________________________________________________
 
  This is the entry point for generating dot file using a BST
  -uses bst_print_dot_aux() to print tree#->tree#
  -used bst_print_dot_null() to print tree#->null#
*/
void bst_print_dot(struct tree* tree, FILE* stream)
{
  int nullcount=0;
  int treecount=0;

  fprintf(stream,"digraph BinaryTree \{");
  if (tree!=NULL && tree->left==NULL && tree->right==NULL)
    fprintf(stream,"    \"%d\";\n",tree->data);
  else
    bst_print_dot_aux(tree,&nullcount,&treecount,stream);
  fprintf(stream,"}\n");
}  