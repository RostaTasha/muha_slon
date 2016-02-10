#include <stdio.h>
#include <sys/types.h>
#include <sys/shm.h>

int main(){
key_t key = ftok("/tmp/mem.temp", 1);
int shmid = shmget(key,2*1024*1024,IPC_CREAT);
void  * start_addr  = shmat(shmid,NULL,0);
int i =0;
for (i=0; i<1024*1024;i++){
	*((char *)(start_addr)+i)=42;
}
return 0;

}