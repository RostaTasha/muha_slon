#include <semaphore.h>
#include <fcntl.h>

int main(){
//sem_t * sem_open(const char * name, int flags);
//sem_t * sem_open(const char * name, int flags,mode_t perms,unsigned value);
sem_open("/test.sem",O_CREAT,0666,66);

}