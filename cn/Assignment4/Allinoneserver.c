#include"header.h"
int main()
{
	int p=system("gcc Process1.c -o Process1");
	if(p<0) perror("System fault\n");
	p=system("gcc Process2.c -o Process2");
	if(p<0) perror("System fault 2\n");
	system("gcc Process3.c -o Process3");
	if(p<0) perror("System fault 3\n");
	system("gcc Process4.c -o Process4");
	system("gcc Process5.c -o Process5");
	system("gcc Server.c -o Server");
	if(p<0) perror("System fault S\n");
	system("./Server");
	return 0; 
}
