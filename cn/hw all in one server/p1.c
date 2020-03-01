#include "header.h"
int main()
{
	char buff[100];buff[0]='\0';
	int n;
	while(n=read(0,buff,sizeof(buff)))
	{
		if(n!=0)
		{
			write(1,buff,n);
		}
	}
	return 0;
}
