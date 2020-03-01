#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include <signal.h>
#include <sys/types.h>
#include<sys/wait.h>
#include <unistd.h>
void handler(int sig, siginfo_t *info, void *ucontext)
{
	pid_t pid=info->si_pid;
	printf("%d\n",pid);
}
int main()
{
       /*int sigaction(int signum, const struct sigaction *act,
                     struct sigaction *oldact);
	*/
	pid_t pid=getpid();
	printf("%d\n",pid);
	struct sigaction act;
	act.sa_flags=SA_SIGINFO;
	act.sa_sigaction=&handler;
	int p=sigaction(SIGUSR1,&act,NULL);
	while(1);
}
