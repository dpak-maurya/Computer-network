#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include <unistd.h>
#include<fcntl.h>
#include<poll.h>
int main()
{
	while(1)
	{
		char buffer[1024];
		buffer[0]='\0';
		scanf("%s",buffer);
		printf("%s\n",buffer);
	}
	return 0;
}
