#include "header.h"
int main(int argc,char **argv)
{
	char buff;char token[100];int fd;
	/*int fp = open("common.txt", O_RDONLY);int p=0;int i=0;int n;
	while( (n=read(fp,&buff,sizeof(buff)))!=0)
	{
		if(buff==' '|| buff=='\n'){fd[p++]=open(token,O_RDWR);i=0;}
		else{token[i++]=buff;}
	}
	close(fp);*/
	int fds;
	mkfifo("ffifo",0666);
	fds=open("ffifo",O_RDONLY);
	char mess[100];
	printf("chat boot is active\n");
	while(1)
	{
		//read
		char buffer[100];
		char fdw[100];
		int size=read(fds,buffer,sizeof(buffer));
		if(size==0)continue;
		buffer[size]='\0';	
		//sleep(1);i=0;int h=0;
		int sl=0;
		for(int t=0;t<strlen(buffer);t++)
		{
			if(buffer[t]=='/')
			{
				printf("received message from %s\n",token);
				strcpy(fdw,token);
				sl=0;
				for(int j=t+1;j<strlen(buffer);j++)
				token[sl++]=buffer[j];
				token[sl]='\0';
				strcpy(mess,token);
				//printf("message is %s\n",token);
				break;
			}
			else{token[sl++]=buffer[t];}
		}	
		//write
		/*for(int j=0;j<p;j++)
		{
			if(fd[j]!=fdw)
			{write(fd[j],mess,strlen(mess)+1);printf("I wrote in %d\n",fd[j]);}
		}*/
		int fp = open("common.txt", O_RDONLY);int i=0;int n;
		while( (n=read(fp,&buff,sizeof(buff)))!=0)
		{
			if(buff==' '|| buff=='\n')
			{
				token[i]='\0';
				if(strcmp(token,fdw)!=0)
				{
					fd=open(token,O_RDWR);
					write(fd,mess,strlen(mess)+1);
					printf("message sent to %s\n",token);
					close(fd);
				}
				i=0;
			}
			else{token[i++]=buff;}
		}
		close(fp);
	}
	return 0;
}
