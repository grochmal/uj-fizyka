#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<sys/types.h>
#include<signal.h>

int main(void)
{
   kill(getpid(), SIGINT);
   while(1)
   {
      puts("ok?");
      sleep(10000);
   }
   return 0;
}
