#include"header.h"
int main(int argc, char * argv[])
{
	int fd=open("Famousfifo",O_WRONLY);//server pipe
	int pfd=open(argv[1],O_WRONLY);//clientpiipe
	while(1)
	{
		char Temp[1024];
		scanf("%s"Temp);
		if(strcmp(Temp,"EXIT")==0)
		{
			char Str[100]="";
			strcat(Str,"X");
			strcat(Str,argv[1]);
			strcat(Str,"|");
			write(fd,Str,strlen(Str));
		}
		else
		write(pfd,Temp,strlen(Temp));
	}
}
