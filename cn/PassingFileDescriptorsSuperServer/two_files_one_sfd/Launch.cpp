#include"header.h"
int main()
{
    system("g++ Server.cpp -o Server ");
    system("g++ SpecialServer.cpp -o SS");
    system("./Server &");
    system("./SS");
    // Just run g++ Launch.cpp -o L
    // ./L on a single terminal
}
