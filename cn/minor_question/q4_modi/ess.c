#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<unistd.h>
#include<fcntl.h>
#include <sys/time.h>
#include <sys/types.h>
#include<sys/wait.h>
#include<sys/stat.h>
#include <sys/select.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <netinet/ip.h>
#include <signal.h>
#include <sys/ipc.h>
#include <sys/msg.h>
int main()
{
	int sfd;
	struct sockaddr_in address;
	address.sin_family=AF_INET;
	address.sin_addr.s_addr=INADDR_ANY;
	if((sfd=socket(AF_INET,SOCK_STREAM,0))<0)
	perror("sfd");
	address.sin_port=htons(8080);
	int opt=1;
	    if (setsockopt(sfd, SOL_SOCKET, SO_REUSEADDR | SO_REUSEPORT, &opt, sizeof(opt))) 
	    { 
		perror("setsockopt");
	    }
	int y;
	y=bind(sfd,(struct sockaddr*)&address,sizeof(address));
	if(y<0)
	perror("bind");
	y=listen(sfd,5);
	if(y<0)
	perror("listen");
	int len=sizeof(address);
	int nsfd=accept(sfd,(struct sockaddr *)&address,(socklen_t *)&len);
	//ess will accept
	if(nsfd<0)
	perror("nsfd");
	printf("started\n");
	while(1)
	{
		char buffer[1024];
		buffer[0]='\0';
		int n=read(nsfd,buffer,1024);
		printf("from client %s\n",buffer);
		write(nsfd,buffer,n+1);
	}
	return 0;
}
