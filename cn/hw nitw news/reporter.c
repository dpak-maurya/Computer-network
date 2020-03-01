#include"header.h"
struct msg
{
	long type;
	char mess[100];	
};
int main()
{
	int key=25;
	int msqid=msgget(key,0666|IPC_CREAT);
	char buff[100];strcpy(buff,"\0");
	struct msg msg1;
	msg1.type=0;	
	while(1)
	{
		strcpy(buff,"");
		strcpy(msg1.mess,"");
		read(0,buff,100);
		strcpy(msg1.mess,buff);
		printf("message with id %ld and message %s -\n",msg1.type,msg1.mess);
		msgsnd(msqid,&msg1,sizeof(msg1),0);
	}
	return 0;
}
