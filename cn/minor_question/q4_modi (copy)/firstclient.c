#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<unistd.h>
#include<fcntl.h>
#include<sys/wait.h>
#include<sys/stat.h>
#include <sys/time.h>
#include <sys/types.h>
#include <sys/select.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <netinet/ip.h>
#include <signal.h>
#include <sys/ipc.h>
#include <sys/msg.h>
struct msgbuf {
               long type;       /* message type, must be > 0 */
               char data[10];    /* message data */
           };
void hdfn()
{
	int p=unlink("name");
	signal(SIGINT,SIG_DFL);
	raise(SIGINT);
}
int main()
{
	key_t key=ftok("name",65);
	int msq=msgget(key,IPC_CREAT|0666);
	signal(SIGINT,hdfn);
	int sfd;
	if((sfd=socket(AF_INET,SOCK_STREAM,0))<0)
	perror("sfd");
	struct sockaddr_in address;
	address.sin_family=AF_INET;
	
	address.sin_port=htons(8080);
	address.sin_addr.s_addr=INADDR_ANY;
	int y;
	y=connect(sfd,(struct sockaddr*)&address,sizeof(address));
	if(y<0)
	perror("connect");
	
	printf("for exit #\n");
	while(1)
	{
		char buffer[1024];
		buffer[0]='\0';
		int n=read(0,buffer,1024);
		if(buffer[0]=='#')
			break;
		write(sfd,buffer,n+1);
		read(sfd,buffer,1024);
		printf("from ess %s\n",buffer);
	}
	printf("exited temporary\n");
	int fd;
	mkfifo("ro",0666);
	fd=open("ro",O_RDWR);
	struct msgbuf msg1;
	while(1)
	{
		msgrcv(msq,&msg1,sizeof(msg1),0,0);
		printf("received new client %ld\n",msg1.type);
		msgsnd(msq,&msg1,sizeof(msg1),0);
		printf("snd\n");
		while(1)
		{
			char buffer[1024];
			buffer[0]='\0';
			int n=read(fd,buffer,1024);
			if(buffer[0]=='#')break;
			write(sfd,buffer,n+1);
			read(sfd,buffer,1024);
			write(fd,buffer,n+1);	
		}
	}
	printf("exited \n");
	return 0;
}
