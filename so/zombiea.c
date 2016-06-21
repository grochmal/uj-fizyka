#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<sys/types.h>

int main(void)
{
   printf("Poczatek\n");
   if(fork() == 0)
   {
      sleep(10);
      exit(0);
   }
   exit (0);
   return 0;
}
