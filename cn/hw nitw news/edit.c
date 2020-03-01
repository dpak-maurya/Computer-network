#include"header.h"
struct msg
{
	long type;
	char mess[100];	
};
int main()
{
	int key=25;
	int msqid_r=msgget(key,0666|IPC_CREAT|/*IPC_NOWAIT*/);
	int msqid_s=msgget(50,0666|IPC_CREAT|/*IPC_NOWAIT*/);
	char buff[100];strcpy(buff,"\0");
	struct msg msg1;
	msg1.type=0;	
	while(1)
	{
		strcpy(buff,"");
		strcpy(msg1.mess,"");
		msgrcv(msqid_r,&msg1,sizeof(msg1),0,0);
		printf("message recevied with id %ld and message %s -\n",msg1.type,msg1.mess);
		if(msg1.mess[0]=='/' && msg1.mess[1]=='d')
		{
			//semd to dw
			int fd=open("dw.txt",O_WRONLY|O_APPEND);
			for(int i=0;i<strlen(msg1.mess)-2;i++)
			buff[i]=msg1.mess[i+2];
			buff[strlen(msg1.mess)-2]='\n';
			write(fd,buff,strlen(msg1.mess)-1);
			close(fd);
		}
		else
		{
			msgsnd(msqid_s,&msg1,sizeof(msg1),0);
		}
	}
	return 0;
}
