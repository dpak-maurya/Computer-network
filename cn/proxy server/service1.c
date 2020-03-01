#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<fcntl.h>
#include<unistd.h>
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
	address.sin_port=htons(8082);
	address.sin_addr.s_addr=inet_addr("127.0.0.1");
	if(connect(sfd,(struct sockaddr *)&address ,sizeof(address))<0)
		perror("connect");
		
	struct pollfd pfd[1];
	pfd[0].fd=sfd;
	pfd[0].events=0;
	pfd[0].events|=POLLIN;
	pfd[0].revents=0;
	int timeout=1000;
	printf("started\n");
	int n;
	while(1)	
	{	
		int pret=poll(pfd,1,timeout);
		if(pret==0)
			printf("timeout\n");
		else
		{
			if(pfd[0].revents & POLLIN)
			{
				char buffer[1024];buffer[0]='\0';
				n=read(sfd,buffer,1024);
				for(int i=0;i<n;i++)
				{
					if(buffer[i]>='a' && buffer[i]<='z')
					buffer[i]=buffer[i]-'a'+'A';
				}
				write(sfd,buffer,n+1);
				printf("send to server\n");
			}
		}
	}
	return 0;
}
