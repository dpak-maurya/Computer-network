#include "header.h"
int main()
{
	int sfd=socket(AF_INET,SOCK_STREAM,0);
	perror("socket");
	struct sockaddr_in address;
	setAddress(address,8082);
	
	connect(sfd,(struct sockaddr*)&address,sizeof(address));
	perror("connect");
	
	char buff2[100];
	strcpy(buff2,"\0");
	while(1)
	{
		//read from c1
		cout<<"msg rcv"<<endl;
		read(sfd,buff2,sizeof(buff2));
		//execute
		for(int i=0;i<strlen(buff2);i++)
		{
			if(buff2[i]>='a' && buff2[i]<='z')
			buff2[i]=buff2[i]+'A'-'a';
		}
		//send to c1
		write(sfd,buff2,strlen(buff2)+1);
		cout<<"msg snd"<<endl;
		
		//read yes from c1
		read(sfd,buff2,sizeof(buff2));
		cout<<"msg rcv"<<endl;
		
		if(buff2[0]=='1')
		{
			//success
			cout<<"success"<<endl;
			//send to c1
			char buff[]="hello";
			write(sfd,buff,sizeof(buff));
			cout<<"msg snd"<<buff<<endl;
		
			//read from c1
			read(sfd,buff,sizeof(buff));
			cout<<"msg rcv"<<buff<<endl;
		
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
			if(flag==1)//success
			{
				strcpy(buff,"1\0");
				write(sfd,buff,sizeof(buff));
				cout<<"msg snd"<<endl;
				break;
			}
			else
			{
				//repeat
			}
		}
	}
	cout<<"complete"<<endl;
	return 0;	
}
