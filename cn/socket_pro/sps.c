#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<sys/socket.h>
#include <arpa/inet.h>
#include <netinet/ip.h>
#include<fcntl.h>
#include <unistd.h>

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
	int n=read(nsfd,buffer,1024);
	write(1,buffer,n);//writing on terminal
	printf("send message to client\n");
	read(0,buffer,1024);
	send(nsfd,buffer,strlen(buffer),0);
	return 0;
}
