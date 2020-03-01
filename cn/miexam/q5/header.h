#include<bits/stdc++.h>
#include<sys/socket.h>
#include<sys/stat.h>
#include<sys/types.h>
#include<fcntl.h>
#include<unistd.h>
#include<sys/un.h>
#include<arpa/inet.h>
#include<pthread.h>
#include <poll.h>
using namespace std;
void setAddress(struct sockaddr_in &Addr, int portno)
{
    Addr.sin_addr.s_addr=INADDR_ANY;
    Addr.sin_port=htons(portno);
    Addr.sin_family=AF_INET;
}
/*
    struct sigaction act;
    act.sa_flags=SA_SIGINFO;
    act.sa_sigaction=&handler;
    sigaction(SIGUSR1,&act,NULL);
    sigaction(SIGUSR2,&act,NULL);
*/
/*
void handler(int signo,siginfo_t *info,void *ucontext)
{
	if(signo==SIGUSR1)
	{
		int pid=info->si_pid;
	}
	else if(signo==SIGUSR2)
	{
	
	}
}
*/
