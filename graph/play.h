#ifndef PLAY_H

#define PLAY_H

// libs

#include <vector>
#include <cmath>
#include <cstring>
#include <iostream>
#include <algorithm>    // std::find
#include <fstream>      // std::ifstream
#include <queue>
#include <map>
#include <list>
#include <climits>

// namespace
using namespace std;

// search the path in the WordsGraph
class SearchAlgo
{
  public:    
    virtual ~SearchAlgo() {};
    virtual vector<int> search(vector<vector<size_t>> & WordsGraph,int & start_index, int & end_index) = 0;
};

class BFS : public SearchAlgo
{
  public:
    vector<int> search(vector<vector<size_t>> & WordsGraph,int & start_index, int & end_index){
	
	
		size_t TreeSize = WordsGraph.size();
	
	
		bool * visited = new bool[TreeSize]; // array containing info if the  point was already visited
		int *  distance = new int[TreeSize]; // array containing info about the path from StartWord to current
		queue<size_t> q;
		size_t index, index1;
		vector<int> InitSeq;
	
		for (int p = 0; p<TreeSize; p++){
			visited[p]=false;
			distance[p]=UINT_MAX;
		}
	
	
		q.push(start_index);
		visited[start_index]=true;
		distance[start_index]=0;
	
	
		while (!(q.empty())){
			index = q.front();
			q.pop();
	
			for (int k=0; k<(WordsGraph[index]).size(); k++){
				index1= WordsGraph[index][k];
				if (visited[index1]==false){
					distance[index1]=distance[index]+1;
					if (index1  == end_index ) goto end;
	
					q.push(index1);
					visited[index1]=true;
				}
			}
	
		}
	
	
		delete [] visited;
		delete [] distance;
		return InitSeq;
	
		end:
	
	
	
		InitSeq.push_back(index1);
	
	
		while (distance[index1]!=0){
	
			for (int k =0; k<WordsGraph[index1].size();k++){
				if (distance[ WordsGraph[index1][k] ]==(distance[index1]-1)){
					index1= WordsGraph[index1][k];
					break;
				}
	
			}
			InitSeq.push_back(index1);
		}
	
		delete [] visited;
		delete [] distance;
		std::reverse(InitSeq.begin(),InitSeq.end());
		return InitSeq;
	}
};



class Searcher 
{
  public:
    Searcher( SearchAlgo* se): p(se) {}
   ~Searcher() { delete p; }
    vector<int> search( vector<vector<size_t>> & WordsGraph,int & start_index, int & end_index ) {
      return p->search(WordsGraph,start_index, end_index);
    }
  private:
    SearchAlgo* p;
};


#endif