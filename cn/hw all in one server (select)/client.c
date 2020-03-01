#include "header.h"
int main()
{
	mkfifo("famfifo",0666);
	int sfd=open("famfifo",O_WRONLY);
	
	char buff[10];buff[0]='\0';
	sprintf(buff,"%d",(int)getpid());
	
	char me='#';write(sfd,&me,1);
	me='\n';
	write(sfd,buff,strlen(buff));
	write(1,buff,strlen(buff)+1);
	write(sfd,&me,1);
	write(1,&me,1);
	close(sfd);
	me='#';
	write(1,&me,1);
	mkfifo(buff,0666);
	int nsfd=open(buff,O_RDONLY|O_NONBLOCK);// will continue if no one to write non block with read
	buff[0]='\0';
	strcpy(buff,"");
	int n;
	write(1,&me,1);
	while(1)
	{
		n=read(nsfd,buff,sizeof(buff));
		if(n<0)
		{//perror("here");
		}
		else
		{
			write(1,buff,n);
			buff[0]='\0';
		}
	}
	return 0;
}
