#include"header.h"
struct msgbuf
{
	long type;
	char msg[100];
};
int main()
{
	int key=25;
	int c=fork();
	if(c==0){
	int msqid=msgget(key,IPC_CREAT|0666);
	struct msgbuf msg1;
	msg1.type=1;
	strcpy(msg1.msg,"i am hero");
	msgsnd(msqid,&msg1,sizeof(msg1),0);printf("%d\n",msg1.type);//printf("%d\n",(int)getpid());
	printf("%s\n","ok");return 0;}
	wait(NULL);
	int msqid=msgget(key,0666|IPC_CREAT);
	struct msgbuf msg1;
	char buff[100];strcpy(buff,"");printf("%s\n","ok");
	msgrcv(msqid,&msg1,sizeof(msg1),1,0);
	printf("%s\n",msg1.msg);
	printf("%d\n",msg1.type);
	msgctl(msqid, IPC_RMID, NULL); 
	return 0;	
}
