#include "header.h"
int main()
{
	char buff[100];
	int n=read(0,buff,sizeof(buff));
	buff[n+1]='\0';
	write(1,buff,sizeof(buff));
	return 0;
}
