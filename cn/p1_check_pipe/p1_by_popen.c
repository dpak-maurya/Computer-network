#include "header.h"
int main()
{
	int pp[2];
	pipe(pp);
	char buff[100];
	strcpy(buff,"HELLO WORLD");
	//dup2(pp[0],0);
	FILE *fd=popen("./p2","r");
	int fdptr=fileno(fd);
	read(fdptr,buff,100);
	printf("%s\n",buff);
	//read(*fd,buff,sizeof(buff));
	pclose(fd);
	return 0;
}
