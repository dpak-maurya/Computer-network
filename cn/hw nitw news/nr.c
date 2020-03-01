#include"header.h"
struct msg
{
	long type;
	char mess[100];	
};
int proc;
void hdfn()
{
	proc=0;
}
int main()
{
	int msqid_r=msgget(50,0666|IPC_CREAT|/*IPC_NOWAIT*/);
	char buff[100];strcpy(buff,"\0");
	struct msg msg1;
	msg1.type=0;
	signal(SIGUSR1,hdfn);
	while(1)
	{
		msgrcv(msqid_r,&msg1,sizeof(msg1),0,0);
		if(msg1.mess[0]>='0' &&  msg1.mess[0]<='9')
		{//live telecast
			kill(getpid(),SIGUSR1);
			
		}
	}
	return 0;
}
