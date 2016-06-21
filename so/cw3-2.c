#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<sys/types.h>
#include<signal.h>

int main()
{
   pid_t child; 
   switch(child = fork())
   {
      case -1;
         perror("Blad\n");
         exit (1);
      case 0:
         FILE cons, store;
         if(fopen(store, r) == -1)
         {
           perror("Blad odczytu magazynu\n");
         }
         if(fopen(cons, r) == -1)
         {
           perror("Blad odczytu pliku\n");
         }
         char buf;
         while(true)
         {
            buf = getc(pen