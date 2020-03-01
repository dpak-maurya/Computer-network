#include "header.h"
int main()
{
	int sfd1=socket(AF_INET,SOCK_STREAM,0);
	perror("sfd1");
	int opt=1;
	if(setsockopt(sfd1,SOL_SOCKET,SO_REUSEADDR|SO_REUSEPORT,&opt,sizeof(opt)))
	perror("setsockopt");
	struct sockaddr_in address;
	setAddress(address,8081);
	bind(sfd1,(struct sockaddr *)& address,sizeof(address));
	perror("bind");
	listen(sfd1,5);
	perror("listen");
	
	int sfd2=socket(AF_INET,SOCK_STREAM,0);
	perror("sfd2");
	if(setsockopt(sfd2,SOL_SOCKET,SO_REUSEADDR|SO_REUSEPORT,&opt,sizeof(opt)))
	perror("setsockopt");
	setAddress(address,8082);
	bind(sfd2,(struct sockaddr *)& address,sizeof(address));
	perror("bind");
	listen(sfd2,5);
	perror("listen");
	
	cout<<"r starting"<<endl;
	int len=sizeof(address);
	while(1)
	{
		int nsfd1=accept(sfd1,(struct sockaddr*)&address,(socklen_t*)&len);
		perror("nsfd1");
		int nsfd2=accept(sfd2,(struct sockaddr*)&address,(socklen_t*)&len);
		perror("nsfd2");
		cout<<"idk"<<endl;
		int c=fork();
		if(c==0)
		{
			cout<<"start scene"<<endl;
			cout<<nsfd1<<endl;
			cout<<nsfd2<<endl;
			char b1[1024],b2[1024];
			sprintf(b1,"%d",nsfd1);
			sprintf(b2,"%d",nsfd2);
			char * argv[]={"./scene",b1,b2,NULL};
			execv(argv[0],argv);	
		}
		else
		{
			close(nsfd1);
			close(nsfd2);
		}
	}
}
