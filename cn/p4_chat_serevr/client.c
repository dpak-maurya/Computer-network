#include "header.h"
int fd;
void *reader(void * s)
{
	char buff[100];
	while(1)
	{
		int n=read(fd,buff,sizeof(buff));
		if(n==0){}
		else
		{
			buff[n]='\0';
			write(1,buff,strlen(buff)+1);
		}
	}
}
void * writter(void *s)
{
	char buff[100];
	pid_t pid;
	pid=getpid();
	int len=0;
	int tmp=pid;
	while(tmp!=0)
	{len++;tmp/=10;}
	char buff2[len];
	sprintf(buff2,"%d",pid);
	int fds=open("ffifo",O_RDWR);
	while(1)
	{
		int n=read(0,buff,sizeof(buff));
		if(n==0){}
		else
		{
			buff[n]='\0';
			char buff3[100];
			strcat(buff3,buff2);
			char ck;ck='/';
			strncat(buff3,&ck,1);
			strcat(buff3,buff);
			//printf("%s",buff);
			//printf("%s %c %s %s \n",buff2,'/',buff,buff3);
			write(fds,buff3,strlen(buff3)+1);
			write(1,buff3,strlen(buff3)+1);
			//printf("%d\n",strlen(buff3)+1);
			buff3[0]='\0';
		}
	}
}
int main(int argc,char **argv)
{
	pthread_t t[2];
	pid_t pid;
	pid=getpid();
	int len=0;
	int tmp=pid;
	//without finding len it will give grabage
	while(tmp!=0)
	{len++;tmp/=10;}
	char buff[len];
	sprintf(buff,"%d",pid);
	//client file
	mkfifo(buff,0666);
	fd=open(buff,O_RDWR);
	//write in comman file with both apppend and wronly
	int fd2=open("common.txt",O_WRONLY|O_APPEND);
	char c='\n';
	write(fd2,buff,len);
	write(fd2,&c,1);
	close(fd2);
	pthread_create(&t[0],NULL,reader,NULL);
	pthread_create(&t[1],NULL,writter,NULL);
	pthread_join(t[0],NULL);
	pthread_join(t[1],NULL);
	return 0;
}
