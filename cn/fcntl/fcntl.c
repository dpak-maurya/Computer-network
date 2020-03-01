#include<stdio.h>
#include <sys/ioctl.h>
#include<stdlib.h>
#include <sys/types.h> 
#include <sys/stat.h> 
#include <fcntl.h>
#include<string.h>
#include<unistd.h>
int main()
{
	mkfifo("ffifo1",0666);
	int fd1=open("ffifo1",O_WRONLY);
	mkfifo("ffifo2",0666);
	int fd2=open("ffifo2",O_WRONLY);
	mkfifo("ffifo3",0666);
	int fd3=open("ffifo3",O_WRONLY);
	
	char buff[100];buff[0]='\0';
	printf("1 for close fd 2 for exit\n");
	while(1)
	{
		read(0,buff,sizeof(buff));
		if(buff[0]=='1')
		{close(fd1);close(fd2);close(fd3);}
		if(buff[0]=='2')
		{break;}
		write(fd1,buff,sizeof(buff));
		write(fd2,buff,sizeof(buff));
		write(fd3,buff,sizeof(buff));
		buff[0]='\0';
	}
	return 0;
}
