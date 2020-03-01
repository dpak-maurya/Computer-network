#include "header.h"
int main()
{
	char buff[100];
	read(0,buff,sizeof(buff));
	printf("%s/n",buff);
	strcpy(buff,"hello");
	write(1,buff,sizeof(buff));
	return 0;
}
