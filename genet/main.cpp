#include <vector>
#include <cmath>
#include <string>
#include <cstring>
#include <iostream>
#include <array>
#include <algorithm>    // std::find
#include <fstream>      // std::ifstream
#include <cassert>
#include <stack>
#include <set>
#include <list>
using namespace std;


#define MAX_SIZE 100 /*maximum size of population*/
#define MAX_GEN 50 /*maximum number of generations*/










bool is_vowel(char codea){
        static const char vowels [] ={'a','e','i','o','u','y'};
        auto it  = find(vowels,vowels + 6, codea);
        return (it!=(vowels+6));
}





class element_chain {

public:

element_chain(int N_=0){
if (N_)
	visited = new bool[N_];

N=N_;
for (int i =0; i< N_; i++)
        visited[i]=false;
}

element_chain( const element_chain& other ){

N=other.N;
if (N){
el=other.el;
visited = new bool[N];
memcpy(visited,other.visited,N);
}



};


element_chain& operator = ( const element_chain& other ){
while (!el.empty())
	el.pop();
N=other.N;
delete [] visited;
if (N){
visited = new bool[N];
}
};


~element_chain(){
delete [] visited;
}

static int fitness(const vector<string> & ar_words,const string & ethalon, int num){

string code1=ar_words[num];
assert(code1.size()==ethalon.size());
int result=0;
for (int i =0; i< ethalon.size(); i++){
if (code1[i]==ethalon[i])
        result+=3;
else
        if (is_vowel(code1.at(i)) && is_vowel(ethalon.at(i)))
                result+=2;
        else
                if (is_vowel(code1.at(i)))
                        result+=1;
}

return result;
}

int  const give_birth( vector<string>  &  ar_words){
static int pos =-1;

for (int i =pos+1; i< ar_words.size(); i++){
if (!visited[i]) {
        int cnt=0;
                        for (int k=0; k < ar_words[i].length(); k++){
                                if (ar_words[i].at(k)==ar_words[el.top()].at(k)) cnt++;
                        }

                        if (cnt==(ar_words[i].length()-1)) {
                                pos=i;
                                return i;
                        }
}
}
pos=-1;
return -1;
}

void next_generation(int num){
        visited[num]=true;
        el.push(num);
}


const int get_size(){
 return el.size();
}

int get_elem(){
	int temp = el.top();
	el.pop();
	return temp;
}


private:
stack<int> el;
bool * visited;
int N;
};


struct association{
	association(int n,list<element_chain>::iterator & i) : num(n), el_p(i) {}
	association(){num=-1; }

	int num;
	list<element_chain>::iterator el_p;
};



void sort(vector<association>  & candidates, const vector<string> & ar_words, const string & eth){
        std::sort (candidates.begin(), candidates.end(), [& ](const association & a, const association & b) -> bool{
                return (element_chain::fitness(ar_words,eth,a.num)>element_chain::fitness(ar_words,eth,b.num));
        }
        );
}





int main(){



vector<string> ar_words;
string start_word;
string end_word;
cin>>start_word>>end_word;


ifstream infile("B:/Eclipse/workspace/3dgr2/Debug/dict.txt");


string ttemp;
while (infile >> ttemp){
        if (ttemp.length()==start_word.length())        ar_words.push_back(ttemp);
        }
infile.close();

size_t tree_size = ar_words.size();



auto it = find(ar_words.begin(), ar_words.end(), start_word);
list<element_chain>::iterator target_it;
int start_num=it- ar_words.begin();

list<element_chain> se;
element_chain temp(tree_size);
temp.next_generation(start_num);

se.push_back(temp);

int num_elem=1;
int step_cnt=0;
int old_size=0;

bool choose=0;
association t;

while(step_cnt<=MAX_GEN)
{

	vector<association> children;

	for (auto it = se.begin(); it!=se.end();it++){
			int temp;
			do{
				temp =(*it).give_birth(ar_words);
				if (temp>=0) children.push_back(association(temp,it));
			} while(temp>=0);
	}



//	cout<<children.size()<<endl;
	sort(children, ar_words, end_word);
	while(children.size()>MAX_SIZE){
		children.pop_back();
	}

	old_size = se.front().get_size();



	while(children.size()!=0){
		//cout<<"cur "<<children.back().el_; p->get_size()<<endl;
		t = children.back();
		if (t.el_p->get_size()==old_size){
			t.el_p->next_generation(t.num);
			choose=0;
		//	cout<<"OKI DOKI"<<endl;
		} else {
			element_chain tt (*(t.el_p));
			tt.get_elem();
			tt.next_generation(t.num);
			se.push_back(tt);
			choose=1;
		}
	children.pop_back();

	if (ar_words[t.num]==end_word){
		cout<<"Found word!!!"<<endl;
		goto end;
		}
	}




/*	remove_if(se.begin(),se.end(),[& ](element_chain & a){
		return ( (a.get_size())!=(old_size+1) );
	} );*/

int size=se.size();
auto it = se.begin();
for (int i=0;((i<size) && (it!=se.end())); i++){
	if ((it->get_size())==(old_size)){
		it=se.erase(it);

	}else{
		it++;
	}

}
//cout<<"finish"<<se.size()<<endl;



	step_cnt++;
}


end:
if (!se.empty()){
element_chain chain = (choose==1) ? se.back() : *(t.el_p);

while (chain.get_size()!=0) {
	cout<<ar_words[chain.get_elem()]<<endl;
}
}



}





