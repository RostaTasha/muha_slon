#include <unistd.h> //sleep
#include <pthread.h>

pthread_mutex_t 	mutex;
pthread_rwlock_t 	lock;
pthread_spinlock_t 	spin;

void* func(void *arg){
pthread_mutex_lock(&mutex);
 }
 
 void* func1(void *arg){
pthread_spin_trylock(&spin);
 }
 
  void* func2(void *arg){
pthread_rwlock_rdlock(&lock);
 }
 
  void* func3(void *arg){
pthread_rwlock_wrlock(&lock); 
 }

int main(){
pthread_t pth_id[4];

pthread_mutex_init(&mutex,NULL);
pthread_spin_init(&spin,PTHREAD_PROCESS_PRIVATE);
pthread_rwlock_init(&lock,NULL);

pthread_mutex_lock(&mutex);
pthread_spin_lock(&spin);
pthread_rwlock_rdlock(&lock); 		//read shared lock
pthread_rwlock_wrlock(&lock); 	//write exclusive lock


// this threads waits for mutex
pthread_create(&pth_id[0], NULL, &func, NULL);
// this thread waits  for spinlock
pthread_create(&pth_id[1], NULL, &func1, NULL);
// this thread waits  for spinlock
pthread_create(&pth_id[2], NULL, &func2, NULL);
// this thread waits  for spinlock
pthread_create(&pth_id[3], NULL, &func3, NULL);


sleep(20);

pthread_spin_unlock(&spin);
pthread_mutex_unlock(&mutex);
pthread_rwlock_unlock(&lock);
pthread_mutex_destroy(&mutex);
pthread_spin_destroy(&spin);
pthread_rwlock_destroy(&lock);
pthread_join(pth_id[0], NULL);
pthread_join(pth_id[1], NULL);
pthread_join(pth_id[2], NULL);
pthread_join(pth_id[3], NULL);
return 0;
}