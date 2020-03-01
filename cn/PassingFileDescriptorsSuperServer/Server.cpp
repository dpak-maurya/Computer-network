#include"header.h"
int main()
{
    int usfd;
    usfd=socket(AF_UNIX,SOCK_STREAM,0);
    sockaddr_un usaddr,ucaddr;
    socklen_t ucaddrlen;
    usaddr.sun_family=AF_UNIX;
    //system("rm SurajUnix");
    strcpy(usaddr.sun_path,"SurajUnix");
    unlink("SurajUnix");
    int x=bind(usfd,(sockaddr *) &usaddr,sizeof(usaddr));
    if(x<0)
    perror("Bind up error\n");
    listen(usfd,5);perror("listen ");
    int nusfd=accept(usfd,(sockaddr *)&ucaddr,&ucaddrlen);
    perror("nusfd");
    usfd=nusfd;
    
    sockaddr_in saddr;
    int sfd=socket(AF_INET,SOCK_STREAM,0);
    setAddress(saddr,8083);
    int p=1;
    setsockopt(sfd,SOL_SOCKET,SO_REUSEADDR| SO_REUSEPORT,&p,sizeof(p));
    p=bind(sfd,(sockaddr *)&saddr,sizeof(saddr));
    if(p<0)perror("Bind in S\n");
    p=listen(sfd,5);
    if(p<0)
    perror("Listen error\n");
    cout<<"Main server starting\n";
    while(true)
    {
        sockaddr_in caddr;
        socklen_t caddrlen;
        caddrlen=sizeof(caddr);
        int nsfd=accept(sfd,(sockaddr *)&caddr,&caddrlen) ;
        perror("nsfd");
        cout<<"Client accepted "<<nsfd<<endl;
        char s[2];
        strcpy(s,"1");
        sock_fd_write(usfd,s,1,nsfd);
        cout<<"FD Written into socket\n";
        //close(nsfd);
    }
}
