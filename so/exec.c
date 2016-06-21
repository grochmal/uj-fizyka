#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>

main()
{
   printf("\nPoczatek\n");
   execlp("ls", "ls", "-a", NULL);   //NULL to koniec polecenia exec()
   printf("Koniec\n");
   return 0;
}
