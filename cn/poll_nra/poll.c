#include<stdlib.h>
#include<stdio.h>
#include<string.h>
#include<unistd.h>
#include<fcntl.h>
#include<sys/stat.h>
#include<sys/wait.h>
#include<sys/types.h>
#include<signal.h>
#include<poll.h>
int main()
{
  
  int pp[2];
  pipe(pp);
  struct pollfd fds[2];
  fds[0].fd=0;
  fds[1].fd=pp[0];
  fds[0].events=fds[1].events=0;
  fds[0].events|=POLLIN;
  fds[1].events|=POLLIN;
  int timeout=5000;
  int c=fork();
  if(c>0)
  {
     while(1)
     {
         int pret=poll(fds,2,timeout);
         write(0,"first",5);
         if(pret==0)
         {
           printf("timeout\n");
         }
         else if(pret>0)
         {
            if(fds[0].revents&POLLIN)
            {
                char ch[100];
                int ret=read(fds[0].fd,ch,100);
                if(ret!=-1)
                {
                    ch[ret]='\0';
                    printf("user:%s \n",ch);
                }
               
            }
            else if(fds[1].revents&POLLIN)
            {
                char ch[100];
                int ret=read(fds[1].fd,ch,100);
                if(ret!=-1)
                {
                      ch[ret]='\0';
                    printf("pipe:%s \n",ch);
                }
            }
          }  
      }
   }
   else
   {
       while(1)
       {
           close(pp[0]);
           char ch[]="hello world";
           int r=rand()%3;
           if(r==0)
           write(pp[1],ch,strlen(ch)+1);
          sleep(2);

       }
    } 
}
