#include <unistd.h>
#include <sys/types.h>
#include <sys/mman.h>
#include <fcntl.h>

int main(){
// mmap munmap memory- file
//int shm_open(const char * name, int flags, mode_t perms)
//int shm unlink(const char * name)
//ftruncate(int fd, ooft,length) change size of file and otobr virtualnii file

//shm_open
//ftrunkate
//mmap

//munmap
//shm_delete

//void * mmap  ( void * addr // �������� �����
//				size_t len // ������ ��������
//				int prot  // ����� �������, ������ �������� PROT_NONE, PROT_READ,PROT_WRITE,PROT_EXEC
//				int flags // ����� MAP_SHARED MAP_PRIVATE
//				int fd //Descriptor
//				off_t off); // ��������

//void * munmap( void * addr,
//				size_t len); //����� ���������� �����, �� ���� ����

int fd = shm_open("/test.shm",O_CREAT|O_RDWR,0666);
ftruncate(fd,1024*1024);
char * addr;
addr = mmap(addr,1024*1024,PROT_WRITE|PROT_READ,MAP_SHARED,fd,0);
int i =0;
for (i=0; i<1024*1024;i++){
	addr[i]=13;
}


}