#include "header.h"
union semun
{
	int val;
	struct semid_ds *buf;    /* Buffer for IPC_STAT, IPC_SET */
        unsigned short  *array;  /* Array for GETALL, SETALL */
        struct seminfo  *__buf;
};
struct shmp
{
	int x;
};
struct sembuf p={0,-1};
struct sembuf q={0,1};
int main()
{
	int shmid=shmget(123,sizeof(struct shmp),IPC_CREAT|0666);
	struct shmp *shm=shmat(shmid,NULL,0);
	int semid=semget(123,2,IPC_CREAT|0666);
	union semun u;
	u.val=1;
	semctl(semid,0,SETVAL,u);
	u.val=0;
	semctl(semid,1,SETVAL,u);
	int c=fork();
	if(c==0)
	{//p1
		shm=shmat(shmid,NULL,0);
		shm->x=5;
		q.sem_num=1;
		semop(semid,&q,1);
		p.sem_num=0;
		semop(semid,&p,1);
		semop(semid,&p,1);//wait
		printf("the data is %d\n",shm->x);
	}
	else
	{//p2
		shm=shmat(shmid,NULL,0);
		p.sem_num=1;
		semop(semid,&p,1);//wait
		//compute
		shm->x+=5;
		q.sem_num=0;
		semop(semid,&q,1);
	}
	return 0;
}
