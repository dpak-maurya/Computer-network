#include "header.h"
int main(int argc,char *argv[])
{
	//0 nsfd1
	//1 nsfd2
	int f0=atoi(argv[1]);
	cout<<f0<<endl;
	int f1=atoi(argv[2]);
	cout<<f1<<endl;
	char buff[100];
	strcpy(buff,"\0");
	while(1)
	{
	//phase1	
		//read from c1
		read(f0,buff,sizeof(buff));
		//send to c2
		write(f1,buff,strlen(buff)+1);
		
		//read from c2
		read(f1,buff,sizeof(buff));
		//send to c1
		write(f0,buff,strlen(buff)+1);
		
		//read from c1
		read(f0,buff,sizeof(buff));
		//send to c2
		write(f1,buff,strlen(buff)+1);
		//if(buff[0]!='1')
		//continue;
	//phase2
		//read from c2	
		read(f1,buff,sizeof(buff));
		//send to c1
		write(f0,buff,strlen(buff)+1);
		cout<<"from f1"<<buff<<endl;
		//read from c1
		read(f0,buff,sizeof(buff));
		cout<<"from f0"<<buff<<endl;
		//send to c2
		write(f1,buff,strlen(buff)+1);

		//read from c2
		read(f1,buff,sizeof(buff));
		//send to c1
		write(f0,buff,strlen(buff)+1);
		//if(buff[0]=='1')
		{break;}
	}
	return 0;
}
