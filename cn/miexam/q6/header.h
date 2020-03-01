#include<bits/stdc++.h>
#include <signal.h>
#include<unistd.h>
#include<netdb.h>
#include<arpa/inet.h>
#include<sys/socket.h>
#include<errno.h>
#include<fcntl.h>
#include<sys/stat.h>
#include<sys/time.h>
#include <sys/select.h>
#include <sys/types.h>
#include <sys/shm.h>
using namespace std;
void setAddress(struct sockaddr_in &Addr, int portno)
{
    Addr.sin_addr.s_addr=INADDR_ANY;
    Addr.sin_port=htons(portno);
    Addr.sin_family=AF_INET;
}
