### Typical performance bottlenecks.

Localisation of bottlenecks in the code can be done with the help of profiler: determine the most time-consuming parts not forgetting about Ahmdal’s Law. Next, these code parts should be analyzed to figure out the ways of accelerating it. 
\
\
The typical performace bottlenecks are the following:
* algorithm-bound 
	* The chosen algorithm is not the optimal one.\
	Solution: calculate the complexity of the algorithm. Choose the better one if it exists. 
* memory-bound 
	* Random memory access causes cache misses.
    For example, not optimal order in accessing 2d-array elements,  using lists instead of vectors, etc. \
	Solution: follow spatial locality principle. Try to access elements in the same order as they are stored in memory. 
	* Unnecessary copy operations. \
	Solution: transfer the values by reference where possible. 
	* Unnecessary function calls. \
	Solution: try to keep thing local. If possible, save the result of some function to the local variable and then operate with it. 
	
* CPU-bound 
	* Too many threads for this CPU, high context-switch rate. \
	Solution: in case of multithreaded program the number of threads should be chosen in accordance with the number of available CPU cores. The threads should not be awakened without necessity.  
	* Complex if-statements cause a lot of jump operations. \
	Solution:  Put the most frequent cases on the top positions.
	* Conditions in if-statements with poorly predictable sequences may cause slowdown due to mispredictions of branch-predictor. \
	Solution: try to avoid such things.	
	


 
 