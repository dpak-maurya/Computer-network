#include"header.h"
int main()
{
	int fd[2];pipe(fd);
	int c=fork();
	if(c>0)
	{
		//close(fd[1]);
		sleep(2);
		char buff[100];
		write(1,"w",1);
		int n=read(fd[0],buff,100);
		if(n<0)perror("error");
		if(n==0)printf("no");
		write(1,buff,n);
	}
	else
	{
		char buff[10];strcpy(buff,"");
		sprintf(buff,"%d",fd[1]);
		char *args[]={"./r.out",buff,NULL};
		execv(args[0],args);
	}
	return 0;
}
