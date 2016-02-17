#include <pthread.h>


void* func(void *arg){

while(1){

}

}

int main(){
pthread_t pth_id;
pthread_create(&pth_id, NULL, &func, NULL);
pthread_join(pth_id, NULL);

return 0;
}