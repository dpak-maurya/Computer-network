#include"header.h"
int main()
{
	int sfd;
	struct sockaddr_in serv_addr;
	int port_no=8081;

	bzero(&serv_addr,sizeof(serv_addr));
	if((sfd = socket(AF_INET , SOCK_STREAM , 0))==-1)
	perror("\n socket");
	else printf("\n socket created successfully\n");
	serv_addr.sin_family = AF_INET;
	serv_addr.sin_port = htons(port_no);
	serv_addr.sin_addr.s_addr = INADDR_ANY;
	if(connect(sfd , (struct sockaddr *)&serv_addr , sizeof(serv_addr))==-1)
	perror("\n connect : ");
	else printf("\nconnect succesful");
	write(sfd,"hello\n",6);
	
	sleep(5);
	
	write(sfd,"left\n",5);
	
	return 0;
}
