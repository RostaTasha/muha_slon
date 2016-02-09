#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <stdio.h>
//msgctl(int msgq,int cmd,struct msgid_ds * data); //IPC_RMID удаление  IPC_STAT  статитсика IPC SET установление
// msgq - id of queue
// struct msgid_ds {
// struct ipc_perm{
//					key_t key;
//					ushort uid;  /*owner can change*/
//					ushort gid; /* can change */
//					ushort cuid;  creator
//					ushort cgid;
//					ushort mode; /* access mode can change */
//					ushort seq;  slot usage sequence number
//}
//struct msg *msg_first; first message on queue
//struct msg *msg_last; last message on queue
//time_t msg_stime /*last msgsnd time*/
//time_t msg_rtime /*last msgrcv time*/
//time_t msg_ctime /*last change time*/
//struct wait_queue *wwait; /* pointer into kernel wait queue*/
//struct wait_queue *rwait;  /* pointer into kernel wait queue*/
//ushort msg_cbytes;    /* sum of sizes of all messages */
//ushort msg_qnum;     /* number of messages currenly in queue*/
//ushort msg_qbytes;      /* max number of bytes on queue  can change*/
//ushort msg_lspid;       /* pid of last msgsnd The PID of the process who sent the last message.*/
 //ushort msg_lrpid;       /* last receive pid  The PID of the process who retrieved the last message.*/
//}


int main(){

struct message{
	long mtype;
	char mtext[80];
};

int q_id = ftok("/tmp/msg.temp",1);
// int msgrcv(int msgq, void * msgp, size_t mtextsize, long msgtype, int flags);
struct message msg;
int err = msgrcv(q_id,(void *)&msg,80,0,0);
FILE * f = fopen("/home/box/message.txt","w");
fwrite(msg.mtext,1,80, f);
fclose(f);

//msgctl(q_id,IPC_RMID,NULL); /*delete*/


}