#include "header.h"
int main(int argc,char* argv[])
{
	char buff[100];buff[0]='\0';
	int n;
	while(n=read(0,buff,sizeof(buff)))
	{
		if(n!=0)
		{
			kill(atoi(argv[1]),SIGUSR1);
			buff[0]='\0';
		}
	}
	return 0;
}
