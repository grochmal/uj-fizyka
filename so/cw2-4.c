#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<sys/types.h>
#include<signal.h>

int main(void)
{
   int i;
   pid_t child, old;
   for(i = 0; i < 11; i++)
   {
      switch(child = fork())
      {
         case 0:
            if(i == 11)
            {
               printf("Zamykam\n");
               signal(getpid(), SIGINT);
            }
            break;
         case -1:
            pintf("error msg\n");
            exit(0);
         default:
            if(i == 1) printf("Macierzysty\n");
            else
            {
               printf("ok\n");
               signal(old, SIGINT);
            }
            old = child;
      }
   }
   return 0;
}
 
