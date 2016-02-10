#include <stdio.h>                                                              
#include <sys/types.h>                                                          
#include <sys/shm.h>                                                            
#include <stdlib.h>                                                             
                                                                                
int main(){                                                                     
key_t key = ftok("/tmp/mem.temp", 1);                                           
unsigned int size = 2*1024*1024; 
unsigned int sizem  = 1024*1024;                                               
int shmid = shmget(key,size,0666|IPC_CREAT);                                    
printf("\nshmid %d\n",shmid);
if (shmid==-1) {
printf("Error!!!\n");
return -1;
}                                                   
void  * start_addr  = shmat(shmid,NULL,0);                                      
int i =0;                                                                       
for (i=0; i<sizem;i++){                                                     
        *((char *)(start_addr)+i)=42;                                           
}                                                                               
return 0;                                                                       
                                                                                
}                                                                               
       