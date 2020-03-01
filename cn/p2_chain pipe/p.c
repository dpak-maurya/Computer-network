#include "header.h"
int main()
{
	int pp[2];
	pipe(pp);
	char buff[100];
	strcpy(buff,"hello world");
	write(pp[1],buff,sizeof(buff));
	int c;
	int n;
	scanf("value of n %d\n",&n);
	int fcopy=dup(1);
	dup2(pp[0],0);
	dup2(pp[1],1);
	while(n--)
	{
		c=fork();
		if(c==0)
		{
			char * args[]={"./p2.out",NULL};
			execvp(args[0],args);
		}
		else
		{
			wait(NULL);
		}
	}
	int size=read(0,buff,sizeof(buff));
	buff[size]='\0';
	write(fcopy,buff,sizeof(buff));
	return 0;
}
