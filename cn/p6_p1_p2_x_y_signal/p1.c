#include"header.h"
struct shm
{
	int x,y;
};
void hdfn(int signo)
{
	if(signo==SIGUSR2)
	{
		printf("signal from parent\n");
	}
	if(signo==SIGUSR1)
	{
		printf("signal from child\n");
	}
}
int main(int argc,char**argv)
{
	int c;
	int shmid=shmget(123,sizeof(struct shm),IPC_CREAT|0666);
	struct shm * sp=shmat(shmid,NULL,0);
	c=fork();
	if(c!=0)
	{
		sp=shmat(shmid,NULL,0);
		signal(SIGUSR1,hdfn);
		sp->x=atoi(argv[1]);
		sleep(1);
		kill(c,SIGUSR2);
		wait(NULL);
		printf("parent read from y %d\n",sp->y);
	}
	else
	{
		sp=shmat(shmid,NULL,0);
		signal(SIGUSR2,hdfn);
		sp->y=atoi(argv[2]);
		sleep(1);
		kill(getppid(),SIGUSR1);
		printf("child read from x %d\n",sp->x);
	}
	return 0;
}
