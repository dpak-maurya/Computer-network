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
	
	int max=10;int cnt=0;
	
	struct pollfd pfd[max];
	for(int i=0;i<max;i++)
	{pfd[i].events=0;pfd[i].revents=0;}
	int n;int timeout=1000;
	printf("started\n");
	
	pfd[0].fd=sfd;
	pfd[0].events|=POLLIN;
	pfd[0].revents=0;
	cnt=1;
	while(1)
	{
		int pret=poll(pfd,cnt,timeout);
		if(pret==0)
			//write(1,"timeout\n",8);
		else
		{
			for(int i=0;i<cnt;i++)
			{
				if((i==0) && (pfd[i].revents & POLLIN))
				{
					if((nsfd=accept(sfd,(struct sockaddr*)&address,(socklen_t *)&addresslen))<0)
							perror("nsfd");	
					else
					{
						pfd[cnt].fd=nsfd;
						pfd[cnt].events|=POLLIN;
						cnt++;
						write(1,"add client\n",11);
					}
				}
				else if(pfd[i].revents & POLLIN)
				{
					n=read(pfd[i].fd,buffer,1024);
					write(1,buffer,n);//writing on terminal
					for(int k=1;k<cnt;k++)
						if(k!=i)send(pfd[k].fd,buffer,n,0);
					break;
				}
			}
		}
	}
	return 0;
}
