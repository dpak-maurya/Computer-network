#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<fcntl.h>
#include<unistd.h>
int main(int argc,char *argv[])
{
	char buffer[1024];
	buffer[0]='\0';
	int n;
	while(1)
	{
		memset(buffer,0,sizeof(buffer));
		n=read(0,buffer,1024);
		for(int i=0;i<n;i++)
		{
			if(buffer[i]>='A' && buffer[i]<='Z')
			buffer[i]=buffer[i]-'A'+'a';
		}
		write(1,buffer,n);	
	}
	return 0;
}
