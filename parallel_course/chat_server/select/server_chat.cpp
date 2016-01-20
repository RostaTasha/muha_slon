#include <iostream>
#include <algorithm>
#include <set>
#include <map>
#include <sys/types.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <netinet/in.h>
#include <unistd.h>
#include <fcntl.h>
#include <string.h>


char *get_ip_str(const struct sockaddr *sa, char *s, size_t maxlen)
{
    switch(sa->sa_family) {
        case AF_INET:
            inet_ntop(AF_INET, &(((struct sockaddr_in *)sa)->sin_addr),
                    s, maxlen);
            break;

        case AF_INET6:
            inet_ntop(AF_INET6, &(((struct sockaddr_in6 *)sa)->sin6_addr),
                    s, maxlen);
            break;

        default:
            strncpy(s, "Unknown AF", maxlen);
            return NULL;
    }

    return s;
}


int set_nonblock(int fd){
	int flags;
#ifdef O_NONBLOCK
	if (-1== (flags=fcntl(fd,F_GETFL,0)))
		flags=0;
	return fcntl(fd,F_SETFL,flags|O_NONBLOCK); //posix standartized
#else
	flags=1;
	return ioctl(fd,FIOBIO,&flags);		// unix, may change its behavior depend on  OS and/or type of file descriptor 
#endif
	
}

int main(int argc, char ** argv){
	int MasterSocket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
	std::map<int,std::string> SlaveSockets;
	struct sockaddr_in SockAddr;
	SockAddr.sin_family=AF_INET;
    SockAddr.sin_port=htons(12345);
    SockAddr.sin_addr.s_addr=htons(INADDR_ANY); //0.0.0.0
    bind(MasterSocket,(struct sockaddr*)(&SockAddr),sizeof(SockAddr));
    
    set_nonblock(MasterSocket);
    listen(MasterSocket,SOMAXCONN); // MAX size of queue of TCP binds
    while(true){
    	fd_set Set; // 1024 bits
    	FD_ZERO(&Set); //set all 0
    	FD_SET(MasterSocket,&Set);
    	for (auto Iter = SlaveSockets.begin(); Iter!=SlaveSockets.end();++Iter){
    		FD_SET(Iter->first,&Set);    		
    	}
    	
    	int Max = std::max(MasterSocket,(std::max_element(SlaveSockets.begin(),SlaveSockets.end(),[](const std::pair<int,std::string> a, const std::pair<int,std::string> b) { return a.first < b.first; }))->first);
    	select(Max+1,&Set,NULL,NULL,NULL);
    	
    	for (auto Iter = SlaveSockets.begin(); Iter!=SlaveSockets.end(); ++Iter){
    	
    	
    	if (FD_ISSET(Iter->first,&Set)){
    	//obrabotka sobitia
    		static char Buffer[1024];
    		int RecvSize=recv(Iter->first,Buffer,1024,MSG_NOSIGNAL); //read as much as we can
    		// error or connection was closed
    		if ((RecvSize==0) && (errno != EAGAIN)) {// exclude interrupt
				std::string msg = Iter->second + " disconnected from chat";
				for (auto Iter1 = SlaveSockets.begin(); Iter1!=SlaveSockets.end(); ++Iter1)
						send(Iter1->first,msg.c_str(),msg.size(),MSG_NOSIGNAL); 
    			shutdown(Iter->first,SHUT_RDWR);
    			close(Iter->first);
    			SlaveSockets.erase(Iter);
    			} else if (RecvSize!=0){
    			 	for (auto Iter1 = SlaveSockets.begin(); Iter1!=SlaveSockets.end(); ++Iter1){
						send(Iter1->first,(Iter1->second+">>>").c_str(),Iter1->second.size()+3,MSG_NOSIGNAL); 
						send(Iter1->first,Buffer,RecvSize,MSG_NOSIGNAL); //send what we have read
						}
    			}
    		
    		}
    		
    	}	
    		
    	 if (FD_ISSET(MasterSocket,&Set)){
			struct sockaddr ip_addr;
			unsigned int size;
			char *  str = new char[16];
			int SlaveSocket = accept(MasterSocket,(struct sockaddr *)(&ip_addr),&size);
			str = get_ip_str((const struct sockaddr *)&ip_addr, str, 16);
			std::string msg = "New user "+std::string(str)+" connected to chat\n";
			set_nonblock(SlaveSocket);
			SlaveSockets.insert(std::pair<int,std::string>(SlaveSocket,std::string(str)));
			delete [] str;
			for (auto Iter1 = SlaveSockets.begin(); Iter1!=SlaveSockets.end(); ++Iter1)
					send(Iter1->first,msg.c_str(),msg.length(),MSG_NOSIGNAL); //send what we have read
    	 }
    	
    	
    	
     
    }
    
    
 return 0;
}
