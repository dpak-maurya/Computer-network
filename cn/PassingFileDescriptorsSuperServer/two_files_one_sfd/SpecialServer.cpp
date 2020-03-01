#include"header.h"
int main()
{
    sleep(1);
    int usfd;
    usfd=socket(AF_UNIX,SOCK_STREAM,0);
    sockaddr_un usaddr;
    usaddr.sun_family=AF_UNIX;
    /*strcpy(usaddr.sun_path,"SurajUnix1");
    unlink("SurajUnix1");
    int p=bind(usfd,(sockaddr *) &usaddr,sizeof(usaddr));
    if(p<0)
    perror("Special server bind error\n");*/
    strcpy(usaddr.sun_path,"f1");
    connect(usfd,(sockaddr *) &usaddr,sizeof(usaddr));perror("connect");
    cout<<"Server2\n";
    //while(true)
    {
        char Buffer[111];
        int tsfd;
        sock_fd_read(usfd,Buffer,111,&tsfd);
        while(1)
        {
        	char buffer;
        	while(read(tsfd,&buffer,1))
        	{
			write(1,&buffer,1);
			if(buffer=='\n')
			break;
		}
	}
        cout<<"Read fd\n";
    }
}
