#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<sys/types.h>

int main(void)
{
   int i, j;
   pid_t child;
   printf("\nMaster Pid = %d\n", getpid());
   for(i = 1; i < 4; i++)
   {
      for(j = i; j > 0; j--)
      {
         printf("   ");
      }
      switch(child = fork())
      {
         case 0:
            printf("|-Child Pid = %d\n", getpid());
            break;
         case -1:
            printf("Error msg, exiting\n");
            exit(0);
         default:
            printf("|-Parent Pid = %d\n", getpid());
            break;
      }
   }
   return 0;
}
