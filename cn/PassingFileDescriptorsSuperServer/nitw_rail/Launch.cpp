#include"header.h"
int main()
{
    system("g++ SM.cpp -o SM ");
    system("g++ T1.cpp -o T1");
    system("g++ T2.cpp -o T2");
    system("g++ T3.cpp -o T3");
    system("g++ P1.cpp -o P1");
    system("g++ P2.cpp -o P2");
    system("g++ P3.cpp -o P3");
    system("./SM");
    // Just run g++ Launch.cpp -o L
    // ./L on a single terminal
    // ./T1 or ./T2 or ./T3
}
