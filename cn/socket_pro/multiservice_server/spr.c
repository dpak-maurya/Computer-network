#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<sys/socket.h>
#include <arpa/inet.h>
#include <netinet/ip.h>
#include<fcntl.h>
#include <unistd.h>
#include<poll.h>
int main()
{
	char buffer[1024];
	buffer[0]='\0';
	int sfd=socket(AF_INET,SOCK_STREAM,0);
	if(sfd<0)		perror("sfd");
	int sfd2=socket(AF_INET,SOCK_STREAM,0);
	if(sfd2<0)		perror("sfd");
	struct sockaddr_in address,address2;
	address.sin_family=AF_INET;
	address2.sin_family=AF_INET;
	
	    int opt=1;
	    if (setsockopt(sfd, SOL_SOCKET, SO_REUSEADDR | SO_REUSEPORT, &opt, sizeof(opt))) 
	    { 
		perror("setsockopt");
	    }
	    if (setsockopt(sfd2, SOL_SOCKET, SO_REUSEADDR | SO_REUSEPORT, &opt, sizeof(opt))) 
	    { 
		perror("setsockopt");
	    }
	
	address.sin_port=htons(8081);
	address2.sin_port=htons(8082);
	address.sin_addr.s_addr=INADDR_ANY;
	address2.sin_addr.s_addr=INADDR_ANY;
	if(bind(sfd,(struct sockaddr *)&address ,sizeof(address))<0)		perror("bind");
	if(listen(sfd,3)<0)		perror("listen");
	if(bind(sfd2,(struct sockaddr *)&address2 ,sizeof(address2))<0)		perror("bind");
	if(listen(sfd2,3)<0)		perror("listen");
	int nsfd;int nsfd2;
	int addresslen=sizeof(address);
	int addresslen2=sizeof(address);
	
	struct pollfd pfd[2];
	for(int i=0;i<2;i++)
	{pfd[i].events=0;pfd[i].revents=0;}
	int n;
	int timeout=5000;
	printf("started\n");
	pfd[0].fd=sfd;
	pfd[1].fd=sfd2;
	pfd[0].events|=POLLIN;pfd[1].events|=POLLIN;
	while(1)
	{
		int pret=poll(pfd,2,timeout);
		if(pret==0)
			write(1,"timeout\n",8);
		else
		{
			if(pfd[0].revents & POLLIN)
			{
				if((nsfd=accept(sfd,(struct sockaddr*)&address,(socklen_t *)&addresslen))<0)
						perror("nsfd");	
				else
				{
					write(1,"add client 1\n",13);
					int c=fork();
					if(c==0)
					{
						//echo server
						close(sfd);
						dup2(nsfd,1);
						dup2(nsfd,0);
						char *args[]={"./es1",NULL};
						/*char statement[72]="";
						strcat(statement,"gnome-terminal -- /bin/bash -c './es1 ");
						strcat(statement,";'");
						system(statement);*/
						execv(args[0],args);
					}
					else
						close(nsfd);
				}
			}
			else if(pfd[1].revents & POLLIN)
			{
				if((nsfd2=accept(sfd2,(struct sockaddr*)&address,(socklen_t *)&addresslen))<0)
						perror("nsfd");	
				else
				{
					write(1,"add client 2\n",13);
					int c=fork();
					if(c==0)
					{
						//echo server
						close(sfd);
						char *args[]={"./es2",NULL};
						dup2(nsfd2,1);
						dup2(nsfd2,0);
						execv(args[0],args);
					}
					else
						close(nsfd2);
				}
			}
		}
	}
	return 0;
}
