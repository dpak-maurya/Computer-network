#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include <signal.h>
#include<unistd.h>
#include<netdb.h>
#include<arpa/inet.h>
#include<sys/socket.h>
#include<errno.h>
#include<fcntl.h>
#include<sys/stat.h>
#include<sys/time.h>
#include <sys/select.h>
#include <sys/types.h>
#include <sys/shm.h>

struct shmp
{
	int arr[100];
	int curr;
	char mess[100];
	int receiver;
	int fs;
};
int flag;
int rece;
char buff[100];
int p_m;
struct shmp *shm;
void hand(int signo)
{
	
	if(signo==SIGUSR1)
	{//data
		int pid=getpid();
		if(shm->receiver==pid)
		{
			char buff2[100];
			memset(buff2,0,sizeof(buff2));
			strcpy(buff2,shm->mess);
			write(1,buff2,strlen(buff2)+1);
			shm->fs=1;
			for(int i=0;i<shm->curr;i++)
			{
				if(shm->arr[i]==pid)
				{
					if(i+1<shm->curr)
					kill(shm->arr[i+1],SIGUSR2);
					else
					kill(shm->arr[0],SIGUSR2);
				}
			}
		}
		else
		{
			for(int i=0;i<shm->curr;i++)
			{
				if(shm->arr[i]==pid)
				{
					if(i+1<shm->curr)
					kill(shm->arr[i+1],SIGUSR1);
					else
					kill(shm->arr[0],SIGUSR1);
				}
			}
		}
	}
	else if(signo==SIGUSR2)
	{//token
		if(p_m==1)
		{	
			if(shm->fs==1)
			{
				p_m=0;
				printf("success\n");
				shm->fs=0;
				p_m=0;
				strcpy(shm->mess,"\0");
			}
		}
		if(flag==0)
		{
			//pass
			int pid=getpid();
			for(int i=0;i<shm->curr;i++)
			{
				if(shm->arr[i]==pid)
				{
					if(i+1<shm->curr)
					kill(shm->arr[i+1],SIGUSR2);
					else
					kill(shm->arr[0],SIGUSR2);
				}
			}
		}
		else if(flag==1)
		{//messgae to pass
			strcpy(shm->mess,buff);
			shm->receiver=rece;
			flag=0;
			p_m=1;
			int pid=getpid();
			for(int i=0;i<shm->curr;i++)
			{
				if(shm->arr[i]==pid)
				{
					if(i+1<shm->curr)
					kill(shm->arr[i+1],SIGUSR1);
					else
					kill(shm->arr[0],SIGUSR1);
				}
			}
		}
	}
	else if(signo==SIGINT)
	{//mess
		printf("message\n");
		read(0,buff,sizeof(buff));
		printf("reveiver pid");
		scanf("%d\n",&rece);
		flag=1;
	}
}
int main()
{
	printf("%d\n",getpid());
	int key=ftok("abc",75);
	//int msqid=msgget(key,IPC_CREAT|0666);
	int shmid=shmget(key,sizeof(struct shmp),IPC_CREAT|0666);
	shm=shmat(shmid,NULL,0); 
	
	shm->curr=0;
	for(int i=0;i<100;i++)
	shm->arr[i]=-1;
	shm->arr[shm->curr++]=getpid();
	
	struct sigaction act;
	act.sa_flags=SA_SIGINFO;
	act.sa_sigaction=hand;
	sigaction(SIGUSR1,&act,NULL);
	sigaction(SIGUSR2,&act,NULL);
	sigaction(SIGINT,&act,NULL);
	p_m=0;flag=0;
	raise(SIGUSR2);
	while(1);
	return 0;
}
