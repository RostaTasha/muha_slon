#include <stdio.h> 
#include <unistd.h>                                                             
#include <iostream>                                                             
#include <string>                                                               
#include <vector>                                                               
#include <sstream> 
#include <stdlib.h> 
#include <fcntl.h>
                                                                                
int main(){                                                                     
	std::string temp;                                                         
	std::vector<std::string> vect;                                                  
	std::getline(std::cin,temp);                                                    
	std::stringstream strm(temp);                                                   
                                                                                
                                                                                
	while (std::getline(strm,temp,'|')){                                           
		vect.push_back(temp);                                                          
	}                                                                               
                                                                                
	int pfd[2];
    	
for (int i =0; i< vect.size()-1; i++){
    pipe(pfd);
	if (!fork()){ //child
	
		close (STDOUT_FILENO); //close stdout
		close(STDIN_FILENO); //close stdin
		dup2(pfd[1],STDOUT_FILENO); //redirect
		dup2(pfd[0],STDIN_FILENO); //redirect;
		close(pfd[1]); //old fd
		close(pfd[0]); // close old fd
		execlp(vect[i].c_str(),vect[i].c_str(),NULL); 
	}
}

pipe(pfd);
close(STDIN_FILENO); //close stdin
dup2(pfd[0],STDIN_FILENO); //redirect;
close(pfd[0]); // close old fd
int f = open("result.out",O_RDWR,0666);
dup2(f,STDOUT_FILENO);
close(f); // close old fd
execlp(vect[vect.size()-1].c_str(),vect[vect.size()-1].c_str(),NULL);
/*for (int i =0; i< vect.size(); i++){                                             
	pipe(fd);
	close(stdin);
	dub3(fd[1],0,O_CLOEXEC); // 0 - stdin
	pid_t pid = fork();
	if (pid){  //child                                                          
     close(fd[1]); // close output;
	 std::cin>>fd[0];
	 exec(vect[i].c_str());                                                                           
	}else { //parent
	close(fd[0]); //close input
	
	}
*/
}