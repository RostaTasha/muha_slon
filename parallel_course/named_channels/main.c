#include <stdio.h> 
#include <unistd.h>
#include <stdlib.h> 
#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <limits.h>


int main(){
char * path_i = "/home/box/in.fifo";
char * path_o = "/home/box/out.fifo";
mkfifo(path_i, 0666);
mkfifo(path_o, 0666);
int f_i = open(path_i,O_NONBLOCK|O_RDONLY);
int f_o = open(path_o,O_WRONLY);
char temp[PIPE_BUF];
int i =0;
while(1){
	read(f_i, temp, PIPE_BUF);
	write(f_o, temp, PIPE_BUF);
}


}
