#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<sys/socket.h>
#include <arpa/inet.h>
#include <netinet/ip.h>
#include<fcntl.h>
#include <unistd.h>
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
	
	
	    int opt=1;
	    if (setsockopt(sfd, SOL_SOCKET, SO_REUSEADDR | SO_REUSEPORT, &opt, sizeof(opt))) 
	    { 
		perror("setsockopt");
	    }
	
	
	address.sin_port=htons(8081);
	address.sin_addr.s_addr=INADDR_ANY;
	if(bind(sfd,(struct sockaddr *)&address ,sizeof(address))<0)
		perror("bind");
	if(listen(sfd,3)<0)
		perror("listen");
	int nsfd;
	int addresslen=sizeof(address);
	if((nsfd=accept(sfd,(struct sockaddr*)&address,(socklen_t *)&addresslen))<0)
		perror("nsfd");
	close(sfd);
	struct pollfd pfd[2];
	pfd[0].fd=0;pfd[1].fd=nsfd;
	pfd[0].events=0;pfd[1].events=0;
	pfd[0].events|=POLLIN;pfd[1].events|=POLLIN;
	pfd[0].revents=0;pfd[1].revents=0;
	int n;int timeout=5000;
	while(1)	
	{	
		int pret=poll(pfd,2,timeout);
		if(pret==0)
			printf("timeout");
		else
		{
			if(pfd[0].revents & POLLIN)
			{
				n=read(0,buffer,1024);
				send(nsfd,buffer,n,0);
			}
			else if(pfd[1].revents & POLLIN)
			{
				n=read(nsfd,buffer,1024);
				write(1,buffer,n);//writing on terminal
			}
		}
	}
	return 0;
}
