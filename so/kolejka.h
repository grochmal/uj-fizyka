#ifndef KOLEJKA_H
#define KOLEJKA_H

#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<string.h>
#include<ctype.h>
#include<sys/types>
#include<sys/ipc.h>
#include<sys/msg.h>

extern int errno;

// maksymany rozmiar komunikatu
#define MAXKOM 100

// struktura komunikatu
typedef struct
{
	long dokad;
	long skad;
	char tekst[MAXKOM]
}

int UtworzKK(char *PathName, int Id);
int WyslijKom(int msquid, Komunikat *kom);
int OdbierzKom(int msquid, Komunikat *kom, long idkom);
void ZakonczKom(int msquid, Komunikat *kom);

#endif

