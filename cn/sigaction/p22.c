#include <stdio.h>
#include <unistd.h>
#include <signal.h>
#include <string.h>
 
static void hdl(int sig, siginfo_t *siginfo, void *context)
{
long x = siginfo->si_pid;
printf("Sending PID - %ld\n",x);
}

int main (int argc, char *argv[])
{
struct sigaction act;
 printf("my pid is %d\n",getpid());
memset (&act, '\0', sizeof(act));
 
act.sa_sigaction = &hdl;

act.sa_flags = SA_SIGINFO;

if (sigaction(SIGUSR1, &act, NULL) < 0) {
perror ("sigaction");
return 1;
}

while(1) sleep(1);
 
}
