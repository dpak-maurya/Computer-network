#include"header.h"
int main()
{
    int usfd;
    usfd=socket(AF_UNIX,SOCK_STREAM,0);
    sockaddr_un usaddr,ucaddr;
    socklen_t ucaddrlen;
    usaddr.sun_family=AF_UNIX;
    //system("rm SurajUnix");
    strcpy(usaddr.sun_path,"f1");
    unlink("f1");
    int x=bind(usfd,(sockaddr *) &usaddr,sizeof(usaddr));
    if(x<0)
    perror("Bind up error\n");
    listen(usfd,5);perror("listen ");
    int nusfd=accept(usfd,(sockaddr *)&ucaddr,&ucaddrlen);
    perror("nusfd");
    usfd=nusfd;
    
    cout<<"Server1\n";
    //while(true)
    {
        int fd=open("abc.txt",O_RDWR);
        int t=5;
        while(t--)
        {
        	char buffer;
        	buffer='\0';
        	while(read(fd,&buffer,1))
        	{
				write(1,&buffer,1);
				if(buffer=='\n')
				break;
		}
        }
        char s[2];
        strcpy(s,"1");
        sock_fd_write(usfd,s,1,fd);
        cout<<"FD Written into socket\n";
        //close(nsfd);
    }
}
