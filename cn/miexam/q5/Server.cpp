#include"header.h"
int arrfd[2][50];
int cnt[2];
int service[3][50];
int cs;
void *fun(void * arg)
{
	int t=*((int *)arg);
	struct pollfd pfd[50];
	for(int i=0;i<50;i++)
	{
		pfd[i].events=0;
		pfd[i].revents=0;
		pfd[i].events|=POLLIN;
	}
	while(true)
	{
		for(int i=0;i<cnt[t];i++)
			pfd[i].fd=arrfd[t][i];
		int pret=poll(pfd,cnt[t],1000);
		if(pret==0||pret==-1){/*cout<<t<<endl;continue;*/}
		else
		{
			for(int i=0;i<cnt[t];i++)
			{
				if(pfd[i].revents & POLLIN)
				{
					char buffer[1024];
					read(pfd[i].fd,buffer,1024);
					cout<<"rev"<<endl;
					write(pfd[i].fd,buffer,strlen(buffer)+1);
					cout<<"snd"<<endl;
				}
			}
		}
	}
}
void handler(int signo,siginfo_t *info,void *ucontext)
{
	int pid=info->si_pid;
	if(signo==SIGUSR1)
	{
		int fl=0;
		for(int i=0;i<cs;i++)
		{
			if(service[0][i]==pid)
			{
				service[1][i]++;
				fl=1;
				break;
			}
		}
		if(fl==0)
		{
			service[0][cs]=pid;
			service[1][cs]=1;
			service[2][cs]=0;
			cs++;
		}
		for(int i=0;i<3;i++)
		{
			for(int j=0;j<cs;j++)
				cout<<service[i][j]<<" ";
			cout<<endl;
		}
	}
	else if(signo==SIGUSR2)
	{
		int fl=0;
		for(int i=0;i<cs;i++)
		{
			if(service[0][i]==pid)
			{
				service[2][i]++;
				fl=1;
				break;
			}
		}
		if(fl==0)
		{
			service[0][cs]=pid;
			service[1][cs]=0;
			service[2][cs]=1;
			cs++;
		}
		for(int i=0;i<3;i++)
		{
			for(int j=0;j<cs;j++)
				cout<<service[i][j]<<" ";
			cout<<endl;
		}
	}
}
int main()
{
    cout<<getpid()<<endl;
    sockaddr_in saddr;
    int sfd1=socket(AF_INET,SOCK_STREAM,0);
    setAddress(saddr,8081);
    int p=1;
    setsockopt(sfd1,SOL_SOCKET,SO_REUSEADDR| SO_REUSEPORT,&p,sizeof(p));
    bind(sfd1,(sockaddr *)&saddr,sizeof(saddr));
    perror("Bind");
    listen(sfd1,5);
    perror("Listen");
    
    int sfd2=socket(AF_INET,SOCK_STREAM,0);
    setAddress(saddr,8082);
    setsockopt(sfd2,SOL_SOCKET,SO_REUSEADDR| SO_REUSEPORT,&p,sizeof(p));
    bind(sfd2,(sockaddr *)&saddr,sizeof(saddr));
    perror("Bind");
    listen(sfd2,5);
    perror("Listen");
    
    cnt[0]=0;
    cnt[1]=0;
    pthread_t pt[2];
    int t1=0;
    pthread_create(&pt[0],NULL,&fun,(void *)&t1);
    int t2=1;
    pthread_create(&pt[1],NULL,&fun,(void *)&t2);
    
    struct sigaction act;
    act.sa_flags=SA_SIGINFO;
    act.sa_sigaction=&handler;
    sigaction(SIGUSR1,&act,NULL);
    sigaction(SIGUSR2,&act,NULL);
    cs=0;
    cout<<"Main server starting\n";
    while(true)
    {
        sockaddr_in caddr;
        socklen_t caddrlen;
        caddrlen=sizeof(caddr);
        struct pollfd pfd[2];
        pfd[0].fd=sfd1;pfd[1].fd=sfd2;
        pfd[0].events=0;pfd[0].events|=POLLIN;
        pfd[1].events=0;pfd[1].events|=POLLIN;
        pfd[0].revents=0;pfd[1].revents=0;
        int pret=poll(pfd,2,1000);
        if(pret==0||pret==-1)continue;
        else
        {
        	if(pfd[0].revents & POLLIN)
        	{
        		int nsfd=accept(sfd1,(sockaddr *)&caddr,&caddrlen);
        		perror("nsfd1");
        		cout<<"Client accepted "<<nsfd<<endl;
        		arrfd[0][cnt[0]]=nsfd;
        		cnt[0]++;
        		//cout<<cnt[0]<<endl;
        	}
        	else if(pfd[1].revents & POLLIN)
        	{
        		int nsfd=accept(sfd2,(sockaddr *)&caddr,&caddrlen);
        		perror("nsfd2");
        		cout<<"Client accepted "<<nsfd<<endl;
        		arrfd[1][cnt[1]]=nsfd;
        		cnt[1]++;
        	}
        }
    }
}
