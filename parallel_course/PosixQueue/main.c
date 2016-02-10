#include <stdio.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <mqueue.h>

int main(){

mqd_t mqdes =  mq_open("/test.mq",O_CREAT | O_RDONLY);
char buf[100];
int msg_size = mq_receive( mqdes, buf, 100, NULL );
FILE * f = fopen("/home/box/message.txt","w");
fwrite(buf,1,msg_size, f);
fclose(f);



}