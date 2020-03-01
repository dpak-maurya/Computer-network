#include<stdlib.h>
#include<stdio.h>
#include<unistd.h>
#include<grp.h>
#include<sys/types.h>
#include<fcntl.h>
#include<signal.h>
void hdfn(int signo)
{
	printf("Signal received\n");
}
int main()
{
	printf("my group id is %d\n",(int)getgid());
	int v=setpgid(0,1000);
	if(v==-1){printf("error");return 0;}
	signal(SIGIO,hdfn);
	while(1);
}
