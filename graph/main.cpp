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

//defines
#define DICT_PATH "./dict.txt"
#define WORDS_PATH "./words.txt"


//local functions
void 		add_to_dict(std::map<std::pair<wstring,int>,vector<int>> & dict, int & k, wstring & word);
vector<int> 	search_algo(vector<vector<size_t>> & graph,int & start_index, int & end_index);



int main(){
std::locale l(getenv("LANG"));
std::locale::global(l);
locale loc("");


 
wstring start_word; 	// muha
wstring end_word; 	// slon



wifstream infilew(WORDS_PATH);
wifstream infile(DICT_PATH);
infilew.imbue(loc);
infile.imbue(loc);
std::wcout.imbue(loc);

if (infilew.fail()){
	wcout<<L"Ошибка открытия файла слов. Попробуйте еще раз. Выход..."<<endl;
	return -1;
}

if (!(infilew>>start_word) ||  !(infilew>>end_word)) {
wcout<<L"Ошибка чтения слов из файла"<<endl;
}

start_word.erase(0,1); //hack. 


wcout<<L"Первое слово "<<start_word<<endl;
wcout<<L"Второе слово "<<end_word<<endl;

infilew.close();


if (start_word.length()!=end_word.length()) {
	wcout<<L"Длины слов не сопадают. Попробуйте еще раз. Выход..."<<endl;
	return -1;
}


if (infile.fail()){
	wcout<<L"Ошибка открытия файла словаря. Попробуйте еще раз. Выход..."<<endl;
	return -1;
}
vector<wstring> ar_words; // vector containing all words of target length

// read from file all words with the target length
int k=-1; // array index counter
wstring ttemp;
std::map<std::pair<wstring,int>,vector<int>> dict; // keys are shortenings; values are words from dict

while (infile >> ttemp){

	if (ttemp.length()==start_word.length())
	{
		ar_words.push_back(ttemp);
		++k;
		add_to_dict(dict, k, ttemp);

	}
	}

infile.close();



auto it = find (ar_words.begin(),ar_words.end(), end_word);
if (it == ar_words.end()){
	wcout<<L"Слова "<<end_word<<L" нет в словаре. Попробуйте еще раз. Выход..."<<endl;
	return -1;
}



// if start word not found then add it to dictionary
++k;
it = find (ar_words.begin(),ar_words.end(), start_word);
if (it == ar_words.end()){
	ar_words.push_back(start_word);
	add_to_dict(dict, k, start_word);
}


// create graph
size_t tree_size = ar_words.size();
vector<vector<size_t>> graph;
graph.resize(tree_size);
for (int j =0; j< tree_size; j++){

	for (int i=0; i<start_word.length(); i++){
			wstring temp = ar_words[j];
			temp.erase(i,1);
			vector<int> links = dict[std::pair<wstring,int>(temp,i)];
			for (int k=0; k< links.size(); k++) {
				 graph[j].push_back(links[k]);
			}
	}

}


// start search

int index, index1;
it = find (ar_words.begin(),ar_words.end(), start_word);
index=it-ar_words.begin();
it = find (ar_words.begin(),ar_words.end(), end_word);
index1=it-ar_words.begin();

vector<int> init_seq;
if (index1!=index) init_seq = search_algo(graph, index, index1);
else init_seq.push_back(index); //trivial case



if (init_seq.empty()){
	wcout<<L"Не существует цепочки слов от "<<start_word<<L" до "<<end_word<<L". Попробуйте еще раз. Выход..."<<endl;
	return -1;
}else{
	wcout<<L"Ура! Цепочка слов от "<<start_word<<L" до "<<end_word<<L" была найдена."<<endl;
	wcout<<"\n\t";
	for (auto it1 = init_seq.begin(); it1 !=init_seq.end();++it1){
		if (it1 != init_seq.begin()) wcout<<"->";
		wcout<<ar_words[*it1];
	}
	wcout<<endl;
}


return 0;
}




// function which adds new info to map of shortenings and indexes of words having this shortening

void add_to_dict(std::map<std::pair<wstring,int>,vector<int>> & dict, int & k, wstring & word){
	for (int i=0; i<word.length(); i++){
		wstring temp = word;
		temp.erase(i,1); // create shortening
		if ( dict.find(std::pair<wstring,int>(temp,i)) == dict.end())  {
			dict.insert(
					std::pair<std::pair<wstring,int>,vector<int>>
																(std::pair<wstring,int>(temp,i),{k})
					);
		} else{
			dict[std::pair<wstring,int>(temp,i)].push_back(k);

		}

	}
}




// search the shortest path in the graph
vector<int> search_algo(vector<vector<size_t>> & graph,int & start_index, int & end_index){

	// I use bfs algorithm to find the path from start_word to end_word if exists

	size_t tree_size = graph.size();


	bool * visited = new bool[tree_size]; // array containing info if the  point was already visited
	int *  distance = new int[tree_size]; // array containing info about the path from start_word to current
	queue<size_t> q;
	size_t index, index1;
	vector<int> init_seq;

	for (int p = 0; p<tree_size; p++){
		visited[p]=false;
		distance[p]=UINT_MAX;
	}


	q.push(start_index);
	visited[start_index]=true;
	distance[start_index]=0;


	while (!(q.empty())){
		index = q.front();
		q.pop();

		for (int k=0; k<(graph[index]).size(); k++){
			index1= graph[index][k];
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
	return init_seq;

	end:



	init_seq.push_back(index1);


	while (distance[index1]!=0){

		for (int k =0; k<graph[index1].size();k++){
			if (distance[ graph[index1][k] ]==(distance[index1]-1)){
				index1= graph[index1][k];
				break;
			}

		}
		init_seq.push_back(index1);
	}

	delete [] visited;
	delete [] distance;
	std::reverse(init_seq.begin(),init_seq.end());
	return init_seq;
}
