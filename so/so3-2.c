#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<string.h>

int IsMe(void);
int IsYou(void);

int main(void)
{
   char buf[12], *me = "Me", *you = "You";
   int mypipe[2];
   
   if(mkfifo(mypipe, ???) == -1)
   {
      puts("Haaaaaaaaaaaaaaaaaaaa!");
   }
   puts("ok");
   
   do{
      
      puts("Me or You");
      scanf("%s", buf);
      
      if(!(strcmp(buf, me)))
         return 0;
      
      if(!(strcmp(buf, you)))
         return 0;
      
   }while(1);
}

