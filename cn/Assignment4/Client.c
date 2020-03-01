#include"header.h"
int main()
{
	char Buff[1024]="";
	int fd=open("Famousfifo",O_WRONLY);
	int pid=getpid();
	char temp[10];
	strcpy(temp,"");
	snprintf(temp,10,"%d",pid);
	strcat(Buff,"#");
	strcat(Buff,temp);
	strcat(Buff,"|");
	write(fd,Buffer,strlen(Buffer));
	sleep(2);
	int f=open(temp,O_RDONLY|O_NONBLOCK);
	while(1)
	{
		char Buffer[1024];
		int r=read(f,Buffer,1024);
		if(r<=0) continue;
		else printf("%s",Buffer);
	}
	return 0;	
}
