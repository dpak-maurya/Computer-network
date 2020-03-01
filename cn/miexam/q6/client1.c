#include "header.h"
int main()
{
	int sfd=socket(AF_INET,SOCK_STREAM,0);
	perror("socket");
	struct sockaddr_in address;
	setAddress(address,8081);
	
	connect(sfd,(struct sockaddr*)&address,sizeof(address));
	perror("connect");
	
	while(1)
	{	
		//send to c2
		char buff[]="hello";
		write(sfd,buff,sizeof(buff));
		printf("message sent1\n");
		strcpy(buff,"\0");
		//read from c2
		read(sfd,buff,sizeof(buff));
		printf("message rcv1\n");
		//compare
		int flag=1;
		for(int i=0;i<strlen(buff);i++)
		{
			if(buff[i]>='A' && buff[i]<='Z')
			{}
			else
			{flag=0;}
		}
		cout<<buff<<flag<<endl;
		if(flag==1)
		{
			//success
			char buff[100];
			printf("success\n");		
			strcpy(buff,"1\0");
			write(sfd,buff,strlen(buff)+1);
			//read from c2
			printf("message rcv2\n");
			read(sfd,buff,sizeof(buff));
			cout<<strlen(buff)<<buff<<endl;
			//execute
			for(int i=0;i<strlen(buff);i++)
			{
				if(buff[i]>='a' && buff[i]<='z')
				buff[i]=buff[i]+'A'-'a';
			}
			//send to c2
			printf("message sent2\n");
			cout<<strlen(buff)<<buff<<endl;
			write(sfd,buff,strlen(buff)+1);
			//read from c2
			strcpy(buff,"\0");
			printf("message rcv2\n");
			read(sfd,buff,sizeof(buff));
			//if(buff[0]=='1')
			break;
		}
		else
		{
			//failed
			strcpy(buff,"0\0");
			write(sfd,buff,sizeof(buff));
		}
	}
	printf("message success\n");
	return 0;
}
