#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<sys/socket.h>
#include <arpa/inet.h>
#include<unistd.h>
#include <poll.h>

int main()
{
	char buffer[1024];
	buffer[0]='\0';
	int sfd=socket(AF_INET,SOCK_STREAM,0);
	if(sfd<0)
		perror("sfd");
	struct sockaddr_in address;
	address.sin_family=AF_INET;
	address.sin_port=htons(8081);
	address.sin_addr.s_addr=inet_addr("127.0.0.1");
	if(connect(sfd,(struct sockaddr *)&address ,sizeof(address))<0)
		perror("connect");
		
	struct pollfd pfd[2];
	pfd[0].fd=0;pfd[1].fd=sfd;
	pfd[0].events=0;pfd[1].events=0;
	pfd[0].events|=POLLIN;pfd[1].events|=POLLIN;
	pfd[0].revents=0;pfd[1].revents=0;
	int n;
	int timeout=1000;
	printf("started\n");
	while(1)	
	{	
		int pret=poll(pfd,2,timeout);
		if(pret==0||pret==-1)continue;
			//printf("timeout\n");
		else
		{
			if(pfd[0].revents & POLLIN)
			{
				n=read(0,buffer,1024);
				int p=send(sfd,buffer,n,0);
				if(p<0) perror("Send error Client\n");
				printf("send to server\n");
			}
			else if(pfd[1].revents & POLLIN)
			{
				n=read(sfd,buffer,1024);
				write(1,buffer,n);//writing on terminal
			}
		}
	}
	return 0;
}
