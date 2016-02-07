#include <stdio.h> 
#include <unistd.h>                                                             
#include <iostream>                                                             
#include <string>                                                               
#include <vector>                                                               
#include <sstream> 
#include <stdlib.h> 
#include <fcntl.h>
#include <algorithm>
#include <cstring>
#include <sys/wait.h>
                                                                                

void command_arg_parser(std::string str,  std::vector<std::string> &  arg){
std::string temp1;      
std::stringstream strm(str);

 while (strm>>temp1){                                           
		arg.push_back(temp1);                                                          
 } 
 

}




int main(){ 
	remove("./result.out");                                                                    
	std::string temp;                                                         
	std::vector<std::string> vect;
	std::string string_arg; 
	std::getline(std::cin,temp);                                                    
	std::stringstream strm(temp);  
	int pfd[2];
                                                                                
                                                                                
        	while (std::getline(strm,temp,'|')){                                           
        		vect.push_back(temp);                                                          
        	} 
			
			
  int * pipefds = new int  [vect.size()*2];  	
/* parent creates all needed pipes at the start */
for (int i =0; i<vect.size(); i++){
	if (pipe(pipefds+2*i)<0){
	std::cerr<<"Could not pipe"<<std::endl;
	exit(EXIT_FAILURE);
	}
}     
     
    	
for (int i =0; i< vect.size(); i++){
	
	int childPid = fork();
	if (childPid==0){ //child
	
		if (i!=0){
			   close(STDIN_FILENO); //close stdin
				if (dup2(pipefds[2*((i-1))],STDIN_FILENO)<0) {/*redirect; // 0 or 2 fd*/
				std::cerr<<"Error dub2 stdin on it "<<i<<std::endl;
				exit(EXIT_FAILURE);
			}

		}
		if (i!=vect.size()-1){
			   close (STDOUT_FILENO); //close stdout
				if (dup2(pipefds[(i)*2+1],STDOUT_FILENO)<0) {/*redirect 1 or 3 fd*/
				std::cerr<<"Error dub2 stdout on it "<<i<<std::endl;
				exit(EXIT_FAILURE);
				}
			//fprintf(stderr,"redirecto %d on it %d\n",(i)*2+1,i);
		} else {
		int f = open("./result.out",O_CREAT|O_RDWR,0666);
		dup2(f,STDOUT_FILENO);
		close(f); // close old fd	
		}
		
			for (int k =0; k< vect.size(); k++){
			close(pipefds[k]);
			}
		
		
		
		std::vector<std::string> arg;
		command_arg_parser(vect[i], arg);
		



		char  * arg_c[64];
		char line[100];
		int cnt=0;
		for (int k =0; k< arg.size();k++){
			std::strncpy(line+cnt,arg[k].c_str(),arg[k].size()+1);
			arg_c[k]=line+cnt;
			cnt+=arg[k].size();
			*(line+cnt)='\0';
			cnt+=1;
			}

			arg_c[arg.size()]=NULL;

		if (execvp(*arg_c,arg_c)<0){
			std::cerr<<"Error exec on it "<<i<<std::endl;
			exit(EXIT_FAILURE);
		}
		break;
	}
	
	//while ((childPid = wait(0)) > 0);
	
	}
	
for (int k =0; k< vect.size(); k++){
close(pipefds[k]);
}

wait(0);

}
