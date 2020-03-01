#include "header.h"
int main()
{
	system("g++ r.cpp -o r");
	system("g++ scene.cpp -o scene");
	system("g++ client1.c -o c1");
	system("g++ client2.c -o c2");
	system("./r");
	//run either ./c1 or ./c2 on terminal
}
