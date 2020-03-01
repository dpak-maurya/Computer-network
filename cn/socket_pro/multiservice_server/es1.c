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
		n=read(0,buffer,1024);
		for(int i=0;i<n;i++)
		{
			if(buffer[i]>='a' && buffer[i]<='z')
			buffer[i]=buffer[i]-'a'+'A';
		}
		write(1,buffer,n);
		buffer[0]='\0';		
	}
	return 0;
}
