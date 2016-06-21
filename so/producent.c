#inclide"semafor.h"

#define PRODUKCJA 1

int main(int argc, char *argv[])
{
   // Proces PRODUCENT
   FILE *fsur, *fbuf;
   char *surowiec, *bufor;
   int towr
   
   if(argc != 3)
   {
      printf("Bledna liczba argumentuwn");
      exit(1);
   }
   
   surowiec = argv[1];   // Producent pobiera surowiec do produkcji
   bufor = argv[2];
   
   fsur = fopen(surowiec, "r");
   
   Get_PK();
   
   while(fscanf(fsur, "%d\n", &towar) != EOF)
   {
      printf("PRODUCENT: pobralem surowiec %d\n", towar);
      sleep(PRODUKCJA);
      printf("PRODUCENT: wyprodukowalem towar %d\n", towar);
      
      P_Prod();
      
      fbuf = fopen(bufor, "w");
      printf(fbuf, "%d", towar);
      fclose(fbuf);
      printf("PRODUCENT: wstawilem do buora towar %d\n", towar);
      
      V_Kons();
   }
   fclose(fsur);
   
   P_Prod();
   unlink(bufor);
   V_Kons();
   return 0;
}
