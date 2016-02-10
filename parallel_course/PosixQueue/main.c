#include <stdio.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <mqueue.h>
#define SIZE 100
int main(){
struct mq_attr attr;
attr.mq_flags = 0;
attr.mq_maxmsg = 10;
attr.mq_msgsize = SIZE;
attr.mq_curmsgs = 0;
mqd_t mqdes =  mq_open("/test.mq",O_CREAT | O_RDWR,0666,&attr);
char buf[SIZE+1];
int msg_size = mq_receive( mqdes, buf, 100, NULL );
buf[msg_size]='\0';
FILE * f = fopen("/home/box/message.txt","w");
fwrite(buf,1,msg_size, f);
fclose(f);
mq_close(mqdes);
mq_unlink("/test.mq");


}
