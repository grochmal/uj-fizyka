#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>

main()
{
   printf("\nPoczatek\n");
   fork();
   printf("Koniec\n");
   return 0;
}
