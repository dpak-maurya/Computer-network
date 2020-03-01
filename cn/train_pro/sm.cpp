#include"header.h"
#define ADDRESS1  "mysocket1"
#define ADDRESS2  "mysocket2"
#define ADDRESS3  "mysocket3"
int p[3];int pidarr[3];
void hand(int sig,siginfo_t *info,void *ucontext)
{
	int pid=info->si_pid;
	if(sig==SIGUSR1)
	{
		for(int i=0;i<3;i++)
		{
			if(pidarr[i]==pid)
			{
				p[i]=0;
				cout<<status<<" "<<p[0]<<" "p[1]<<" "p[2]<<endl;
				break;
			}
		}
	}
}        
int main()
{
	cout<<getpid()<<endl;
	struct sigaction act;
	act.sa_flags=SA_SIGINFO;
	act.sa_sigaction=&hand;
	sigaction (SIGUSR1,&act,NULL);
	for(int i=0;i<3;i++)
	p[i]=0;
	//for t.cpp
	int sfd;
	struct sockaddr_in serv_addr,cli_addr;
	socklen_t cli_len;
	int port_no=8081;
	if((sfd = socket(AF_INET,SOCK_STREAM,0))==-1)
	perror("\n socket ");
	else printf("\n socket created successfully");
	bzero(&serv_addr,sizeof(serv_addr));
	serv_addr.sin_family = AF_INET;
	serv_addr.sin_port = htons(port_no);
	serv_addr.sin_addr.s_addr = INADDR_ANY;
	if(bind(sfd,(struct sockaddr *) &serv_addr,sizeof(serv_addr))==-1)
	perror("\n bind : ");
	else printf("\n bind successful ");
	listen(sfd,10);
	
	// for p.cpp
	int  usfd[3];
	
	struct sockaddr_un userv_addr,ucli_addr;
  	socklen_t userv_len,ucli_len;
  	
	usfd[0] = socket(AF_UNIX , SOCK_STREAM , 0);
	perror("socket");
  	bzero(&userv_addr,sizeof(userv_addr));
  	userv_addr.sun_family = AF_UNIX;
	strcpy(userv_addr.sun_path, ADDRESS1);
	unlink(ADDRESS1);
	userv_len = sizeof(userv_addr);
	if(bind(usfd[0], (struct sockaddr *)&userv_addr, userv_len)==-1)
	perror("server: bind");
	listen(usfd[0], 5);
	
	usfd[1] = socket(AF_UNIX , SOCK_STREAM , 0);
	perror("socket");
  	bzero(&userv_addr,sizeof(userv_addr));
  	userv_addr.sun_family = AF_UNIX;
	strcpy(userv_addr.sun_path, ADDRESS2);
	unlink(ADDRESS2);
	userv_len = sizeof(userv_addr);
	if(bind(usfd[1], (struct sockaddr *)&userv_addr, userv_len)==-1)
	perror("server: bind");
	listen(usfd[1], 5);
	
	usfd[2] = socket(AF_UNIX , SOCK_STREAM , 0);
	perror("socket");
  	bzero(&userv_addr,sizeof(userv_addr));
  	userv_addr.sun_family = AF_UNIX;
	strcpy(userv_addr.sun_path, ADDRESS3);
	unlink(ADDRESS3);
	userv_len = sizeof(userv_addr);
	if(bind(usfd[2], (struct sockaddr *)&userv_addr, userv_len)==-1)
	perror("server: bind");
	listen(usfd[2], 5);
	ucli_len=sizeof(ucli_addr);

	int nusfd[3];
	for(int i=0;i<3;i++)
	nusfd[i]=-1;
	
	printf("nusfd start\n");
	while(1)
	{
		fd_set rfds;
		FD_ZERO(&rfds);
		int ma=0;
		for(int i=0;i<3;i++)
		{
			if(nusfd[i]==-1)
			{
				FD_SET(usfd[i],&rfds);
				ma=max(ma,usfd[i]);
			}
		}
		if(ma==0)break;
		ma++;
		int sret=select(ma,&rfds,NULL,NULL,NULL);
		if(sret==0||sret==-1)
		continue;
		else
		{
			for(int i=0;i<3;i++)
			{
				if(nusfd[i]==-1 && FD_ISSET(usfd[i],&rfds))
				{
					nusfd[i]=accept(usfd[i], (struct sockaddr *)&ucli_addr, &ucli_len);
					cout<<"accept usfd"<<i<<endl;
				}
			}
		}
	}
	printf("nusfd complete\n");	
	char temp[100];
	strcpy(temp,"");
	int fd;
	
	system("pgrep p1 > abc.txt");
	fd=open("abc.txt",O_RDONLY);
	read(fd,temp,100);
	pidarr[0]=atoi(temp);
	close(fd);
	strcpy(temp,"");
	
	system("pgrep p2 > abc.txt");
	fd=open("abc.txt",O_RDONLY);
	read(fd,temp,100);
	pidarr[1]=atoi(temp);
	close(fd);
	strcpy(temp,"");
	
	system("pgrep p3 > abc.txt");
	fd=open("abc.txt",O_RDONLY);
	read(fd,temp,100);
	pidarr[2]=atoi(temp);
	close(fd);
	
	for(int i=0;i<3;i++)
	cout<<pidarr[i]<<endl;
	printf("train start\n");
	while(1)
	{	
		fd_set rfds;
		FD_ZERO(&rfds);
		FD_SET(sfd,&rfds);
		int ma=sfd+1;
		int nsfd;
		int sret=select(ma,&rfds,NULL,NULL,NULL);
		if(sret==0||sret==-1)
		continue;
		else
		{
			for(int i=0;i<3;i++)
			{
				if(p[i]==0)
				{
					nsfd = accept(sfd , (struct sockaddr *)&cli_addr , &cli_len);
					perror("nsfd ");
					p[i]=1;	
					send_fd(nusfd[i],nsfd);		
				}
			}
		}
	}
	
	return 0;
}
