#include"header.h"
int main()
{
    system("g++ Server.cpp -o Server ");
    system("g++ SpecialServer.cpp -lpthread -o SS");
    system("./Server &");
    system("./SS");
    // Use telnet localhost 8083 on a separate terminal as client
    // Just run g++ Launch.cpp
    // ./a.out on a single terminal
}