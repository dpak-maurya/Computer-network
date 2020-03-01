#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<sys/socket.h>
#include <arpa/inet.h>
#include <netinet/ip.h>
#include<fcntl.h>
#include <unistd.h>
#include<poll.h>
#include <sys/ipc.h>
#include <sys/shm.h>
const int max=10;
struct shm
{
	int cnt;
	struct pollfd pofd[max];
};
int main()
{
	char buffer[1024];
	buffer[0]='\0';
	int sfd=socket(AF_INET,SOCK_STREAM,0);
	if(sfd<0)
		perror("sfd");
	struct sockaddr_in address;
	address.sin_family=AF_INET;
	
	
	    int opt=1;
	    if (setsockopt(sfd, SOL_SOCKET, SO_REUSEADDR | SO_REUSEPORT, &opt, sizeof(opt))) 
	    { 
		perror("setsockopt");
	    }
	
	
	address.sin_port=htons(8081);
	address.sin_addr.s_addr=INADDR_ANY;
	if(bind(sfd,(struct sockaddr *)&address ,sizeof(address))<0)
		perror("bind");
	if(listen(sfd,3)<0)
		perror("listen");
	int nsfd;
	int addresslen=sizeof(address);
	
	int shmid=shmget(123,sizeof(struct shm),0666);
	struct shm * s=(struct shm *)shmat(shmid,NULL,0);
	s->pofd[0].fd=0;s->pofd[0].events=0;s->pofd[0].events|=POLLIN;s->pofd[0].revents=0;
	for(int i=1;i<max;i++)
	{s->pofd[i].events=0;s->pofd[i].revents=0;}
	int n;int timeout=5000;
	printf("started\n");
	s->cnt=1;
	while(1)
	{
		int c=fork();
		if(c==0)
		{
			s=(struct shm *)shmat(shmid,NULL,0);
			while(1)
			{
				if((nsfd=accept(sfd,(struct sockaddr*)&address,(socklen_t *)&addresslen))<0)
					perror("nsfd");	
				else
				{
					s->pofd[s->cnt].fd=nsfd;
					s->pofd[s->cnt].events|=POLLIN;
					s->cnt++;
					write(1,"add client\n",11);
				}
			}
			return 0;
		}
		s=(struct shm *)shmat(shmid,NULL,0);
		int pret=poll(s->pofd,s->cnt,timeout);
		if(pret==0)
			write(1,"timeout\n",8);
		else
		{
			for(int i=0;i<s->cnt;i++)
			{
				if( (i==0) && (s->pofd[i].revents & POLLIN) )
				{
					n=read(0,buffer,1024);
					write(1,"sending\n",8);
					for(int k=1;k<s->cnt;k++)
						send(s->pofd[k].fd,buffer,n,0);
				}
				else if(s->pofd[i].revents & POLLIN)
				{
					n=read(s->pofd[i].fd,buffer,1024);
					write(1,buffer,n);//writing on terminal
					for(int k=1;k<s->cnt;k++)
						if(k!=i)send(s->pofd[k].fd,buffer,n,0);
				}
			}
		}
	}
	return 0;
}
