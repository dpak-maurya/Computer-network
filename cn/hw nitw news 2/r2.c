#include"header.h"
struct shm
{
	int proc_1;
	int proc_2;
	pid_t edit;
	pid_t lt;
	int dw1;
	int dw2;
	int dw3;
	int cnt;
};
int main()
{
	printf("i am reporter2\n");
	int shmid=shmget(125,sizeof(struct shm),0666|IPC_CREAT);
	if(shmid<0)perror("error\n");
	struct shm *s=shmat(shmid,NULL,0);
	mkfifo("rf2",0666|IPC_CREAT);
	int fd=open("rf2",O_WRONLY);
	char buff[100];
	buff[0]='\0';
	printf("pid of live telecaster is %d\n",s->lt);
	while(1)
	{
		int n=read(0,buff,100);
		buff[n]='\0';
		write(0,buff,n+1);
		write(fd,buff,n+1);
	}
	return 0;
}
