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
struct msgbuff
{
	long type;
	char msg[100];
};
int main()
{
	printf("i am editor\n");
	int shmid=shmget(125,sizeof(struct shm),0666|IPC_CREAT);
	if(shmid<0)perror("error\n");
	struct shm *s=shmat(shmid,NULL,0);
	s->edit=getpid();s->dw1=0;s->dw2=0;s->dw3=0;
	s->proc_1=1;s->proc_2=0;
	int msqid=msgget(30,IPC_CREAT|0666);
	if(msqid<0)perror("error\n");
	struct msgbuff msg1;
	
	mkfifo("rf1",0660);
	int fd1=open("rf1",O_RDONLY|O_NONBLOCK);if(fd1<0)perror("error\n");
	mkfifo("rf2",0666|IPC_CREAT);
	int fd2=open("rf2",O_RDONLY|O_NONBLOCK);if(fd2<0)perror("error\n");
	mkfifo("rf3",0666|IPC_CREAT);
	int fd3=open("rf3",O_RDONLY|O_NONBLOCK);if(fd3<0)perror("error\n");
	printf("\nok\n");
	struct pollfd pofd[3];
	pofd[0].fd=fd1;pofd[1].fd=fd2;pofd[2].fd=fd3;
	pofd[0].events=pofd[1].events=pofd[2].events=0;
	pofd[0].events|=POLLIN;pofd[1].events|=POLLIN;pofd[2].events|=POLLIN;
	pofd[0].revents=pofd[1].revents=pofd[2].revents=0;
	int timeout=5000;
	while(1)
	{
		int ret=poll(pofd,3,timeout);
		if(ret==0)
			write(1,"timeout\n",8);
		else if(ret>0)
		{
			if(pofd[0].revents & POLLIN)
			{
				char buff[100];
				buff[0]='\0';
				int n=read(pofd[0].fd,buff,100);
				buff[n]='\0';
				write(0,buff,n+1);
				if(buff[0]=='/' && buff[1]=='d')
				{
					//close
					pofd[0].fd=0;
					close(fd1);
					write(1,"i closed it\n",12);
					s->dw1=1;
					printf("%d\n",s->dw1);
				}
				else
				{
					msg1.type=65;//msg type>0
					strcpy(msg1.msg,buff);
					msgsnd(msqid,&msg1,sizeof(msg1),0);
					write(1,"send to mess\n",13);
				}
			}
			if(pofd[1].revents & POLLIN)
			{
				char buff[100];
				buff[0]='\0';
				int n=read(pofd[1].fd,buff,100);
				buff[n]='\0';
				write(0,buff,n+1);
				if(buff[0]=='/' && buff[1]=='d')
				{
					//close
					pofd[1].fd=0;
					close(fd2);
					s->dw2=1;
				}
				else
				{
					msg1.type=0;
					strcpy(msg1.msg,buff);
					msgsnd(msqid,&msg1,sizeof(msg1),0);
				}
			}
			if(pofd[2].revents & POLLIN)
			{
				char buff[100];
				buff[0]='\0';
				int n=read(pofd[2].fd,buff,100);
				buff[n]='\0';
				write(0,buff,n+1);
				if(buff[0]=='/' && buff[1]=='d')
				{
					//close
					pofd[2].fd=0;
					close(fd3);
					s->dw3=1;
				}
				else
				{
					msg1.type=0;
					strcpy(msg1.msg,buff);
					msgsnd(msqid,&msg1,sizeof(msg1),0);
				}
			}
		}
		if(s->dw1==0)
			{fd1=open("rf1",O_RDONLY|O_NONBLOCK);pofd[0].fd=fd1;write(1,"i opened it\n",12);}
		if(s->dw2==0)
			fd2=open("rf2",O_RDWR);
		if(s->dw3==0)
			fd3=open("rf3",O_RDWR);
	}
	return 0;
}
