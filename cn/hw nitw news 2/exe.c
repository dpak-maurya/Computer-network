#include"header.h"
int main()
{
	int p=system("gcc r1.c -o r1");
	if(p<0) perror("System fault\n");
	system("gnome-terminal -- /bin/bash -c './r1 ;'");
	p=system("gcc l.c -o l");
	if(p<0) perror("System fault\n");
	p=system("gcc r2.c -o r2");
	if(p<0) perror("System fault\n");
	system("gnome-terminal -- /bin/bash -c './r2 ;'");
	p=system("gcc r3.c -o r3");
	if(p<0) perror("System fault\n");
	system("gnome-terminal -- /bin/bash -c './r3 ;'");
	p=system("gcc e.c -o e");
	if(p<0) perror("System fault\n");
	system("gnome-terminal -- /bin/bash -c './e ;'");
	p=system("gcc d.c -o d");
	if(p<0) perror("System fault\n");
	system("gnome-terminal -- /bin/bash -c './d ;'");
	p=system("gcc n1.c -o n1");
	if(p<0) perror("System fault\n");
	system("gnome-terminal -- /bin/bash -c './n1 ;'");
	p=system("gcc n2.c -o n2");
	if(p<0) perror("System fault\n");
	system("gnome-terminal -- /bin/bash -c './n2 ;'");
	return 0; 
}
