// namespace
using namespace std;

#include "play.h"


//local functions
void 		add_to_dict(std::map<std::pair<wstring,int>,vector<int>> & ShortWordDict, int & k, wstring & word);


int main(){

locale l(getenv("LANG"));
locale::global(l);


string DictPath;
string WordPath;

wcout<<L"Путь к файлу словаря"<<endl;
cin>>DictPath;
wcout<<L"Путь к файлу слов"<<endl;
cin>>WordPath;
 
 
wstring StartWord; 	// muha
wstring EndWord; 	// slon



wifstream WFile(WordPath.c_str());
wifstream DFile(DictPath.c_str());


if (WFile.fail()){
	wcout<<L"Ошибка открытия файла слов. Попробуйте еще раз. Выход..."<<endl;
	return -1;
}

if (!(WFile>>StartWord) ||  !(WFile>>EndWord)) {
wcout<<L"Ошибка чтения слов из файла"<<endl;
}

StartWord.erase(0,1); //hack. 


wcout<<L"Первое слово "<<StartWord<<endl;
wcout<<L"Второе слово "<<EndWord<<endl;

WFile.close();


if (StartWord.length()!=EndWord.length()) {
	wcout<<L"Длины слов не сопадают. Попробуйте еще раз. Выход..."<<endl;
	return -1;
}


if (DFile.fail()){
	wcout<<L"Ошибка открытия файла словаря. Попробуйте еще раз. Выход..."<<endl;
	return -1;
}
vector<wstring> WordArray; // vector containing all words of target length

// read from file all words with the target length
int k=-1; // array index counter
wstring ttemp;
std::map<std::pair<wstring,int>,vector<int>> ShortWordDict; // keys are shortenings; values are words from dictionary

while (DFile >> ttemp){

	if (ttemp.length()==StartWord.length())
	{
		WordArray.push_back(ttemp);
		++k;
		add_to_dict(ShortWordDict, k, ttemp);

	}
	}

DFile.close();

Searcher* sch = new Searcher( new BFS); //searcher algo
  

auto it = find (WordArray.begin(),WordArray.end(), EndWord);
if (it == WordArray.end()){
	wcout<<L"Слова "<<EndWord<<L" нет в словаре. Попробуйте еще раз. Выход..."<<endl;
	return -1;
}



// if start word not found then add it to dictionary
++k;
it = find (WordArray.begin(),WordArray.end(), StartWord);
if (it == WordArray.end()){
	WordArray.push_back(StartWord);
	add_to_dict(ShortWordDict, k, StartWord);
}


// create WordsGraph
size_t TreeSize = WordArray.size();
vector<vector<size_t>> WordsGraph;
WordsGraph.resize(TreeSize);
for (int j =0; j< TreeSize; j++){

	for (int i=0; i<StartWord.length(); i++){
			wstring temp = WordArray[j];
			temp.erase(i,1);
			vector<int> links = ShortWordDict[std::pair<wstring,int>(temp,i)];
			for (int k=0; k< links.size(); k++) {
				 WordsGraph[j].push_back(links[k]);
			}
	}

}


// start search

int index, index1;
it = find (WordArray.begin(),WordArray.end(), StartWord);
index=it-WordArray.begin();
it = find (WordArray.begin(),WordArray.end(), EndWord);
index1=it-WordArray.begin();

vector<int> InitSeq; // final sequence of indexes from WordArray 
if (index1!=index) InitSeq = sch->search(WordsGraph, index, index1);
else InitSeq.push_back(index); //trivial case



if (InitSeq.empty()){
	wcout<<L"Не существует цепочки слов от "<<StartWord<<L" до "<<EndWord<<L". Попробуйте еще раз. Выход..."<<endl;
	return -1;
}else{
	wcout<<L"Ура! Цепочка слов от "<<StartWord<<L" до "<<EndWord<<L" была найдена."<<endl;
	wcout<<"\n\t";
	for (auto it1 = InitSeq.begin(); it1 !=InitSeq.end();++it1){
		if (it1 != InitSeq.begin()) wcout<<"\n\t";
		wcout<<WordArray[*it1];
	}
	wcout<<endl;
}

delete sch;

return 0;
}




// function which adds new info to map of shortenings and indexes of words having this shortening

void add_to_dict(std::map<std::pair<wstring,int>,vector<int>> & ShortWordDict, int & k, wstring & word){
	for (int i=0; i<word.length(); i++){
		wstring temp = word;
		temp.erase(i,1); // create shortening
		if ( ShortWordDict.find(std::pair<wstring,int>(temp,i)) == ShortWordDict.end())  {
			ShortWordDict.insert(
					std::pair<std::pair<wstring,int>,vector<int>>
																(std::pair<wstring,int>(temp,i),{k})
					);
		} else{
			ShortWordDict[std::pair<wstring,int>(temp,i)].push_back(k);

		}

	}
}



