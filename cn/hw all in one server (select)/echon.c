#include"header.h"
int main(int argc, char * argv[])
{
	printf("%s\n",argv[1]);//server pipe
	int pfd=open(argv[1],O_WRONLY);//clientpiipe
	if(pfd<0) perror("client opening error\n");
	//signal(SIGINT,hdfn);
	while(1)
	{
		char Temp[1024];
		strcpy(Temp,"");
		scanf("%s",Temp);
		if(strcmp(Temp,"exit")==0)
		{
			char Str[100]="";
			strcat(Str,"X");
			strcat(Str,argv[1]);
			strcat(Str,"\n");
			int fd=open("famfifo",O_WRONLY);
			if(fd<0) perror("ERror opening famfifo\n");
			write(fd,Str,strlen(Str));
			close(fd);close(pfd);
			return 0;
		}
		else
		write(pfd,Temp,strlen(Temp)+1);
	}
	return 0;
}
