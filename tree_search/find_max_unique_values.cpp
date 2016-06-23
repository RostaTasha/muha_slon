#include <stdio.h>
#include <cstdlib>
#include <set>
#include <stack>
#include <ctime>
#include <iostream>

extern "C" {
#include "binary_tree_visualizer.h"
}

#define MAX_PATH 1000
#define MIN 3
struct tree {
	tree(int ii=0, tree *ll = NULL ,tree *rr = NULL): i(i), l(ll),r(rr){};
	
	int i;
	tree *l;
	tree *r;
};

struct tree_level {
	tree_level(tree *nnode = NULL, int llevel = 0, bool vvisited = false): node(nnode), level(llevel),visited(vvisited){};
	
	tree *node;
	int level; /* holds the level of the vertex in the tree */
	bool visited; /* for depth-first_search */
};

tree* generateTree (int depth);
int func(tree *P);

int main(void) {    
    std::srand(time(NULL));
	tree * root = generateTree(10); /* generate tree */
	printf("program result is %d\n", func(root));  /* answer to the question. Max number of unique values  on the paths from the tree*/
	
	/* visualization part for self-checking See futher details in binary_tree_visualizer.c*/
	char* dotFilename = "bstGraph.dot"; /*file which will hold the data for tree visualization*/
	FILE *fp = fopen(dotFilename,"w");
	if (fp == NULL) {
		std::cout<<"Error opening file "<<dotFilename<<std::endl;
		return -1;
	}
	bst_print_dot(root,fp); /* generate file*/
	fclose(fp);
	
	return 0;
}

tree* generateTree (int depth) {
    
	if (depth <= 0) {
		return NULL;
	}	
	int i =std::rand()%10;
    tree*  currentNode = new tree();
    currentNode->i = i;
	/*left*/
    if ( (rand()%2) || (depth < MIN) ) {
		currentNode->l = generateTree(depth-1);
		}
    /*right*/
	if ( (rand()%2) || (depth < MIN) ) {
		currentNode->r = generateTree(depth-1);
		}
    return currentNode;
}

/* function  makes Depth-first search and finds the max  number of the unique values for the path of the tree */

int func(tree *P) {
	int max_result = 0; /* holds the maximum number of unique values */
	int array[MAX_PATH]; /* the number in array corresponds to the level number in the tree */
	std::stack<tree_level> st; /* stack */
	tree_level base(P,0,false); 
	st.push(base); /* push root to stack */
	int array_pointer = 0;

	while (!st.empty()) {
		tree_level node_level = st.top();
		st.pop();
		if (node_level.node != NULL) {
			array_pointer = node_level.level;
			array[array_pointer] = node_level.node->i; /* value which helds vertex */
			if (node_level.visited == false) {
				node_level.visited = true;
				tree_level left(node_level.node->l,node_level.level+1,false);
				tree_level right(node_level.node->r,node_level.level+1,false);
				st.push(left);
				st.push(right);
			}
			
		}else{
		/* end vertex. Stop and calculate number of unique values.  */
			std::set<int> unique; /* unique values */
			array_pointer = node_level.level; /* level  of the end vertex in the tree. */
			
			for (int i =0; i < array_pointer; i++) {
				unique.insert(array[i]);
			}
			int temp = unique.size();
			
			if (temp > max_result) {
				max_result = temp; // update max number of unique values on the path
			}
		}
	}	
	
	return max_result;
}




