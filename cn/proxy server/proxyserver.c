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
int tot=1;
int s_avl[1];
int ssfd[1];
void * fun(void *arg)
{
	int *i =(int *)arg;
	int n;
	char buffer[1024];
	buffer[0]='\0';
	while(1)
	{
		struct pollfd pfd[2];
		pfd[0].fd=s_avl[*i];
		pfd[0].events=0;pfd[0].events|=POLLIN;
		pfd[0].revents=0;
		pfd[1].fd=ssfd[*i];
		pfd[1].events=0;pfd[1].events|=POLLIN;
		pfd[1].revents=0;
		if(s_avl[*i]!=0)
		{	
			int ret=poll(pfd,2,1000);
			if(ret==-1)
				printf("timeout\n");
			else
			{	
				//client fd
				if(pfd[0].revents & POLLIN)
				{
					n=read(s_avl[*i],buffer,1024);
					printf("message from client\n");
					write(ssfd[*i],buffer,n+1);
				}
				buffer[0]='\0';
				//server fd
				if(pfd[0].revents & POLLIN)
				{
					n=read(ssfd[*i],buffer,1024);
					printf("message from server\n");
					write(s_avl[*i],buffer,n+1);
				}
				buffer[0]='\0';
			}
		}
		else
		printf("no client to serve\n");
	}
}
int main()
{
	tot=1;
	char buffer[1024];
	buffer[0]='\0';
	for(int i=0;i<tot;i++) s_avl[i]=0;
	int sfd=socket(AF_INET,SOCK_STREAM,0);
	if(sfd<0)		perror("sfd");
	struct sockaddr_in address;
	address.sin_family=AF_INET;
	
	    int opt=1;
	    if (setsockopt(sfd, SOL_SOCKET, SO_REUSEADDR | SO_REUSEPORT, &opt, sizeof(opt))) 
	    { 
		perror("setsockopt");
	    }
	
	address.sin_port=htons(8081);
	address.sin_addr.s_addr=INADDR_ANY;
	if(bind(sfd,(struct sockaddr *)&address ,sizeof(address))<0)		perror("bind");
	if(listen(sfd,3)<0)		perror("listen");
	int nsfd;
	int addresslen=sizeof(address);
	printf("started intial\n");
	//fill ssfd[tot]
	for(int i=0;i<tot;i++)
	{
		int sfd=socket(AF_INET,SOCK_STREAM,0);
		if(sfd<0)		perror("sfd");
		struct sockaddr_in saddress;
		saddress.sin_family=AF_INET;
	
		    int opt=1;
		    if (setsockopt(sfd, SOL_SOCKET, SO_REUSEADDR | SO_REUSEPORT, &opt, sizeof(opt))) 
		    { 
			perror("setsockopt");
		    }
		
		saddress.sin_port=htons(8082);
		saddress.sin_addr.s_addr=INADDR_ANY;
		if(bind(sfd,(struct sockaddr *)&saddress ,sizeof(saddress))<0)		perror("bind");
		if(listen(sfd,3)<0)		perror("listen");
		int saddresslen=sizeof(saddress);
		int nssfd;
		if((nssfd=accept(sfd,(struct sockaddr*)&saddress,(socklen_t *)&saddresslen))<0)
				perror("nssfd");
		else printf("socket connected\n");	
		ssfd[i]=nssfd;
	}
	//pthread
	pthread_t thread[tot];
	for(int i=0;i<tot;i++)
		pthread_create(&thread[i],NULL,&fun,(void *)&i);
	//poll for client
	struct pollfd pfd[1];pfd[0].fd=sfd;pfd[0].events=0;pfd[0].events|=POLLIN;pfd[0].revents=0;
	int timeout=1000;
	printf("started final1\n");
	while(1)
	{
		printf("started finalwhile\n");
		int pret=poll(pfd,1,timeout);
		if(pret==0)
			printf("timeout\n");
		else
		{
			printf("started finalelse\n");
			if(pfd[0].revents & POLLIN)
			{//sfd
				if((nsfd=accept(sfd,(struct sockaddr*)&address,(socklen_t *)&addresslen))<0)
						perror("nsfd");	
				else
				{
					write(1,"add client 1\n",13);
					//check empty service
					for(int i=0;i<5;i++)
					{
						if(s_avl[i]==0)
						{
							s_avl[i]=nsfd;
							printf("service given\n");
							break;				
						}
					}
				}
			}
		}
	}
	return 0;
}
