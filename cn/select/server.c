#include<stdio.h>
#include<stdlib.h>
#include<sys/types.h>
#include<netdb.h>
#include<arpa/inet.h>
#include<sys/socket.h>
#include<string.h>
#include<unistd.h>
#include<errno.h>
#include<signal.h>
#include<sys/poll.h>
int max(int a,int b)
{
	if(a>b) return a;
	return b;
}
int main()
{
	printf("started\n");
	char buffer[1024];
	buffer[0]='\0';
	int sfd1,sfd2;
	sfd1=socket(AF_INET,SOCK_STREAM,0);
	sfd2=socket(AF_INET,SOCK_STREAM,0);
	if(sfd1<0)perror("sfd error");
	if(sfd2<0)perror("sfd error");
	struct sockaddr_in address1,address2,cliaddr;
	address1.sin_family=AF_INET;
	address1.sin_port=htons(8081);
	address1.sin_addr.s_addr=INADDR_ANY;
	address2.sin_family=AF_INET;
	address2.sin_port=htons(8082);
	address2.sin_addr.s_addr=INADDR_ANY;
	    int opt=1;
	    if (setsockopt(sfd1, SOL_SOCKET, SO_REUSEADDR | SO_REUSEPORT, &opt, sizeof(opt))) 
		perror("setsockopt");
	    if (setsockopt(sfd2, SOL_SOCKET, SO_REUSEADDR | SO_REUSEPORT, &opt, sizeof(opt))) 
		perror("setsockopt");
	if(bind(sfd1,(struct sockaddr *)&address1,sizeof(address1))<0)	perror("bind error");
	if(bind(sfd2,(struct sockaddr *)&address2,sizeof(address2))<0)	perror("bind error");
	if((listen(sfd1,5))<0)	perror("listen error");
	if((listen(sfd2,5))<0)	perror("listen error");
	int len=sizeof(cliaddr);
	fd_set rfds;
	
        int nsfd1,nsfd2;
        printf("started2\n");
        
	while(1)
	{
		FD_ZERO(&rfds);
		FD_SET(sfd1,&rfds);
		FD_SET(sfd2,&rfds);
		int maxfd=max(sfd1,sfd2);maxfd++;
		int ret=select(maxfd,&rfds,NULL,NULL,NULL);
           	if (ret== -1||ret==0)
               		perror("timeout");
           	else
               	{
               		printf("selected\n");
       			if(FD_ISSET(sfd1,&rfds))
       			{
       				if((nsfd1=accept(sfd1, (struct sockaddr*)&cliaddr, &len))<0)
       					perror("nsfd error");
       				printf("added client\n");
       				int c=fork();
				if(c!=0)
				{
					close(nsfd1);
				}
				else
				{
					close(sfd1);
					dup2(nsfd1,0);
					dup2(nsfd1,1);
					char * args[]={"./s1",NULL};
					execv(args[0],args);
				}
       			}
       			if(FD_ISSET(sfd2,&rfds))
       			{
       				if((nsfd2=accept(sfd2, (struct sockaddr*)&cliaddr, &len))<0)
       					perror("nsfd error");
       				printf("added client\n");
       				int c=fork();
				if(c!=0)
				{
					close(nsfd2);
				}
				else
				{
					close(sfd2);
					dup2(nsfd2,0);
					dup2(nsfd2,1);
					char * args[]={"./s2",NULL};
					execv(args[0],args);
				}
       			}
               	}
	}
	return 0;
}
