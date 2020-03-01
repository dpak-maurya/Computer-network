#include"header.h"
void * ServiceThread(void * Arg)
{
    int nsfd=*(int *) Arg;
    while(true)
    {
        char Buffer[1024];
        strcpy(Buffer,"");
        recv(nsfd,Buffer,1024,0);
        cout<<"rcv"<<endl;
        for(int i=0;Buffer[i]!='\0';i++)
        {
            Buffer[i]=toupper(Buffer[i]);
        }
        send(nsfd,Buffer,strlen(Buffer)+1,0);
        cout<<"sent"<<endl;
    }
}
int main()
{
    sleep(1);
    int usfd;
    usfd=socket(AF_UNIX,SOCK_STREAM,0);
    sockaddr_un usaddr;
    usaddr.sun_family=AF_UNIX;
    strcpy(usaddr.sun_path,"SurajUnix1");
    unlink("SurajUnix1");
    int p=bind(usfd,(sockaddr *) &usaddr,sizeof(usaddr));
    if(p<0)
    perror("Special server bind error\n");
    pthread_t Threads[10];
    int sthread;
    int ClientNFDS[10];
    strcpy(usaddr.sun_path,"SurajUnix");
    connect(usfd,(sockaddr *) &usaddr,sizeof(usaddr));perror("connect");
    cout<<"Special Server Starting\n";
    while(true)
    {
        char Buffer[111];
        int tsfd;
        sock_fd_read(usfd,Buffer,111,&tsfd);
        cout<<"Read fd\n";
        ClientNFDS[sthread]=tsfd;
        pthread_create(&Threads[sthread],NULL,ServiceThread,&tsfd);
        sthread++;
    }
}
