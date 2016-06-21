#include"semafor.h"

#define KONSUMPCJA 2

int main(int argc, char *argv[])
{
   FILE *fmag, *fbuf;
   char *magazyn, *bufor;
   int towar;
   
   if(argc != 3)
   {
      printf("Bledna liczba argumentuw programu KONSUMENT!\n);
      exit(1);
   }
   
   magazyn = argv[1];
   bufor = argv[2];
   
   fmag = fopen(magazyn, "w");
   fclose(fmag);
   fmag = fopen(magazyn, "a");
   
   Get_PK();
   
   do{
      printf("KONSUMENT: probuje pobrac towar z bufora\n");
      
      P_Kons();
      
      if((fbuf = fopen(bufor, "r")) == NULL)
      {
         printf("KONSUMENT: bufor zmakniety!\n");
         break;
      }
      
      fscanf(fbuf, "%d", &towar);
      fclose(fbuf);
      sleep(KONSUMPCJA);
      fprintf(fmag, "%4d\n", towar);
      printf("KONSUMENT: skonsumowalem towar %d\n", towar);
      V_Prod();
   }while(1);
   fclose(fmag);
   Usun_PK();
   printf("KONSUMENT: Komsumpcja zakonczona - semafory usuniente!\n");
   return 0;
}