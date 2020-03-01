#include"header.h"
int main(int argc,char * argv)
{
	int fd=(int)atoi(argv[1]);
	write(fd,"hello",5);
	return 0;
}
