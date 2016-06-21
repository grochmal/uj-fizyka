#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>

int main(void)
{
   pid_t pid;
   
   if((pid = fork()) == 0)
   {
      // proces potny
      while(1)
      {
         printf("abc\n");
         sleep(9);
      }
   }
   if(pid == -1)
   {
      perror("nie dziala :(\n");
      exit(1);
   }
   else
   {
      // proces macierzysty
      while(1)
      {
         printf("def\n");
         sleep(8);
      }
   }
}
