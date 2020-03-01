#include "header.h"
int main()
{
	char buff[100];
	int n=read(0,buff,sizeof(buff));
	buff[n]='2';buff[n+1]='\0';
	write(1,buff,strlen(buff)+1);
	return 0;
}
