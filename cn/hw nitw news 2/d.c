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
	printf("i am document writer\n");
	int shmid=shmget(125,sizeof(struct shm),0666|IPC_CREAT);
	if(shmid<0)perror("error\n");//safety
	struct shm *s=shmat(shmid,NULL,0);
	int wr=open("out.txt",O_WRONLY|O_APPEND);
	if(wr<0)perror("error\n");
	char buff[100];
	buff[0]='\0';
	printf("%d\n",s->dw1);
	while(1)
	{
		printf("%d ",s->dw1);sleep(2);
		while(s->dw1==1)
		{
			int fd=open("rf1",O_RDONLY);
			int n=read(fd,buff,100);
			if(n==0)continue;
			buff[n]='\0';
			write(wr,buff,n+1);
			write(1,buff,n+1);
			close(fd);
			s->dw1=0;
			write(1,"exit",4);
		}
		if(s->dw2==1)
		{
			int fd=open("rf2",O_RDWR);
			int n=read(fd,buff,100);
			buff[n]='\0';
			write(wr,buff,n+1);
			write(1,buff,n+1);
			close(fd);
			s->dw2=0;
		}
		if(s->dw3==1)
		{
			int fd=open("rf3",O_RDWR);
			int n=read(fd,buff,100);
			buff[n]='\0';
			write(wr,buff,n+1);
			close(fd);
			write(1,buff,n+1);
			s->dw3=0;
		}
	}
	return 0;
}
