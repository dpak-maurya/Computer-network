#include "header.h"
int main()
{
	int pp[2];
	pipe(pp);
	char buff[]={'1','2','3','4','5','6'};
	write(pp[1],buff,sizeof(buff));
	dup2(pp[0],0);
	FILE *fp=popen("./p1.out","r");
	
	
	char buff2[20];
	int fpr=fileno(fp);
	read(fpr,buff2,sizeof(buff2));
	close(fpr);
	
	write(1,buff2,strlen(buff2)+1);
	return 0;
}
