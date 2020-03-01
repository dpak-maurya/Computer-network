#include<stdio.h>
#include <sys/ioctl.h>
#include<stdlib.h>
#include <sys/types.h> 
#include <sys/stat.h> 
#include <fcntl.h>
#include<string.h>
int main()
{
	int fd=1;
	char buff[100];buff[0]='\0';
	strcpy(buff,"changing font");
	write(fd,buff,strlen(buff)+1);
	ioctl(fd,SETFONT,"Arial");
	write(fd,buff,strlen(buff)+1);
	return 0;
}
