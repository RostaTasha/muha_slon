#include <stdio.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>

int main(int argc, char **argv){
    int MasterSocket = socket( /* listen */
                      AF_INET/* IPv4*/,
                      SOCK_STREAM/* TCP */,
                      IPPROTO_TCP); 
    struct sockaddr_in SockAddr;
    SockAddr.sin_family=AF_INET;
    SockAddr.sin_port=htons(12345);
    SockAddr.sin_addr.s_addr=htons(INADDR_ANY); //0.0.0.0
    bind(MasterSocket,(struct sockaddr*)(&SockAddr),sizeof(SockAddr));
    
    listen(MasterSocket,SOMAXCONN);
    
    while(1){
    	int SlaveSocket  = accept(MasterSocket,0,0);
    	char Buffer[5]={0,0,0,0,0};
    	while (recv(SlaveSocket,Buffer,1,MSG_NOSIGNAL) >0){
    			send(SlaveSocket,Buffer,1,MSG_NOSIGNAL);
    	}
    	
    	shutdown(SlaveSocket,SHUT_RDWR);
    	close(SlaveSocket);
    			
 
    }
    

    
    
    

	

    return 0;
}
