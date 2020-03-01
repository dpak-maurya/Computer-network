#include"header.h"
int main()
{
	int pid;
	cout<<"pid of sm"<<endl;
	cin>>pid;
	//notify sm i am here
	int usfd;
    usfd=socket(AF_UNIX,SOCK_STREAM,0);
    perror("usfd");
    sockaddr_un usaddr;
    usaddr.sun_family=AF_UNIX;
    strcpy(usaddr.sun_path,"f1");
    unlink("f1");
    bind(usfd,(sockaddr *) &usaddr,sizeof(usaddr));
    perror("platform bind ");
    strcpy(usaddr.sun_path,"f1");
    connect(usfd,(sockaddr *) &usaddr,sizeof(usaddr));perror("connect");
    cout<<"Platform1\n";
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
