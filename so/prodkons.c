#include"semafor.h"

#define PRODUCENT "producent.x"
#define KONSUMENT "konsument.c"
#define BUFOR "bufor"
#define SUROWIEC "prod.inp"
#define MAGAZYN "kons.out"

int main(void)
{
   int pid;
   char *argv[6];
   argv[2] = BUFOR;
   argv[3] = NULL;
   
   Get_PK();
   Init_PK();
   Odczyt_PK();
   
   if((pid = fork()) == -1)
   {
      perror("prodkons - blad fork'a");
      exit(1);
   }
   
   if(pid == 0)
   {
      argv[0] = KONSUMENT;
      argv[1] = MAGAZYN;
      execv(argv[0], argv);
      perror("prodkons - blad execv");
      printf("Proces: %s\n", argv[0]);
      exit(3);
   }
   else
   {
      argv[0] = PRODUCENT;
      argv[1] = SUROWIEC;
      execv(argv[0], argv);
      perror("prodkons - blad execv");
      printf("Proces: %s\n", argv[0]);
      exit(3);
   }
   return 0;
}