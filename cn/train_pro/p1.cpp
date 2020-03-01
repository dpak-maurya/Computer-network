#include"header.h"
#define ADDRESS     "mysocket1"
int main()
{
	int pid;
	cout<<"pid of sm"<<endl;
	cin>>pid;
	int usfd;
	struct sockaddr_un userv_addr;
  	int userv_len,ucli_len;

  	usfd = socket(AF_UNIX, SOCK_STREAM, 0);

  	if(usfd==-1)
  	perror("\nsocket  ");

  	bzero(&userv_addr,sizeof(userv_addr));
  	userv_addr.sun_family = AF_UNIX;
   	strcpy(userv_addr.sun_path, ADDRESS);

	userv_len = sizeof(userv_addr);

	if(connect(usfd,(struct sockaddr *)&userv_addr,userv_len)==-1)
	perror("\n connect ");

	else printf("\nconnect succesful");
	int fd;
	while(1)
	{
		fd=recv_fd(usfd);
		if(fd==-1||fd==0)
		continue;
		char buffer[1024];
		memset(buffer,'\0',sizeof(buffer));
		read(fd,buffer,1024);
		
		write(1,buffer,strlen(buffer)+1);
		
		memset(buffer,'\0',sizeof(buffer));
		read(fd,buffer,1024);
		
		kill(pid,SIGUSR1);
	}
	return 0;	
}
