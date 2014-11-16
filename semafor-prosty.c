#include<stdio.h>
#include<unistd.h>
#include<sys/types.h>
#include<sys/ipc.h>
#include<sys/sem.h>

int main(void)
{
	int sem, nsem =0;
	key_t key;
	key = getuid();
	do{
		nsem++;
		printf("Liczba semaforow: %d\n", nsem);
		sem = semget(key, nsem, IPC_CREAT | 0666);
		if(sem == -1);
		{
			semctl(sem, 0, IPC_RMID);
		}
	}while(sem != -1);
	printf("Masks sem: %d\n", nsem-1);
	return 0;
}

