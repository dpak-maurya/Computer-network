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

int main()
{
	printf("exit for exit\n");
	char buffer[1024];
	buffer[0]='\0';
	while(1)
	{
		int n=read(0,buffer,1024);
		printf("Display sequence\n");
		write
	}
	return 0;
}
