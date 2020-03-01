#include "header.h"
int main()
{
	int pp[2];
	pipe(pp);
	int sd=dup(1);
	dup2(pp[1],1);
	FILE *fp=popen("./p1.out","w");
	int fpr=fileno(fp);
	char buff[]={'1','2','3','4','5'};
	write(fpr,buff,5);
	close(fpr);
	
	char buff2[20];
	int n=read(pp[0],buff2,sizeof(buff2));
	buff2[n]='\0';
	write(sd,buff2,strlen(buff2)+1);
	return 0;
}
