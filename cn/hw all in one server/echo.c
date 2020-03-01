#include"header.h"
int main(int arc,char * argv[])
{
	int nsfd=open(argv[1],O_RDWR);
	char buff[100];buff[0]='\0';
	int n;
	while(n=read(0,buff,sizeof(buff)))
	{
		if(n!=0 && buff[0]!='#')
		{
			write(nsfd,buff,n);
		}
		else if(n==1 && buff[0]=='#')
		{
			break;
		}
	}
	
	return 0;
}
