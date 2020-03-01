#include "header.h"
int main()
{
	system("g++ Server.cpp -o Server -lpthread");
	system("g++ A.cpp -o A -lpthread");
	system("g++ client1.c -o c1");
	system("g++ client2.c -o c2");
	system("./Server");
	//run ./A on seperate terminal
	//run either ./c1 or ./c2 on terminal
}
