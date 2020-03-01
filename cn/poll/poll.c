#include<time.h>
#include<stdio.h>
#include<sys/socket.h>
#include<netinet/in.h>
#include<string.h>
#include<sys/select.h>
#include<pthread.h>
#include<signal.h>
#include<stdlib.h>
#include<fcntl.h>
#include<sys/shm.h>
#include<unistd.h>
#include<sys/un.h>
#include<netinet/ip.h>
#include<arpa/inet.h>
#include<errno.h>
#include<netinet/if_ether.h>
#include<net/ethernet.h>
#include<netinet/ether.h>
#include<netinet/udp.h>
#include<poll.h>
#define TIMEOUT 5000

int main ()
{
	
	int pp[2];pipe(pp);
	
	
	struct pollfd pfd[2];
	
	pfd[0].fd = pp[1];
	pfd[0].events|=0;
	pfd[0].events = POLLOUT;
	pfd[0].revents=0;
	
	pfd[1].fd = pp[0];
	pfd[1].events|=0;
	pfd[1].events = POLLIN;
	pfd[1].revents=0;
	
	int ret;
	int c=fork();
	char buffer[1024];
	memset(buffer,'\0',sizeof(buffer));
	if(c>0)
	{while(1){
		//close(pp[1]);
		ret = poll(pfd, 2, TIMEOUT);
		if (ret==0||ret==-1) {
			printf ("%d seconds elapsed.\n", TIMEOUT);
		}
		if(pfd[0].revents & POLLOUT)
		{
			printf("pipe write\n");
			read(pp[1],buffer,sizeof(buffer));
			write(1,buffer,strlen(buffer)+1);
			memset(buffer,'\0',sizeof(buffer));
		}
		if(pfd[1].revents & POLLIN)
		{
			printf("pipe read\n");
			read(pp[0],buffer,sizeof(buffer));
			write(1,buffer,strlen(buffer)+1);
			memset(buffer,'\0',sizeof(buffer));
		}
		}
	}
	else
	{
		close(pp[0]);
		strcpy(buffer,"hello world\n");
		while(1)
		{
			write(pp[1],buffer,strlen(buffer)+1);
			sleep(3);
		}
		
	}
	return 0;

}
