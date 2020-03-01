#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<sys/socket.h>
#include <arpa/inet.h>
#include<unistd.h>
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
	printf("send message to server\n");
	read(0,buffer,1024);
	send(sfd,buffer,strlen(buffer),0);
	buffer[0]='\0';
	int n=read(sfd,buffer,1024);
	write(0,buffer,n);
	return 0;
}
