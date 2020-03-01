#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <netdb.h>
#include <arpa/inet.h>
#include <sys/socket.h>
#include <string.h>
#include <unistd.h>
#include <errno.h>
#include <signal.h>
#include<sys/poll.h>
int main()
{
	char buffer[1024];
	while(1)
	{	
		memset(buffer,0,sizeof(buffer));
		int n=read(0,buffer,1024);
		buffer[n]='\0';
		write(1,buffer,strlen(buffer)+1);
	}
	return 0;
}
