#include "header.h"
int main()
{
	int pout=fileno(popen("./p5.out","w"));
	write(pout,"done5",5);
	return 0;
}
