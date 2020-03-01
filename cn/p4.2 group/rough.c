#include "header.h"
int main()
{
	/*pid_t pid;
	pid=getppid();
	printf("%d\n",pid);
	char buff[50];
	sprintf(buff,"%d",pid);
	printf("%s\n",buff);
	strcat(buff," ");
	strcat(buff,"hello");char *token=NULL;
	char *delimiter;
	delimiter=" ";
	token=strtok(buff,delimiter);
	    while(token!=NULL){
	    printf("%s  ",token); //or store 
	    token=strtok(NULL,delimiter);
	    }*/
	/*int fp;
	char buff[100];int neo; 
	fp = open("common.txt", O_RDONLY);
	while((neo=read(fp,buff,sizeof(buff)))!=0)
	{printf("%s\n",buff);}*/
	/*char buff;
	char token[100];
	int fd=open("c.txt",O_RDWR);int n;int i;
	while( (n=read(fd,&buff,sizeof(buff)))!=0)
	{
		if(buff==' '|| buff=='\n'){token[i]='\0';printf("%d\n",atoi(token));i=0;}
		else{token[i++]=buff;}
	}*/char buff[100];
	buff[0]='2';buff[1]='2';buff[2]='2';
	printf("%d\n",atoi(buff));
	return 0;
}
