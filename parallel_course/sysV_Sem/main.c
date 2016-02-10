#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/sem.h>
#include <stdio.h>


int main(){

key_t  key = ftok("/tmp/sem.temp", 1); 
//int semget(key_t key, int nsems, int semflg); 
semget(key, 16, 0666|IPC_CREAT);
struct sembuf op[16];
int i;
for (i =0; i<16; i++){
  //operation for 0th semaphore
  op[i].sem_num = i; //signifies 0th semaphore
  op[i].sem_op = -1; //reduce the semaphore count to lock
  op[i].sem_flg = 0; //wait till we get lock on semaphore
}

}