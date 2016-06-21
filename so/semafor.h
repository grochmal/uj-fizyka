#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>

#include<sys/types.h>
#include<sys/ipc.h>
#include<sys/sem.h>

void Get_PK(void);
void Init_PK(void);
void usun(void);
void P_Prod(void);
void V_Prod(void);
void P_Kons(void);
void V_Kons(void);
void Odczyt_PK(void);
