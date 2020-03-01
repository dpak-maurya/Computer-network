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
	mkfifo("ffifo3",0666);
	int fd=open("ffifo3",O_RDONLY);
	fcntl(fd,F_SETFL,O_NONBLOCK);//wait
	char buff[100];buff[0]='\0';
	int n;
	while(n=read(fd,buff,sizeof(buff)))
	{
		if(n==-1 )
		{//errno==EAGAIN
			strcpy(buff,"data will come wait\n");
			write(1,buff,strlen(buff)+1);
			sleep(1);
		}
		else if(n==0)
		{//EOF
			strcpy(buff,"data will not come now\n");
			write(1,buff,strlen(buff)+1);
			break;
		}
		else
		{
			write(1,buff,strlen(buff)+1);
		}
		buff[0]='\0';
	}
	close(fd);
	return 0;
}
