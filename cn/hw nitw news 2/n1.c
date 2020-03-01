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
	printf("i am news reader1\n");
	int shmid=shmget(125,sizeof(struct shm),0666|IPC_CREAT);
	if(shmid<0)perror("error\n");
	else perror("no\n");
	struct shm *s=shmat(shmid,NULL,0);
	write(1,"hello0",6);
	int msqid=msgget(30,IPC_CREAT|0666|IPC_NOWAIT);
	if(msqid<0)perror("error\n");
	else perror("no\n");
	struct msgbuff msg1;
	while(1)
	{
		while(s->proc_1==0)
		{write(1,"hello1",6);sleep(1);}
		write(1,"hello2",6);
		char buff[100];buff[0]='\0';
		msgrcv(msqid,&msg1,sizeof(msg1),0,0);
		write(1,"hello3",6);
		if(msg1.msg[0]>='0' && msg1.msg[0]<='9')
		{
			//livecast
			int c=fork();
			if(c!=0)
			wait(NULL);
			else
			{
				
				char *args[]={"./l",msg1.msg,NULL};
				execv(args[0],args);
			}
		}
		else
		{
			write(1,&msg1.msg,strlen(msg1.msg)+1);
		}
		s->proc_2=1;
		s->proc_1=0;
	}
	
	return 0;
}
