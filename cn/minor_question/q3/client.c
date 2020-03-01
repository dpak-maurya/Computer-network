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

int main()
{
	printf("give service number\n");
	int i;
	scanf("%d",&i);
	int sfd;
	if((sfd=socket(AF_INET,SOCK_STREAM,0))<0)
	perror("sfd");
	struct sockaddr_in address;
	address.sin_family=AF_INET;
	int p=8080+i;
	address.sin_port=htons(p);
	address.sin_addr.s_addr=INADDR_ANY;
	int y;
	y=connect(sfd,(struct sockaddr*)&address,sizeof(address));
	if(y<0)
	perror("connect");
	printf("client started %d \n",p);
	char buffer[1024];
	while(1)
	{	
		strcpy(buffer,"");
		int n=read(0,buffer,1024);
		buffer[n]='\0';
		write(sfd,buffer,strlen(buffer)+1);
		strcpy(buffer,"");
		n=read(sfd,buffer,1024);
		printf("output from serviceserver is %s\n",buffer);
	}
	return 0;
}
