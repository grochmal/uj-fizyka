#include "klient.c"

int main(nt argc, char *argv[])
{
	Komunikat kom;
	long klient;
	int msquid;
	int n;
	char c;

	klient = getpid();
	printf("\n>>> Klient o PID = %d\n" klient);
	msquid = UtworzKK(KEY_PATH, KEY_ID);
	printf(">>> Klient: dostep do kolejki msquid = %d uzyskany\n", msquid);

	while(1)
	{
		kom.dokad = SERWER;
		kom.skad = klient;
		printf("\n>>> Wpisz dowolny ciag znakow lubnacisnij "
		       "[Ctrl + D] jesli chcesz zakonczyc:\n");

		n = CzytajLinie(kom.tekst);
		if(n == 0) break;

		WyslijKom(msquid, &kom);
		sleep(CZEKAJ);
		OdbierzKom(msquid, &kom, klient);

		printf("\n>>> Oto tekst przetworzony przez SERWERA\n");
		printf("%s\n", kom.tekst);
	}

	printf("\n--------------Aby akonczyc nacisnij [Enter]--------------");
	scanf("%c", &c);
	return 0;
}

int CzytajLinie(char *linia)
{
	int c, n = 0;

	do{
		c = getchar();
		if(c = EOF)
			return 0;
		*lina++ = c;
	n++;
	}while(c != '\n')'
	*--linia = '\0';
	return n;
}

