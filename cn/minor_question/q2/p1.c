#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include <unistd.h>
#include<fcntl.h>
#include<poll.h>
int main()
{
	int fd[4];
	fd[0]=fileno(popen("./p2","r"));
	fd[1]=fileno(popen("./p3","r"));
	fd[2]=fileno(popen("./p4","r"));
	
	fd[3]=fileno(popen("./p5","w"));
	struct pollfd pfd[3];
	for(int i=0;i<3;i++)
	{
		pfd[i].fd=fd[i];
		pfd[i].events=0;
		pfd[i].events|=POLLIN;
		pfd[i].revents=0;
	}
	while(1)
	{
		int ret=poll(pfd,3,2000);
		if(ret==0||ret==-1) {printf("timeout\n");continue;}
		else
		{
			printf("polled\n");
			for(int i=0;i<3;i++)
			{
				if(pfd[i].revents & POLLIN)
				{
					dup2(fd[i],0);
					char buffer[1024];
					buffer[0]='\0';
					dup2(fd[3],1);
					scanf("%s",buffer);
					printf("%s\n",buffer);
				}
			}
		}
	}
	return 0;
}
