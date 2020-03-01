#include"header.h"
int plat[2][3];
void handler(int signo,siginfo_t *info,void *ucontext)
{
	int pid=info->si_pid;
	if(signo==SIGUSR1)
	{
		int fl=1;
		for(int i=0;i<3;i++)
		{
			if(plat[0][i]==pid)
			{
				plat[i]=0;
				fl=0;
				break;
			}
		}
		if(fl==1)
		{
			for(int i=0;i<n;i++)
			{
				if(plat[0][i]==0)
				{
					plat[i]=pid;
					break;
				}
			}
		}
	}
	
}
int main()
{
	cout<<getpid()<<endl;
	plat[0][0]=0;plat[0][1]=0;plat[0][2]=0;
	plat[1][0]=0;plat[1][1]=0;plat[1][2]=0;
	struct sigaction act;
    act.sa_flags=SA_SIGINFO;
    act.sa_sigaction=&handler;
    sigaction(SIGUSR1,&act,NULL);
	
	int sfd[3];
	sockaddr_in saddr;
    sfd[0]=socket(AF_INET,SOCK_STREAM,0);
    setAddress(saddr,8081);
    int p=1;
    setsockopt(sfd[0],SOL_SOCKET,SO_REUSEADDR| SO_REUSEPORT,&p,sizeof(p));
    p=bind(sfd[0],(sockaddr *)&saddr,sizeof(saddr));
    if(p<0)perror("Bind in S\n");
    p=listen(sfd[0],5);
    if(p<0)
    perror("Listen error\n");
    
    sfd[1]=socket(AF_INET,SOCK_STREAM,0);
    setAddress(saddr,8082);
    p=1;
    setsockopt(sfd[1],SOL_SOCKET,SO_REUSEADDR| SO_REUSEPORT,&p,sizeof(p));
    p=bind(sfd[1],(sockaddr *)&saddr,sizeof(saddr));
    if(p<0)perror("Bind in S\n");
    p=listen(sfd[1],5);
    if(p<0)
    perror("Listen error\n");
    
    sfd[2]=socket(AF_INET,SOCK_STREAM,0);
    setAddress(saddr,8083);
    p=1;
    setsockopt(sfd[2],SOL_SOCKET,SO_REUSEADDR| SO_REUSEPORT,&p,sizeof(p));
    p=bind(sfd[2],(sockaddr *)&saddr,sizeof(saddr));
    if(p<0)perror("Bind in S\n");
    p=listen(sfd[2],5);
    if(p<0)
    perror("Listen error\n");
    
    cout<<"all train process are running"<<endl;
    int cnt_y=1;
    int usfd[cnt_y];
    usfd[0]=socket(AF_UNIX,SOCK_STREAM,0);perror("socket");
    sockaddr_un usaddr,ucaddr;
    socklen_t ucaddrlen;
    usaddr.sun_family=AF_UNIX;
    //system("rm SurajUnix");
    strcpy(usaddr.sun_path,"f1");
    unlink("f1");
    int x=bind(usfd[0],(sockaddr *) &usaddr,sizeof(usaddr));perror("Bind");
    listen(usfd[0],5);perror("listen ");
    int nusfd=accept(usfd[0],(sockaddr *)&ucaddr,&ucaddrlen);
    perror("nusfd0");
    usfd[0]=nusfd;
    
    /*usfd[1]=socket(AF_UNIX,SOCK_STREAM,0);perror("socket");
    usaddr.sun_family=AF_UNIX;
    //system("rm SurajUnix");
    strcpy(usaddr.sun_path,"f2");
    unlink("f2");
    x=bind(usfd[1],(sockaddr *) &usaddr,sizeof(usaddr));perror("Bind");
    listen(usfd[1],5);perror("listen ");
    nusfd=accept(usfd[1],(sockaddr *)&ucaddr,&ucaddrlen);
    perror("nusfd1");
    usfd[1]=nusfd;
    
    usfd[2]=socket(AF_UNIX,SOCK_STREAM,0);perror("socket");
    usaddr.sun_family=AF_UNIX;
    //system("rm SurajUnix");
    strcpy(usaddr.sun_path,"f3");
    unlink("f3");
    x=bind(usfd[2],(sockaddr *) &usaddr,sizeof(usaddr));perror("Bind");
    listen(usfd[2],5);perror("listen ");
    nusfd=accept(usfd[2],(sockaddr *)&ucaddr,&ucaddrlen);
    perror("nusfd2");
    usfd[2]=nusfd;*/
    
    cout<<"Finally"<<endl;
   	struct pollfd pfd[cnt_y];
    for(int i=0;i<3;i++)
    {
    	pfd[i].fd=sfd[i];
    	pfd[i].events=0;pfd[i].events|=POLLIN;
    	pfd[i].revents=0;
    	plat[i]=0;
    }
	socklen_t saddrlen=sizeof(saddr);
   	while(true)
    {
        int pret=poll(pfd,3,5000);
        if(pret==-1||pret==0)continue;
        else
        {
        	for(int i=0;i<3;i++)
        	{
        		if(pfd[i].revents & POLLIN)
        		{
        			//accept if empty
        			//if u dont accept then it will be polled again so no need to worry
        			for(int j=0;j<3;j++)
        			{
        				if(plat[j]==0)
        				{
        					plat[j]=1;
        					int nsfd=accept(sfd[i],(struct sockaddr *)&saddr,&saddrlen);
        					char s[2];
							strcpy(s,"1");
							//
							sock_fd_write(usfd[0],s,1,nsfd);
							cout<<"FD Written into socket\n";
        				}
        			}
        			//cout<<"polled"<<endl;
        		}
        	}
		}
        //close(nsfd);
    }
}
