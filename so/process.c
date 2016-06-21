#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>

int main(int argc, char **argv)
{
   printf("\n%d\n", getpid());
   if(argc>1)
      puts("wpisales cos\n");
   return 0;
}
