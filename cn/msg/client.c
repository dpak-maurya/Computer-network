#include"header.h"
struct msgbuf
{
	long type;
	char msg[100];
};
int main()
{
	int key=25;
	int msqid_s=msgget(key,IPC_CREAT|0666);
	key+=25;
	int msqid_r=msgget(key,IPC_CREAT|0666|IPC_NOWAIT);
	struct msgbuf msg1;
	char buff[100];strcpy(buff,"");
	//new
	msg1.type=getpid();
	strcpy(msg1.msg,"new");
	printf("my id is%ld\n",msg1.type);
	msgsnd(msqid_s,&msg1,sizeof(msg1),0);
	int c=fork();
	if(c==0)
	{
		int msqid_r=msgget(50,IPC_CREAT|0666);
		while(1)
		{//mess
			msgrcv(msqid_r,&msg1,sizeof(msg1),msg1.type,0);//block
			printf("message received is %s\n",msg1.msg);
		}	
	}
	else
	{
		int msqid_s=msgget(25,IPC_CREAT|0666);
		while(1)
		{
			strcpy(buff,"");
			int n=read(0,buff,100);buff[n]='\0';
			if(n==0)
			sleep(1);
			else
			{
				strcpy(msg1.msg,buff);
				printf("message to send is %s\n",msg1.msg);
				msgsnd(msqid_s,&msg1,sizeof(msg1),0);
			}
		}
	}
	return 0;	
}
