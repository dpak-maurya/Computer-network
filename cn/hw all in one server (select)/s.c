#include"header.h"
struct dictionary
{
	char s[10];
	int fd;
	int here;
};
struct dictionary d[100];
int i;
void hdfn(int signo)
{
	printf("number of clients now %d\n",i);
	for(int j=0;j<i;j++)
	{
		if(d[j].here==1)
		{
			printf("Here\n");
			d[j].here=0;
			close(d[j].fd);
			char statement[72]="";
			strcpy(statement,"");
			strcat(statement,"gnome-terminal -- /bin/bash -c './echon ");
			strcat(statement,d[j].s);
			strcat(statement,";'");
			system(statement);
			break;
		}
	}
}
void handler(int sig, siginfo_t *info, void *ucontext)
{
	
}
int max(int a,int b)
{
	if(a>b)return a;
	return b;
}
int main()
{
	char buffer[1024];
	buffer[0]='\0';
	i=0;
	int f0=dup(0);int f1=dup(1);
	int pfd[2];
	pipe(pfd);
	int c=fork();
	if(c==0)
	{//child
		/*p1*/
		close(pfd[0]);
		/*while(1)
		{
			char Bff[]="Input from process1 :\n";
			write(pfd[1],Bff,strlen(Bff));
			for(int j=0;j<0x2fffffff;j++)
			;
		}*/
		exit(0);
	}
	//parent
	/*p2*///run p2 first
	write(1,"done1",5);
	mkfifo("fifo",0666);
	int ffd=open("fifo",O_RDONLY|O_NONBLOCK);
	write(1,"done2",5);
	/*p3*/
	int fd=fileno(popen("./p3","r"));
	write(1,"done3",5);
	/*p4*/
	struct sigaction act;
	act.sa_flags=SA_SIGINFO;
	act.sa_sigaction=&handler;
	sigaction(SIGUSR1,&act,NULL);
	char statement[72]="";
	strcat(statement,"gnome-terminal -- /bin/bash -c './p4 ");
	char temp[10]="";
	sprintf(temp,"%d",(int)getpid());
	strcat(statement,temp);
	strcat(statement,";'");
	system(statement);
	write(1,"done4",5);
	/*p5*/
	int pout=fileno(popen("./p5.out","w"));
	write(pout,"done5",5);
	//sfd
	mkfifo("famfifo",0666);
	int sfd=open("famfifo",O_RDONLY|O_NONBLOCK);//run 1 client first
	if(sfd==-1)
	printf("error\n");
	write(f1,"start\n",6);
	//gets input from 0,p1,p2,p3
	//input and output
	char buff;
	char str[10];str[0]='\0';
	int size;int which=0;
	
	fd_set rfds;
	FD_ZERO(&rfds);
	FD_SET(f0,&rfds);//0
	FD_SET(pfd[0],&rfds);//p1
	FD_SET(ffd,&rfds);//p2
	FD_SET(fd,&rfds);//p3
	FD_SET(sfd,&rfds);//new client
	int arr[]={f0,pfd[0],ffd,fd,sfd};
	int arrsize=5;a
	int maxfd=max(max(max(max(f0,pfd[0]),ffd),fd),sfd)+1;
	while(1)
	{
		//client add and removal
		int n=select(maxfd,&rfds,NULL,NULL,5000);
		if(n<0) perror("select()");
		else if(n==0)
			printf("timeout\n");
		else
		{
			for(int k=0;k<arrsize;i++)
			{
				if(FD_ISSET(aarr[k],&rfds) && arr[k]!=sfd)
				{
					int op=read(arr[k],buffer,1024);
					for(int j=0;j<i;j++)
					{
						if(d[j].here==1)
						{
							write(d[j].fd,buffer,op);
							printf("wrote on %s\n",d[j].s);
						}
					}
				}
				else if(FD_ISSET(arr[k],&rfds) && arr[k]==sfd)
				{//new client
					
				}
			}
		}
		while(1)
		{	
			size=read(sfd,&buff,1);
			if(size<0) {perror("File open error\n");break;}
			if(size>0) printf("Client addition\n");
			if(size==0)
				break;
			else if(buff!='\n')
				{if(buff=='#'){which=0;}
				else if(buff=='X'){which=1;}
				else{strncat(str,&buff,1);}}
			else if(buff=='\n' && strcmp(str,"")!=0)
			{
				printf(" %d,%s ",which,str);
				if(which==0)
				{
					d[i].s[0]='\0';
					strcpy(d[i].s,str);
					mkfifo(d[i].s,0666);
					d[i].fd=open(d[i].s,O_WRONLY);
					if(d[i].fd<0) perror("Wait error\n");
					str[0]='\0';
					i++;
					printf("client completed %d\n",i);
					d[i-1].here=1;
				}
				else if(which=1)
				{
					for(int j=0;j<i;j++)
					{
						if(strcmp(d[j].s,str)==0)
						{
							d[j].fd=open(d[j].s,O_WRONLY);
							d[j].here=1;
							break;
						}						
					}
					str[0]='\0';
				}
			}
		}
		//poll
		int ret=poll(pofd,4,timeout);
		write(f1,"first ",6);
		char to=(char)(i+48);
		write(f1,&to,1);
		if(ret==0)
		write(1,"timeout\n",strlen("timeout")+1);
		else if(ret>0)
		{
			char buff[100];buff[0]='\0';
			for(int k=0;k<4;k++)
			{
				if(pofd[k].revents&POLLIN)
				{
					printf("-%d-",k);
					int siz=read(pofd[k].fd,buff,sizeof(buff));
					for(int j=0;j<i;j++)
					{
						if(d[j].here==1)
						{
							write(d[j].fd,buff,siz);
							printf("wrote on %s\n",d[j].s);
						}
					}
					write(1,buff,siz);
					buff[0]='i';
					write(1,buff,1);
					pofd[k].revents=0;
				}
			}
		}	
	}	
	return 0;
}
