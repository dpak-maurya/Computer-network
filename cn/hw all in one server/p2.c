#include "header.h"
int main()
{
	mkfifo("fifo",0666);
	int ffd=open("fifo",O_WRONLY);
	int n;
	char buff[100];buff[0]='\0';
	while(n=read(0,buff,sizeof(buff)))
	{
		if(n!=0)
		{
			write(ffd,buff,n);
			buff[0]='\0';
		}
	}
	return 0;
}
