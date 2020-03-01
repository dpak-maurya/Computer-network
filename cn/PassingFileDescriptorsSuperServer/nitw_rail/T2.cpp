#include"header.h"
int main()
{
	int sfd=socket(AF_INET,SOCK_STREAM,0);
	perror("sfd");
	struct sockaddr_in address;
	address.sin_family=AF_INET;
	address.sin_port=htons(8082);
	address.sin_addr.s_addr=inet_addr("127.0.0.1");
	connect(sfd,(struct sockaddr *)&address ,sizeof(address));
	perror("connect");
	
	char buffer[]="123456789";	
	write(sfd,buffer,strlen(buffer)+1);
	sleep(2);
	char buff[]="left";
	write(sfd,buff,strlen(buff)+1);
	return 0;
}
