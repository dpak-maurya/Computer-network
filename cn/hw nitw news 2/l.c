#include"header.h"
int main(int argc ,char * argv[])
{
	write(1,"i am live telecaster\n",21);
	write(1,argv[1],strlen(argv[1])+1);
	return 0;
}
