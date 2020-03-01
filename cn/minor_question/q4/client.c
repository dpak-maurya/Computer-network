#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<unistd.h>
#include<fcntl.h>
#include <sys/time.h>
#include <sys/types.h>
#include <sys/select.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <netinet/ip.h>
#include <signal.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include<sys/wait.h>
#include<sys/stat.h>

struct msgbuf {
               long type;       /* message type, must be > 0 */
               char data[10];    /* message data */
           };
int main()
{
	int msq_r=msgget(95,IPC_CREAT|0666);
	int msq_s=msgget(65,IPC_CREAT|0666);
	
	struct msgbuf msg1;
	pid_t pid=getpid();
	msg1.type=pid;
	msgsnd(msq_s,&msg1,sizeof(msg1),0);
	printf(" message snd\n");
	msgrcv(msq_r,&msg1,sizeof(msg1),pid,0);
	printf(" message rcv\n");
	int fd;
	mkfifo("ro",0666);
	fd=open("ro",O_RDWR);
	int sfd;
	dup2(fd,sfd);
	
	printf("for exit #\n");
	while(1)
	{
		char buffer[1024];
		buffer[0]='\0';
		int n=read(0,buffer,1024);
		if(buffer[0]=='#')
			break;
		printf("from server %s\n",buffer);
	}
	
	msgrcv(msq_r,&msg1,sizeof(msg1),0,0);
	
	msgsnd(msq_s,&msg1,sizeof(msg1),0);
	printf("exited\n");
	return 0;
}
