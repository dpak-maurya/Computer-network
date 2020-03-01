#include "header.h"
int main(int argc,char **argv)
{
	char buff[100];
	read(0,buff,sizeof(buff));
	strcat(buff,"i");
	write(1,buff,sizeof(buff));
	return 0;
}
