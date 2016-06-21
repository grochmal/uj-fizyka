#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>

int main(void)
{
   int i;
   for(i = 0; i < 5; i++)
   {
      wait();
      sleep(10000);
   }
   return 0;
}
