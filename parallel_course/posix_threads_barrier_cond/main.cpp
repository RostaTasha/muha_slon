#include <unistd.h> //sleep
#include <pthread.h>
#include <iostream>

pthread_mutex_t 	mutex;
pthread_cond_t cond;
pthread_barrier_t barrier;


bool condition=0;

void* func(void *arg){
std::cout<<"started cond mutex"<<std::endl;
pthread_mutex_lock(&mutex);
while (!condition)
	pthread_cond_wait(&cond, &mutex);
std::cout<<"ended cond mutex"<<std::endl;
pthread_mutex_unlock(&mutex);

 }
 
 
 void* func1(void *arg){
std::cout<<"started barrier"<<std::endl;
pthread_barrier_wait(&barrier);
std::cout<<"ended barrier"<<std::endl;


 }
 


int main(){
pthread_t pth_id[4];

pthread_mutex_init(&mutex,NULL);
pthread_cond_init(&cond,NULL);
//barrier for 2 threads
pthread_barrier_init(&barrier,NULL,2);






pthread_mutex_lock(&mutex);



// this threads waits for mutex
pthread_create(&pth_id[0], NULL, &func, NULL);
// this threads waits for barrier
pthread_create(&pth_id[1], NULL, &func1, NULL);



std::cout<<"started sleeping"<<std::endl;
sleep(5);
pthread_barrier_wait(&barrier);
condition=1;
std::cout<<"ended sleeping"<<std::endl;
pthread_cond_signal(&cond);
pthread_mutex_unlock(&mutex);


pthread_cond_destroy(&cond);
pthread_barrier_destroy(&barrier);
pthread_mutex_destroy(&mutex);

pthread_join(pth_id[0], NULL);


return 0;
}