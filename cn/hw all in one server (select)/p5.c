#include "header.h"
int main()
{
	int n;
	char buff[100];buff[0]='\0';
	while(n=read(0,buff,sizeof(buff)))
	{
		if(n!=0)
		{
			buff[n]='5';
			write(1,buff,n+1);
			buff[0]='\0';
		}
	}
	return 0;
}
