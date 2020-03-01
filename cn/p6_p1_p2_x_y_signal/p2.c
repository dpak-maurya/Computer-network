#include "header.h"
void hdfn(int signo)
{
	if(signo==SIGINT)
	printf("hello");
}
int main()
{
	signal(SIGINT,hdfn);
	printf("hi\n");raise(SIGINT);
	printf("hi\n");
	int n=10;
	while(n--){printf("1\n");sleep(1);}
	return 0;
}
