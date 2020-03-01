#include"header.h"
struct msgbuf
{
	long type;
	char msg[100];
};
struct dict
{
	long pid;
};
int main()
{
	int key=25;
	struct dict d[100];
	int i=0;
	int msqid_r=msgget(key,IPC_CREAT|0666);
	key+=25;
	int msqid_s=msgget(key,IPC_CREAT|0666);
	struct msgbuf msg1;
	char buff[100];strcpy(buff,"");
	while(1)
	{//new ,mess
		msgrcv(msqid_r,&msg1,sizeof(msg1),0,0);
		printf("%s ",msg1.msg);
		long p=msg1.type;
		printf("%ld\n",p);
		if(strcmp(msg1.msg,"new")==0)
		{
			d[i++].pid=p;
			for(int j=0;j<i;j++)
			printf("p%ldp ",d[j].pid);
			printf("\n");
		}
		else
		{
			printf("value of i is %d\n",i);
			for(int j=0;j<i;j++)
			{
				if(p!=d[j].pid)
				{
					msg1.type=d[j].pid;
					msgsnd(msqid_s,&msg1,sizeof(msg1),0);
					printf("sending message to %ld\n",msg1.type);
				}
			}
		}
	}
	return 0;	
}
