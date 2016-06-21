/*fdesec
mkfifo
read
write
pipe


to co jest tu bedzie podobny do tego program zaliczeniiowy. kontynuacja problemy producent konsument. SUROWIEC-prod.in->PROCES1->potok->PROCES2->kons.out*/


#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<sys/types.h>
#include<sys/stat.h>
#include<sys/wait.h>

#define SUROWIEC "prod.in"
#define MAGAZYN "kons.out"

/*zakladamy ze jakas jednostke czasu zajmuje konsumpcja i produkcja to tez definiujemy*/

#define PRODUKCJA 2
#define KONSUMPCJA 1

int main()
{
	int fdesc[2];
	FILE *fsur;
	FILE *fmag;
	int desbuf;
	int towar;
	int nread;
	printf("START:D\n");
	if(pipe(fdesc)==-1)
	{
		perror("Blad potoku\n");
		exit(1);
	}
	printf("Utworzono potok o deskryptorach %d, %d\n", fdesc[0], fdesc[1]);
	switch(fork())
	{
		case -1:
			perror("Blad forka\n");
			exit(2);
		case 0: //KONSUMENT
			if(close(fdesc[1])==-1)/*zamykamy zapisywanie w buforze przez PROCES 2*/
			{
				perror("Blad zamykania\n");
				exit(3);
			}
			desbuf=fdesc[0];
			fmag=fopen(MAGAZYN, "w");
			if(fmag==NULL)
			{
				perror("blad otwarcia\n");
				exit(4);
			}
			do/*zaczynamy wczytytwac dane z potoku*/
			{
				printf("Proba pobrania danych z potoku\n");
				nread=read(desbuf,&towar,sizeof(towar));
				if(nread==-1)
				{
					printf("blad pobierania\n");
					exit(5);
				}
				else if(nread==0)
				{
					break;
				}
				printf("Pobrano z potoku dane: %d\n", towar);
				sleep(KONSUMPCJA);
				fprintf(fmag, "%d\n", towar);
				printf("skonusmowano %d\n", towar);
			}
			while(1);/*konczy sie gdy bufor jest pusty*/
			fclose(fmag);
			close(desbuf);
		break;
		default: //PRODUCENT
			if(close(fdesc[0]))
			{
				perror("Blad zamykania\n");
				exit(6);
			}
			desbuf=fdesc[1];
			fsur=fopen(SUROWIEC, "r");
			if(fsur==NULL)
			{
				perror("blad otwarcia\n");
				exit(7);
			}
			/*teraz zrobimy zwyklego while'a bo mozemy latwo sprawdzic warunek*/
			while(fscanf(fsur,"%d\n",&towar)!=EOF)
			{
				printf("Pobralem %d\n",towar);
				sleep(PRODUKCJA);
				printf("Wyprodukowalem %d\n",towar);
				if(write(desbuf,&towar,sizeof(towar))==-1)
				{
					perror("Nie udalo sie zapisac w potoku.\n");
					exit(8);
				}
			}
	}
}

