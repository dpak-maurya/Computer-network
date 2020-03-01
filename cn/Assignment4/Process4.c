#include"header.h"
int main(int argc, char * argv[])
{
	while(1)	
	{
		char  ip[10];
		scanf("%s",ip);
		//if(ip=="KILL")
		{
			kill(atoi(argv[1]),SIGUSR1);
			sleep(1);	
		}
	}
	return 0;
}
