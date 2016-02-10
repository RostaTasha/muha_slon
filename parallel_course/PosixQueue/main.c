#include <stdio.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <mqueue.h>

int main(){

mqd_t mqdes =  mq_open("/test.mq",O_CREAT | O_RDWR,0666,NULL);
char buf[9];
int msg_size = mq_receive( mqdes, buf, 9, NULL );
buf[msg_size]='\0';
FILE * f = fopen("/home/box/message.txt","w");
fwrite(buf,1,msg_size, f);
fclose(f);
mq_close(mqdes);
mq_unlink("/test.mq");


}
