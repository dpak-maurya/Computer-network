#include "header.h"
int main()
{
	int pp1[2];
	int pp2[2];
	pipe(pp1);
	pipe(pp2);
	int c=fork();
	if(c>0)
	{
		//parent
		close(pp2[1]);
		close(pp1[0]);
		char buff[100];
		strcpy(buff,"hello world");
		write(pp1[1],buff,100);
		close(pp1[1]);
		wait(NULL);
		
		char buff2[100];
		int n=read(pp2[0],buff2,100);
		//buff2[n]='\0';
		printf("%s\n",buff2);
		close(pp2[0]);
	}
	else 
	{
		//child
		close(pp2[0]);
		close(pp1[1]);
		char buff[100];
		int n=read(pp1[0],buff,100);
		//buff[n]='\0';
		printf("%s\n",buff);
		close(pp1[0]);
		
		char buff2[100];
		strcpy(buff2,"HELLO WORLD");
		write(pp2[1],buff2,100);
		close(pp2[1]);
	}
	return 0;
}
