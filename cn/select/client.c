#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <netdb.h>
#include <arpa/inet.h>
#include <sys/socket.h>
#include <string.h>
#include <unistd.h>
#include <errno.h>
#include <signal.h>
#include<sys/poll.h>
int max(int a,int b)
{
	if(a>b) return a;
	return b;
}
int main()
{
	char buffer[1024];
	buffer[0]='\0';
	int sfd=socket(AF_INET,SOCK_STREAM,0);
	if(sfd<0)
		perror("sfd");
	struct sockaddr_in address;
	address.sin_family=AF_INET;
	printf("Enter 1 for service 1 or 2 for service 2\n");
	int s;
	scanf("%d",&s);
	if(s==1)
		address.sin_port=htons(8081);
	else
		address.sin_port=htons(8082);
	address.sin_addr.s_addr=INADDR_ANY;
	if(connect(sfd,(struct sockaddr *)&address ,sizeof(address))<0)
		perror("connect");
        printf("sarted\n");
        fd_set rfds;
	while(1)
	{
		FD_ZERO(&rfds);
		FD_SET(0,&rfds);
		FD_SET(sfd,&rfds);
		int maxfd=max(0,sfd);maxfd++;
		int ret=select(maxfd,&rfds,NULL,NULL,NULL);
		if (ret== -1||ret==0)
               		perror("timeout");
           	else
               	{
               		if(FD_ISSET(0,&rfds))
               		{
               			memset(buffer,0,sizeof(buffer));
               			int n=read(0,buffer,1024);
               			write(sfd,buffer,n);
 				printf("send to service %s\n",buffer);
               		}
               		if(FD_ISSET(sfd,&rfds))
               		{
               			memset(buffer,0,sizeof(buffer));
               			int n=read(sfd,buffer,1024);
               			printf("from service %s\n",buffer);
               		}
               	}
	}
	return 0;
}
