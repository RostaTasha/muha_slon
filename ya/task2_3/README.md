## Complexity
 * Solution 1  ~O(N^2*ln(N)) 
 * Solution 2  ~O(N^2*ln(N))
 * Solution 3  ~O(N*ln(N))
 
	In the first case the part of the vector is sorted on each iteration. According to the documentation [link](http://en.cppreference.com/w/cpp/algorithm/sort) the compexity of sort  function is \
O(N·log(N)) comparisions (on average in case of standart < C++11).  In case of large N's the sum(i*log(i)) from i = 1 to N can be estimated as the corresponding integral. So, the complexity in \
this case can be  estimated as O(N^2log(N))

	In the second case the std::partial_sort is called on every iteration of the cycle. According to the documentation [link](http://www.cplusplus.com/reference/algorithm/partial_sort/) the complexity of this function can be estimated \
as N*log(M), where N  is the distance between first and last, M is the distance between first and middle. So, the final complexity can be estimated as the correspinding  sum (i) from i = 1 to N which results in the \
~ O(N^2)
 
	In the third case multiset is used. The multisets are typically implemented as binary search trees. So, the complexity of constructing multiset for unordered sequence can be estimated as \
N*log(N). On each iteration of the algorithm erase and insert iteration are performed. The complexity of the code, which contains cycle, can be estimated similarly to the first case as the integral \
of ln(i) which is ~ O(ln(N)*N). The final complexity is ~O(ln(N)*N).

My solution, listed  in the file sol.cpp is based on the Kahan summation algorithm  [link](http://www.cplusplus.com/reference/algorithm/partial_sort/).\
The complexity of the proposed solution is ~O(N)
 
```cplusplus

 double sum1(std::vector& v)
{    
    if (v.empty()) {
        return 0.0;
    }
    for(size_t i = 0; i < v.size() - 1; ++i) {
        std::sort(v.begin()+i, v.end()); 				//(N-i) log (N-i)
        v[i+1] += v[i]; 								//1
    }
    return v.back();
}

// N^2*ln(N) 
 
double sum2(std::vector& v)
{    
    if (v.empty()) {
        return 0.0;
    }
    for(size_t i = 0; i < v.size() - 1; ++i) {
        std::partial_sort(v.begin() + i, v.begin() + i + 2, v.end()); 			//N-i
        v[i+1] += v[i]; 														//1
    }
    return v.back();
}

// (N)^2
 
double sum3(std::vector& v)
{    
    std::multiset set(v.begin(), v.end()); // N*ln(N)  multiset is intristically binary tree
    while (set.size() > 1) {
        std::multiset::const_iterator itA = set.begin();				//1
        std::multiset::const_iterator itB = ++set.begin();				//1
        double c = *itA + *itB;											//1
        set.erase(itA, itB);        									//1
        set.insert(c); 													//ln(i)
    }
    return !set.empty() ? *set.begin() 
                        : 0.0;
}

//N*ln(N)
 
``` 
 