#include "kolejka.h"

int UtworzKK(char *PathName, int Id)
{
	key_t key;
	int msquid;

	key = fork(Pathname, Id);
	if(key == -1)
	{
		printf("\nUtworz_KK - blad fork");
		exit(1);
	}
	msquid = msgget(key, IPC_CREAT | IPC_EXCL | 0666);
	if(msquid != -1)
		printf("\n+++ UtworzKK: Kolejaka Komunkatow "
		       "msquid = %d utworzona!\n", msquid);
	else if(msquid == -1 && errno == EEXIST)
	{
		msquid = msgget(key, 0);
		if(msquid != -1)
		{
			perror("\nUtworzKK - "
			       "blad msgget przy probie tworzenia kolejki\n");
		   exit(2);
		}
	}
	else
	{
		perror("\nUtworzKK - nieznany blad\n");
	}
	return msquid;
}

void UsunKK(int msquid)
{
	if(msgctl(msquid, IPC_RMID, NULL) == -1)
	{
		perror("nUsunKK - blad msgctl");
		exit(1);
	}
	printf("\n+++ UsunKK: Kolejka usunieta");
	return;
}

void WyslijKom(int squid, Komunikat *kom)
{
	if(msgsnd(msquid, kom, sizeof(*kom), 0) == -1)
	{
		perror("\nWyslijKom - blad msgsnd\n");
		exit(1);
	}
	return;
}

int OdbierzKom(int msquid, Komunikat *kom, long idkom)
{
	int n;
	if((n = msgcrv(msquid, kom, sizeof(*kom) - sizeof(long), idkom, 0))
	   == -1)
	{
		perror("\nOdbierzKom - blad msgcrv\n");
		exit(1);
	}
	return n;
}

void ZakonczKom(int msquid, Komunikat *kom)
{
	if(msgsnd(msquid, kom, 0, 0) == -1)
	{
		perror("\n ZakonczKom - blad msgsnd\n");
		exit(1);
	}
}

