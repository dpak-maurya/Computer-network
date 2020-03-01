#include"header.h"
int main(int argc, char * argv[])
{
	while(1)
	{
		char Buffer[1024]="";
		int p=read(0,Buffer,1024);
		if(p<=0)
		continue;
		printf("%s\n",Buffer);
	}
}
