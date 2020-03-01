#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include <signal.h>

int main(int argc,char *argv[])
{
	int pid=atoi(argv[1]);//p2 pid
	printf("%d\n",pid);
	kill(pid,SIGUSR1);//send signal to p2
	printf("signal sent\n");
	pid=getpid();
	printf("my pid %d\n",pid);
	return 0;
}
