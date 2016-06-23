## Problem:

Each node of binary tree has a corresponding value.  Find the maximum number of unique values on the path from root to the vertex.

## Solution:

The idea is the following:
 * use depth-first search to explore the tree
 * save values in the nodes on the path to array. Track the pointer to the level of current node
 * in case of vertex determine the number of unique values, which correspond to the current path
 
## Visualization
 
The program generates a file which holds the information about the tree stucture. Can be used for selfcontro. 
More information in binary_tree_visualizer.c 
 
## Compilation and run
 
#### To compile:
  * gcc -c binary_tree_visualizer.c -o visual.o
  * g++ -c find_max_unique_values.cpp -o find.o
  * g++ -o myapp  find.o visual.o
  
####  To run:
 * ./myapp  
 

