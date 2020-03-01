#include"header.h"
int arrfd[2][50];
int cnt[2];
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
		if(pret==0||pret==-1)continue;
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
int main()
{
	int pid;
    cout<<"pid server"<<endl;
    cin>>pid;
    sockaddr_in saddr;
    int sfd1=socket(AF_INET,SOCK_STREAM,0);
    setAddress(saddr,8083);
    int p=1;
    setsockopt(sfd1,SOL_SOCKET,SO_REUSEADDR| SO_REUSEPORT,&p,sizeof(p));
    bind(sfd1,(sockaddr *)&saddr,sizeof(saddr));
    perror("Bind");
    listen(sfd1,5);
    perror("Listen");
    
    int sfd2=socket(AF_INET,SOCK_STREAM,0);
    setAddress(saddr,8084);
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
        		kill(pid,SIGUSR1);
        	}
        	else if(pfd[1].revents & POLLIN)
        	{
        		int nsfd=accept(sfd2,(sockaddr *)&caddr,&caddrlen);
        		perror("nsfd2");
        		cout<<"Client accepted "<<nsfd<<endl;
        		arrfd[1][cnt[1]]=nsfd;
        		cnt[1]++;
        		kill(pid,SIGUSR1);
        	}
        }
    }
}
