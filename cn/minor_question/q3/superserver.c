#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<unistd.h>
#include<fcntl.h>
#include <sys/time.h>
#include <sys/types.h>
#include <sys/select.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <netinet/ip.h>
#include <signal.h>

int max(int a,int b)
{
	if(a>b) return a;
	return b;
}
void hand(int sig, siginfo_t *info, void *ucontext)
{
	pid_t pid=info->si_pid;
	printf("%d\n",pid);
}
int main()
{
	int sfd[3];
	int cnt[3];
	struct sigaction act;
	act.sa_flags=SA_SIGINFO;
	act.sa_sigaction=&hand;
	sigaction(SIGUSR1,&act,NULL);
	struct sockaddr_in address;
	address.sin_family=AF_INET;
	address.sin_addr.s_addr=INADDR_ANY;
	for(int i=0;i<3;i++)
	{
		if((sfd[i]=socket(AF_INET,SOCK_STREAM,0))<0)
		perror("sfd");
		int p=8080+i;
		address.sin_port=htons(p);
		int opt=1;
		    if (setsockopt(sfd[i], SOL_SOCKET, SO_REUSEADDR | SO_REUSEPORT, &opt, sizeof(opt))) 
		    { 
			perror("setsockopt");
		    }
	    	int y;
		y=bind(sfd[i],(struct sockaddr*)&address,sizeof(address));
		if(y<0)
		perror("bind");
		y=listen(sfd[i],5);
		if(y<0)
		perror("listen");
		cnt[i]=0;		
	}
	fd_set rfds;
	while(1)
	{
		FD_ZERO(&rfds);
		int maxfd=0;
		for(int i=0;i<3;i++)
		{
			if(cnt[i]==0)
			{
				FD_SET(sfd[i],&rfds);
				maxfd=max(maxfd,sfd[i]);
			}
		}
		if(maxfd!=0)
		{
			maxfd++;
			int ret=select(maxfd,&rfds,NULL,NULL,NULL);
			if(ret==0||ret==-1) {continue;}
			else
			{
				printf("selected from super server\n");
				for(int i=0;i<3;i++)
				{
					if(cnt[i]==0 && FD_ISSET(sfd[i],&rfds))
					{
						int len=sizeof(address);
						int nsfd=accept(sfd[i],(struct sockaddr *)&address,(socklen_t *)&len);
						if(nsfd<0)
						perror("nsfd");
						printf("added client\n");
						cnt[i]=1;
						int c=fork();
						if(c==0)
						{
							for(int j=0;j<3;j++)
								if(j!=i)
									close(sfd[j]);
							char *args[]={"./se",NULL};
							dup2(sfd[i],0);
							execv(args[0],args);
						}
						else
						{
							close(nsfd);
						}
					}
				}
			}
		}
	}
	return 0;
} 
