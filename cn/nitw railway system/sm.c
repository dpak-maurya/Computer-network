#include<stdio.h>
#include<stdlib.h>
#include<sys/types.h>
#include<netdb.h>
#include<arpa/inet.h>
#include<sys/socket.h>
#include<string.h>
#include<unistd.h>
#include<errno.h>
#include<signal.h>
#include<sys/poll.h>

int max(int a,int b)
{
  if(a>b) return a;
  else return b;
}

int main()
{
	int fl[3];
	for(int i=0;i<3;i++) fl[i]=0;
	struct sockaddr_in clientaddr,serveraddr1,serveraddr2,serveraddr3;
	int sfd1,sfd2,sfd3;

	sfd1=socket(AF_INET,SOCK_STREAM,0);
	sfd2=socket(AF_INET,SOCK_STREAM,0);
	sfd3=socket(AF_INET,SOCK_STREAM,0);
	if(sfd1<0 || sfd2<0 || sfd3<0)
	{
		printf("error creating socket\n");
		exit(1);
	}

	    int opt=1;
	    if (setsockopt(sfd1, SOL_SOCKET, SO_REUSEADDR | SO_REUSEPORT, &opt, sizeof(opt))) 
	    { 
		perror("setsockopt");
	    }
	    if (setsockopt(sfd2, SOL_SOCKET, SO_REUSEADDR | SO_REUSEPORT, &opt, sizeof(opt))) 
	    { 
		perror("setsockopt");
	    }
	    if (setsockopt(sfd3, SOL_SOCKET, SO_REUSEADDR | SO_REUSEPORT, &opt, sizeof(opt))) 
	    { 
		perror("setsockopt");
	    }
	serveraddr1.sin_family=AF_INET;
	serveraddr1.sin_port=htons(8081);
	serveraddr1.sin_addr.s_addr=INADDR_ANY;
	socklen_t addr_len1=sizeof(serveraddr1);

	serveraddr2.sin_family=AF_INET;
	serveraddr2.sin_port=htons(8082);
	serveraddr2.sin_addr.s_addr=INADDR_ANY;
	socklen_t addr_len2=sizeof(serveraddr2);
	
	serveraddr3.sin_family=AF_INET;
	serveraddr3.sin_port=htons(8083);
	serveraddr3.sin_addr.s_addr=INADDR_ANY;
	socklen_t addr_len3=sizeof(serveraddr3);

	int y=bind(sfd1,(struct sockaddr*)&serveraddr1,addr_len1);
	int z=bind(sfd2,(struct sockaddr*)&serveraddr2,addr_len2);
	int x=bind(sfd3,(struct sockaddr*)&serveraddr3,addr_len3);
	
	if(y<0 || z<0 || x<0)
	{
		printf("error in binding address\n");
		exit(1);
	}

	int y1=listen(sfd1,5);
	int z1=listen(sfd2,5);
	int x1=listen(sfd3,5); 
	if(y1<0 || z1<0 || x1<0)
	{
		printf("error in listening\n");
		exit(1);
	}
	socklen_t addr_len=sizeof(struct sockaddr_in);

	fd_set rfds;
	fd_ser wfds;
	FD_ZERO(&rfds);
	FD_ZERO(&wfds);
	int maxfd=max(max(sfd1,sfd2),sfd3)+1;

	FD_SET(sfd1,&rfds);
	FD_SET(sfd2,&rfds);
	FD_SET(sfd3,&rfds);
	int nsfd1,nsfd2,nsfd3;

	while(1)
	{ 
		int n=select(maxfd,&rfds,NULL,NULL,5000);
		if(n==-1)
			perror("select()");
		if(FD_ISSET(sfd1,&rfds))
		{	
			if((nsfd1=accept(sfd1,(struct sockaddr*)&clientaddr,&addr_len))<0)
				perror("nsfd1");
			else
			{
				  printf("Client connected to s1\n");
				  int c=fork();
				  if(c==0)
				  {
				      close(sfd1);
				      char *arg[]={"./p",NULL};
				      dup2(nsfd1,0);
				      execv(arg[0],arg);
				  }
				  else
				  {
				   close(nsfd1);
				  }
			}

	        }
		if(FD_ISSET(sfd2,&rfds))
		{
			if((nsfd2=accept(sfd2,(struct sockaddr*)&clientaddr,&addr_len))<0)
			{
				perror("nsfd2");
			}
			else
			{
			 	  printf("Client connected to s2\n");
				  int c=fork();
				  if(c==0)
				  {
				      close(sfd2);
				      char *arg[]={"./p",NULL};
				      dup2(nsfd2,1);
				      dup2(nsfd2,0); 
				      execv(arg[0],arg);
				  }
				  else
				  {
				   close(nsfd2);
				  }
			}
		}
		if(FD_ISSET(sfd3,&rfds))
		{
			if((nsfd3=accept(sfd3,(struct sockaddr*)&clientaddr,&addr_len))<0)
			{
				perror("nsfd3");
			}
			else
			{
			 	  printf("Client connected to p\n");
				  int c=fork();
				  if(c==0)
				  {
				      close(sfd3);
				      char *arg[]={"./s2",NULL};
				      dup2(nsfd3,1);
				      dup2(nsfd3,0); 
				      execv(arg[0],arg);
				  }
				  else
				  {
				   close(nsfd3);
				  }
			}
		}
	}


}
