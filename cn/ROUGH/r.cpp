#include<bits/stdc++.h>
#include<time.h>
#include<stdio.h>
#include<sys/socket.h>
#include<netinet/in.h>
#include<string.h>
#include<sys/select.h>
#include<pthread.h>
#include<signal.h>
#include<stdlib.h>
#include<fcntl.h>
#include<sys/shm.h>
#include<unistd.h>
#include<sys/un.h>
#include<netinet/ip.h>
#include<arpa/inet.h>
#include<errno.h>
#include<netinet/if_ether.h>
#include<net/ethernet.h>
#include<netinet/ether.h>
#include<netinet/udp.h>
#include<poll.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/msg.h>
using namespace std;
struct msgbuff
{
long type;
char msg[100];
char str[100];
};
int main()
{
	struct msgbuff msg1;
	key_t h=ftok("a.txt",65);
	key_t i=ftok("b.txt",75);
	int ms=msgget(h,IPC_CREAT|0666);
	int mr=msgget(i,IPC_CREAT|0666);
	
	msg1.type=getpid();
	strcpy(msg1.msg,"hello\n");
	strcpy(msg1.str,"bye\n");
	msgsnd(mr,&msg1,sizeof(msg1),0);
	
	msgrcv(ms,&msg1,sizeof(msg1),0/*type*/,0);
	cout<<msg1.msg<<endl;
	cout<<msg1.type<<endl;
	cout<<msg1.str<<endl;
	
	return 0;
}
