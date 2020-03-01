#include"header.h"
int main(int argc, char * argv[])
{
	while(1)
	{	
		for(int j=0;j<240000;j++);
		char x[30]="Input from Process1\n";
		printf("%s",x);
	}
	return 0;
}
