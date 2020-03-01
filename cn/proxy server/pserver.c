#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<sys/socket.h>
#include <arpa/inet.h>
#include <netinet/ip.h>
#include<fcntl.h>
#include <unistd.h>
#include<pthread.h>
#include<poll.h>
int ss[5][100];
int curr[5];
int max(int a,int b)
{
	if(a>b)	return a;
	return b;
}
void  *fun(void * arg)
{
	int *t=(int *)arg;
	printf("s server number %d\n",*t);
	
	int sfd=socket(AF_INET,SOCK_STREAM,0);
	if(sfd<0)
		perror("sfd\n");
		
	struct sockaddr_in address;
	address.sin_family=AF_INET;
	address.sin_port=htons(8083);
	address.sin_addr.s_addr=inet_addr("127.0.0.1");
	if(connect(sfd,(struct sockaddr *)&address ,sizeof(address))<0)
		perror("connect\n");
	printf("started %d \n",*t);
	
	fd_set rfds;
	FD_ZERO(&rfds);
	while(1)
	{
		int maxfd=-1;
		printf("curr %d\n",curr[*t]);
		for(int i=0;i<curr[*t];i++)
		{	
			FD_SET(ss[*t][i],&rfds);
			maxfd=max(maxfd,ss[*t][i]);
		}
		maxfd++;
		struct timeval tv;
		tv.tv_sec=3;
		int ret=select(maxfd,&rfds,NULL,NULL,&tv);
		if(ret==-1|| ret==0)	continue;
		else
		{
			printf("SElected here\n");
			for(int i=0;i<curr[*t];i++)
			{	
				if(FD_ISSET(ss[*t][i],&rfds))
				{
					char buffer[1024];buffer[0]='\0';
					int n=read(ss[*t][i],buffer,1024);
					buffer[n]='\0';
					printf("message is %s\n",buffer);
					write(sfd,buffer,n+1);
					buffer[0]='\0';
					n=read(sfd,buffer,1024);
					write(ss[*t][i],buffer,n+1);
				}
			}
		}
	}
}
int main()
{
	for(int i=0;i<5;i++)

	curr[i]=0;
	int sfd=socket(AF_INET,SOCK_STREAM,0);
	if(sfd<0)	perror("sfd");
	struct sockaddr_in address;
	address.sin_family=AF_INET;
	address.sin_port=htons(8081);
	address.sin_addr.s_addr=INADDR_ANY;
	int opt=1;
	    if (setsockopt(sfd, SOL_SOCKET, SO_REUSEADDR | SO_REUSEPORT, &opt, sizeof(opt))) 
	    { 
		perror("setsockopt");
	    }
	int y=bind(sfd,(struct sockaddr *)&address,sizeof(address));
	if(y<0)		perror("bind error l83");
	y=listen(sfd,5);
	if(y<0)		perror("listen");
	
	pthread_t pt[5];
	int x=1;
	for(int i=0;i<1;i++){
		pthread_create(&pt[i],NULL,&fun,&x);
		printf("I value : %d\n",i);
		}
	fd_set rfds;
	FD_ZERO(&rfds);
	printf("final started\n");
	//new client
	while(1)
	{	
		//FD_SET(sfd,&rfds);
		int maxfd=sfd+1;
		struct timeval t;
		t.tv_sec=3;
		//int ret=select(maxfd,&rfds,NULL,NULL,&t);
		//if(ret==-1 || ret==0) printf("Timedout\n");
			//continue;
		//else
		{
			//if(FD_ISSET(sfd,&rfds))
			{
				printf("client added\n");
				int addresslen=sizeof(address);
				int nsfd=accept(sfd,(struct sockaddr*)&address,(socklen_t *)&addresslen);
				if(nsfd<0)	perror("nsfd");
				else
				{
					write(nsfd,"which service\n",14);
					char buffer[1024]="";
					//buffer[0]='\0';
					read(nsfd,buffer,1024);
					int sno=(int)(buffer[0]-'0');
					printf("opted service %d\n",sno);
					ss[sno][curr[sno]++]=nsfd;
					write(ss[sno][curr[sno]-1],"opted serviced\n",15);
				}
			}		
		}
	}	
}
