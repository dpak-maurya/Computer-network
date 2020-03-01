#include<stdlib.h>
#include<stdio.h>
#include<string.h>
#include<unistd.h>
#include <signal.h>
#include<sys/types.h>
#include<netdb.h>
#include<arpa/inet.h>
#include<sys/socket.h>
#include<errno.h>
#include<fcntl.h>
#include<sys/stat.h>
#include<sys/time.h>
#include <sys/select.h>

struct stm
{
	int nsfd;
	int here;
	int pid;
};
int max(int a,int b)
{
  if(a>b) return a;
  else return b;
}
struct stm st[100];
int count=0;
void handler(int sig, siginfo_t *info, void *ucontext)
{
	pid_t pid=info->si_pid;//p4 pid
	printf("signal received from p4\n");
	printf("value of count %d\n",count);
	for(int i=0;i<count;i++)
	{
		if(st[i].here==1)
		{
			int dd=st[i].nsfd;
			for(int i=0;i<2;i++)
			{
				write(dd,"hello from echo\n",17);
				//sleep(2);
			}
			break;
		}
	}
}
int main()
{
	//return from echon
	mkfifo("echonpipe",0666);
	int efd=open("echonpipe",O_RDONLY|O_NONBLOCK);
	//p4
	struct sigaction act;
	act.sa_flags=SA_SIGINFO;
	act.sa_sigaction=&handler;
	int p=sigaction(SIGUSR1,&act,NULL);
	if(p==0){printf("success\n");}
	
	/*p4*/
	/*char statement[72]="";
	strcat(statement,"gnome-terminal -- /bin/bash -c './p4 ");
	char temp[10]="";
	sprintf(temp,"%d",(int)getpid());
	strcat(statement,temp);
	strcat(statement,";'");
	system(statement);
	write(1,"done4\n",6);*/
	printf("%d\n",(int)getpid());
	
	struct sockaddr_in clientaddr,serveraddr;
	
	int sfd;
	sfd=socket(AF_INET,SOCK_STREAM,0);
	
	if(sfd<0)		perror("sfd");

	int opt=1;
	if (setsockopt(sfd, SOL_SOCKET, SO_REUSEADDR | SO_REUSEPORT, &opt, sizeof(opt))) 
	{ 
		perror("setsockopt");
	}
	socklen_t addr_len=sizeof(serveraddr);

	serveraddr.sin_family=AF_INET;
	serveraddr.sin_port=htons(8081);
	serveraddr.sin_addr.s_addr=INADDR_ANY;
	
	if(bind(sfd,(struct sockaddr *)&serveraddr ,sizeof(serveraddr))<0)		perror("bind");

	int y=listen(sfd,5);
	if(y<0)
	{
		printf("error in listening\n");
		exit(1);
	}
	addr_len=sizeof(struct sockaddr_in);

	fd_set rfds;

	FD_ZERO(&rfds);
	int fd_arr[100];
	int curr=0;
	fd_arr[curr++]=sfd;
	fd_arr[curr++]=efd;
	
	int nsfd;
	int maxfd=max(efd,sfd);maxfd++;
	write(1,"started\n",8);
	while(1)
	{ 
		//after select all FD_SET should be set
		for(int i=0;i<curr;i++)
			FD_SET(fd_arr[i],&rfds);
		printf("all fd set\n");
		int n=select(maxfd,&rfds,NULL,NULL,NULL);//infinite wait 
		
		if(n==-1)
			{continue;}
		else
		{	
			//new client
			printf("no of clients %d\n",count);
			if(FD_ISSET(sfd,&rfds))
			{
				if((nsfd=accept(sfd,(struct sockaddr*)&clientaddr,&addr_len))<0)
				{
					perror("nsfd()");
				}
				else
				{
					st[count].nsfd=nsfd;
					st[count].here=1;
					maxfd=max(maxfd-1,nsfd)+1;
					count++;
					write(1,"add client\n",11);
					fd_arr[curr++]=nsfd;
				}
			}
			//client messages
			for(int i=0;i<count;i++)
			{
				if(st[i].here ==1 && FD_ISSET(st[i].nsfd,&rfds))
				{
					//read
					char buffer[1024];
					buffer[0]='\0';
					int n=read(st[i].nsfd,buffer,1024); 
					buffer[n]='\0';
					printf("message received %s\n",buffer);
					//write
					for(int j=0;j<count;j++)
					{
						if(st[j].here==1 && i!=j)
						{
							write(st[j].nsfd,buffer,n+1);
						}
					}
				}
			}
			//echonpipe
			if(FD_ISSET(efd,&rfds))
			{
				char buffer[1024];
				buffer[0]='\0';
				int n=read(efd,buffer,1024);
				if(n==0)continue;
				buffer[n]='\0';
				int onsfd=atoi(buffer);
				for(int i=0;i<count;i++)
				{
					if(st[i].nsfd==onsfd)
					{
						printf("found\n");
						st[i].here=1;
						break;
					}
				}
			}
		}
	}
	return 0;
}
