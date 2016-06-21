#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<sys/types.h>

int main(void)
{
   int i, pid_t, child;
   for(i = 0; i <= 3; i++)
   {
      switch((child = fork()))
      {
         case 0:
            printf("pid %d, parentpid %d\n", getpid(), getppid());
            break;
         case -1:
            perror("fail");
            exit (1);
         default:
            printf("child pid: %d\n", child);
            break;
       }
   }
   return 0;
}
