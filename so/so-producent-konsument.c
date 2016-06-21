#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<sys/types.h>
#include<signal.h>
#include<sys/wait.h>
#include<sys/stat.h>

#define SUROWIEC "prod.in"
#define MAGAZYN "kons.out"
#define PRODUKCJA 2
#define KONSUMPCJA 1

int main(void)
{
	int desbuf, nread, towar, fdesc[2];
	FILE *fsur, *fmag;

	printf("Start\n");
	if(pipe(fdesc) == -1)
	{
		perror("Blad potoku\n");
		exit (1);
	}

	printf("Utworzono potok o deskryptorach %d, %d\n", fdesc[0], fdesc[1]);
	switch(fork())
	{
		case -1:
			perror("Blad fork\n");
			exit (2);
		case 0:   // KONSUMENT
			if(close(fdesc[1]) == -1)
			{
				perror("Blad zamykania\n");
				exit(3);
			}
			desbuf = fdesc[0];
			fmag = fopen(MAGAZYN, "a");
			if(fmag == NULL)
			{
				perror("Blad otwarcia\n");
				exit(4);
			}

			do
			{
				printf("Proba pobrania danych z potoku\n");
				nread = read(desbuf, &towar, sizeof(towar));

				if(nread == -1)
				{
					perror("Blad pobierania\n");
					exit(5);
				}
				else if(nread == 0)
				{
					break;
				}

				printf("Pobrano z pootku dane: %d\n", towar);
				sleep(KONSUMPCJA);
				/* Robimy cos z tym produktem */
				towar = towar + 17;

				printf("Teraz w towarze jest %d\n", towar);
				fprintf(fmag, "%d\n", towar);

				printf("Skonsumowalem %d\n", towar);
			}while(1);

			fclose(fmag);
			close(desbuf);

			break;
		default:   //PRODUCENT
			if(close(fdesc[0]) == -1)
			{
				perror("Blad zamykania\n");
				exit(6);
			}

			desbuf = fdesc[1];
			fsur = fopen(SUROWIEC, "r");

			if(fsur == NULL)
			{
				perror("Blad otwarcia\n");
				exit(7);
			}

			while(fscanf(fsur, "%d\n", &towar) != EOF)
			{
				printf("Pobralem %d towaru\n", towar);
				sleep(PRODUKCJA);
				printf("Wyprodukowalem\n");

				if(write(desbuf, &towar, sizeof(towar)) == -1)
				{
					perror("Blad pisania w potoku\n");
					exit(8);
				}
			}

			close(desbuf);
			fclose(fsur);
			wait(NULL);
			printf("Koniec\n");

			break;
	}
	return 0;
}

