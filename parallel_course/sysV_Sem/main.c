#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/sem.h>
#include <stdio.h>


int main(){
key_t  key = ftok("/tmp/sem.temp", 1); 
//int semid =  semget(key_t key, int nsems, int semflg); 
int semid = semget(key, 16, 0666|IPC_CREAT);
int i;

struct sembuf op[16];
for (i =0; i<16; i++){
op[i].sem_num = i; //signifies 0th semaphore
op[i].sem_op = 1; //reduce the semaphore count to lock
op[i].sem_flg = 0; //wait till we get lock on semaphore
}
semop(semid, op, 16);
}