#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>
#include <string.h>
#include <fcntl.h>
#include <sys/syscall.h>

int main()
{
system("pgrep p22 > abc.txt");

int fd = open("abc.txt",O_RDONLY);

char x[100];
int n=read(fd,x,100);
x[n]='\0';
printf("PID of P1 - %s\n",x);

kill(atoi(x),SIGUSR1);


return 0;
}
