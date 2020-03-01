#include<stdlib.h>
#include<stdio.h>
#include<unistd.h>
#include<grp.h>
#include<sys/types.h>
#include<fcntl.h>
#include<signal.h>
#include<string.h>
int main()
{
	printf("process starting\n");
	int fd=open("c.txt",O_RDWR|O_CREAT);
	printf("%d\n",(int)getgid());
	sleep(5);
	fcntl(fd,F_SETOWN,-1000);
	while(1)
	{
		char buffer[]="hello--";
		write(fd,buffer,strlen(buffer));
	}
	return 0;
}
