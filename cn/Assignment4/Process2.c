#include"header.h"
int main(int argc, char * argv[])
{
	int fd=open("Process2Fifo",O_WRONLY);
	int cnt=0;
	while(1)
	{	
		sleep(5);
		char x[30]="Input from Process2\n";
		write(fd,x,strlen(x));
	}
	return 0;
}
