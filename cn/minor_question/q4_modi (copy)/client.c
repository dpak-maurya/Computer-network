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
	pid_t pid=getpid();
	printf("%d\n",pid);
	key_t key=ftok("name",65);
	int msq=msgget(key,IPC_CREAT|0666);
	
	struct msgbuf msg1;
	msg1.type=pid;
	msgsnd(msq,&msg1,sizeof(msg1),0);
	printf(" message snd %ld\n",msg1.type);
	//waiting for my message
	msgrcv(msq,&msg1,sizeof(msg1),pid,0);
	
	int fd;
	mkfifo("ro",0666);
	fd=open("ro",O_RDWR);
	
	printf("for exit #\n");
	while(1)
	{
		char buffer[1024];
		buffer[0]='\0';
		int n=read(0,buffer,1024);
		write(fd,buffer,n+1);
		if(buffer[0]=='#')
			break;
		read(fd,buffer,1024);
		printf("from ess %s\n",buffer);
	}
	printf("exited\n");
	return 0;
}
