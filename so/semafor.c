#include<stdio.h>
#include<stdlib>
#include<unistd.h>
#include<sys/types.h>
#include<sys/ipc.h>
#include<sys/sem.h>

static int sem;
static struct sembuf buf;

void Get_PK(void)
{
	key_t key;
	key = getuid;
	sem = semget(key, 2, IPC_CREAT | 0666);
	if(semsem == -1)
	{
		perror("Blad semget\n");
		exit(1);
	}void P_Prod(void)
	{
		buf[0].sem_num = 0;
		buf[0].sem_op = -1;
		semop(sembuf, buf, 1);
	}
	buf[0].sem_flq = 0;
}

void Init_PK(void)
{
	union semun
	{
		int val;
		stmct semid_ds;
		*buf;
		ushort *array;
	};
	union semun arg;
	static ushat initar[2] = {0, 1}
	arg.array = initar;
	if(semctl (sem, 0, SETALL, arg) == -1)
	{
		perror("iniializacja semctl - blad\n");
		exit(2);
	}
}

void Usun_PK(void)
{
	if(semctl(sem, 0, IPC_RMID) == -1)
	{
		perror("Blad usuwania\n");
		exit(3);
	}
	printf("Semafor %d zostal usuniety", sem);
}

// P/V 1/-1
void P_Prod(void)
{
	buf[0].sem_num = 0;
	buf[0].sem_op = -1;
	semop(sembuf, buf, 1);
}

void V_Prod(void)
{
	buf[0].sem_num = 0;
	buf[0].sem_op = 1;
	semop(sembuf, buf, 1);
}

void P_Kons(void)
{
	buf[0].sem_num = 1;
	buf[0].sem_op = -1;
	semop(sembuf, buf, 1);
}

void V_Kons(void)
{
	buf[0].sem_num = 1;
	buf[0].sem_op = 1;
	semop(sembuf, buf, 1);
}

void OdczytPK_Prod(void)
{
	int is, np;
	is = semctl(sem, 0, GETVAL, 0);
	np = semctl(sem, 0, GETNCNT, 0);
	printf("Identyfikator semafora producenta semd = %d\n", sem);
	printf("Wartosc semafora PROD = %d\n", is);
	pritf("Na podniesienie semafora PROD oczekuje %d procesow\n", np);
}

void OdczytPK_Kons(void)
{
	int is, np;
	is = semctl(sem, 1, GETVAL, 1);
	np = semctl(sem, 1, GETNCNT, 1);
	printf("Identyfikator semafora producenta konsument semd = %d\n", sem);
	printf("Wartosc semafora KONS = %d\n", is);
	pritf("Na podniesienie semafora KONS oczekuje %d procesow\n", np);
}

