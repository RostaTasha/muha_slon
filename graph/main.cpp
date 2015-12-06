#include <vector>
#include <cmath>
#include <string>
#include <cstring>
#include <iostream>
#include <array>
#include <algorithm>    // std::find
#include <fstream>      // std::ifstream
#include <queue>
#include <map>

using namespace std;



int main(){



vector<string> ar_words;
string start_word;
string end_word;
cin>>start_word>>end_word;


ifstream infile("B:/Eclipse/workspace/3dgr2/Debug/dict.txt");


string ttemp;
std::map<char,int> dict;
while (infile >> ttemp){
	if (ttemp.length()==start_word.length()) 	ar_words.push_back(ttemp);
	}
infile.close();

size_t tree_size = ar_words.size();



string temp_word;
auto it = find (ar_words.begin(),ar_words.end(), start_word);
vector<vector<size_t>> graph;
graph.resize(tree_size);


vector<vector<int>> codes;
codes.resize(tree_size);

for (int i =0; i< tree_size; i++) {
	codes[i].resize(start_word.length());
	for (int k = 0; k < start_word.length(); k++){
		codes[i][k]=ar_words[i].at(k);
	}
}


vector<int>  code_cur;

for (int i =0; i< tree_size; i++)
{
	code_cur = codes[i];
	for (int j =0; j< tree_size; j++)
	{
		int cnt=0;
		for (int k=0; k < start_word.length(); k++){
			if (code_cur[k]==codes[j][k]) cnt++;
		}

		if (cnt==start_word.length()-1) graph[i].push_back(j);
	}
}


cout<<"Graph created!"<<endl;
bool * visited = new bool[tree_size];
int *  distance = new int[tree_size];
for (int p = 0; p<tree_size; p++){
	visited[p]=false;
	distance[p]=0;
}
queue<size_t> q;
int index, index1;
it = find (ar_words.begin(),ar_words.end(), start_word);
index=it-ar_words.begin();
q.push(index);
visited[index]=true;
distance[index]=0;


while (!(q.empty())){
	index = q.front();
	//cout<<ar_words[index]<<endl;
	q.pop();

	for (int k=0; k<(graph[index]).size(); k++){
		index1= graph[index][k];
		if (visited[index1]==false){
			distance[index1]=distance[index]+1;
			if (ar_words[ index1 ] == end_word ){
				cout<<"Founded!"<<endl;
				goto end;
			}

			q.push(index1);
			visited[index1]=true;
		}
	}

}


end:

cout<<ar_words[index1 ]<<endl;

while (distance[index1]!=0){

	for (int k =0; k<graph[index1].size();k++){
		if (distance[ graph[index1][k] ]==(distance[index1]-1)){
			index1= graph[index1][k];
			break;
		}

	}

	cout<<ar_words[index1 ]<<endl;
}

}









