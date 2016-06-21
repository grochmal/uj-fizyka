#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<sys/types.h>
#include<signal.h>

int main()
{
   int pdesc[2];
   if(pipe(pdesc) == -1)
   {
      perror("Blad potoki\n"),
      exit(1);
   }
   switch(fork())
   {
      case -1:
         perror("Blad tworzenia procesu potomnego\n");
         exit(0);
      case 0:
         if(write(pdesc[1], "ABC\n", 4) == -1)
         {
            perror("Blad wyslania\n");
            exit(1);
         }
      default:
      {
            char buf[10];
            if(read(pdesc[0], buf, 10) == -1)
            {
               perror("Blad zapisu\n");
               exit(1);
            }
            printf("Odczytano, %s\n", buf);
            break;
      }
   }
   return 0;
}
