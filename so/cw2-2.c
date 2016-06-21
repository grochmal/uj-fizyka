#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<sys/types.h>
#include<signal.h>

int main(void)
{
   int i;
   while(1)
   {
      signal(SIGINT, SIG_IGN);
      for(i = 0; i < 6; i++)
         pause();
   }
   return 0;
}
