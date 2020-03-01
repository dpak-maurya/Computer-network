#include"header.h"
int main(int argc, char * argv[])
{
	/*int nsfd=atoi(argv[1]);//nsfd
	pritnf("%d\n",nsfd);
	while(1)
	{
		printf("hello\n");
		char Temp[1024];
		strcpy(Temp,"");
		scanf("%s",Temp);
		printf("%s\n",Temp);
		if(strcmp(Temp,"exit")==0)
		{
			write(1,"I\n",2);
			mkfifo("echonpipe",0666);
			int efd=open("echonpipe",O_WRONLY);
			char Str[100]="";
			strcat(Str,argv[1]);
			strcat(Str,"\n");
			write(efd,Str,strlen(Str));
			close(efd);
			return 0;
		}
		else
		write(nsfd,Temp,strlen(Temp)+1);
	}*/
	for(int i=0;i<2;i++)
	{
		write(1,"hello from echon\n",17);
		sleep(2);
	}
	mkfifo("echonpipe",0666);
	int efd=open("echonpipe",O_WRONLY);
	write(efd,argv1,sizeof(argv1));
	close(efd);
	return 0;
}
