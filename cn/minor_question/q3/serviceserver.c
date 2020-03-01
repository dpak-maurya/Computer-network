#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<unistd.h>
#include<fcntl.h>
#include <sys/time.h>
#include <sys/types.h>
#include <sys/select.h>
#include <arpa/inet.h>
#include <netinet/ip.h>
#include <sys/socket.h>
#include <signal.h>

int max(int a,int b)
{
	if(a>b) return a;
	return b;
}
int main()
{
	int cnt=0;
	int fd[5];
	fd_set rfds;
	FD_ZERO(&rfds);
	while(1)
	{
		if(cnt==5)
		{
			pid_t pid=getppid();
			kill(pid,SIGUSR1);
		}
		int maxfd=0;
		FD_SET(0,&rfds);
		for(int i=0;i<cnt;i++)
		{
			FD_SET(fd[i],&rfds);
			maxfd=max(maxfd,fd[i]);
		}
		maxfd++;
		int ret=select(maxfd,&rfds,NULL,NULL,NULL);
		if(ret==0||ret==-1) {continue;}
		else
		{
			printf("selected from service server %d\n",cnt);
			for(int i=0;i<cnt;i++)
			{
				if(FD_ISSET(fd[i],&rfds))
				{
					char buffer[1024];
					strcpy(buffer,"");
					int n=read(fd[i],buffer,1024);
					printf("input from client %s \n",buffer);
					write(fd[i],buffer,n+1);
				}
			}
			if(FD_ISSET(0,&rfds))
			{
				struct sockaddr_in address;
				int len=sizeof(address);
				int nsfd=accept(0,(struct sockaddr *)&address,(socklen_t *)&len);
				if(nsfd<0)
				perror("nsfd");
				fd[cnt++]=nsfd;
			}
		}
	}
	return 0;
} 
