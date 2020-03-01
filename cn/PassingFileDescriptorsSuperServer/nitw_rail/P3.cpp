#include"header.h"
int main()
{
	int pid;
	cout<<"pid of sm"<<endl;
	cin>>pid;
	//notify sm i am here
	kill(pid,SIGUSR2);
    //sleep(1);
    int usfd;
    usfd=socket(AF_UNIX,SOCK_STREAM,0);
    sockaddr_un usaddr;
    usaddr.sun_family=AF_UNIX;
    /*strcpy(usaddr.sun_path,"SurajUnix1");
    unlink("SurajUnix1");
    int p=bind(usfd,(sockaddr *) &usaddr,sizeof(usaddr));
    if(p<0)
    perror("Special server bind error\n");*/
    strcpy(usaddr.sun_path,"f3");
    connect(usfd,(sockaddr *) &usaddr,sizeof(usaddr));perror("connect");
    cout<<"Platform3\n";
    while(true)
    {
        char Buffer[111];
        int tsfd;
        sock_fd_read(usfd,Buffer,111,&tsfd);
        
		char buffer[100];
		read(tsfd,buffer,100);
		write(1,buffer,strlen(buffer)+1);
		
		read(tsfd,buffer,100);
		//exit notify station
		kill(pid,SIGUSR1);
        cout<<"Read fd\n";
    }
}
