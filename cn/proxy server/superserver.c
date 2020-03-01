#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<sys/socket.h>
#include <arpa/inet.h>
#include <netinet/ip.h>
#include<fcntl.h>
#include <unistd.h>
#include<pthread.h>
#include<poll.h>
int main()
{
	int sfd=socket(AF_INET,SOCK_STREAM,0);
	if(sfd<0)	perror("sfd");
	struct sockaddr_in address;
	address.sin_family=AF_INET;
	address.sin_port=htons(8083);
	address.sin_addr.s_addr=INADDR_ANY;
	int opt=1;
	    if (setsockopt(sfd, SOL_SOCKET, SO_REUSEADDR | SO_REUSEPORT, &opt, sizeof(opt))) 
	    { 
		perror("setsockopt");
	    }
	int y=bind(sfd,(struct sockaddr *)&address,sizeof(address));
	if(y<0)		perror("bind");
	y=listen(sfd,5);
	if(y<0)		perror("bind");
	int nsfd;
	int addresslen=sizeof(address);
	nsfd=accept(sfd,(struct sockaddr *)&address,(socklen_t *)&addresslen);
	if(nsfd<0) 	perror("nsfd");
	fd_set rfds;
	FD_ZERO(&rfds);
	printf("started\n");
	while(1)
	{
		FD_SET(nsfd,&rfds);
		int maxfd=nsfd+1;
		int ret=select(maxfd,&rfds,NULL,NULL,NULL);
		if(ret==-1) 	{continue;}
		else
		{
			if(FD_ISSET(nsfd,&rfds))
			{
				char buffer[1024]="";
				//buffer[0]='\0';
				int n=read(nsfd,buffer,1024);
				buffer[n]='\0';
				write(1,"message from main server %s\n ",nsfd);
				for(int i=0;i<n;i++)
				{
					if(buffer[i]>='a' && buffer[i]<='z')
					buffer[i]=buffer[i]-'a'+'A';
				}
				write(nsfd,buffer,n+1);
			}
		}
	}
}
