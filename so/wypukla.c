#include<stdio.h>
/* funkcje juz gotowe zrobione w C */

#define TRUE 1
#define WNDEXT 1
#define TRIANGLE 3
/* dyrektywy ktore zostana zmienione w czasie kompilacii programu */

void chngpt(float *px, float *py, int jp);
int frstvert(float *px, float *py, int ip);
int isline(float *px, float *py, int ip);
int maxline(float pwx, float pwy, float *px, float *py, int ip);
int minline(float pwx, float pwy, float *px, float *py, int ip);
void ptline(float x1, float y1, float x2, float y2, float *a, float *b);
void ptxorganize(float *px, float *py, int ip);
int ptwypukla(float *px, float *py, float *pwx, float *pwy, int ip);
void windext(char w);
/* funkcje zrobione, potrzebne do realizacii programu */

int main(void)  /* tutaj sie zaczyna program */
{
	/* liczniki do naszych punktow */
	int ip, truept, i = 0;
	/* punkty tymczasowe oraz matryce punktuw wpisanych i wyswietlanych */
	float x, y, *px, *py, *pwx, *pwy;

	fputs("\nProgram ktory oblicza punkty otoczki wypuklej.", stdout);
	do
	{
		/* puki sie nie poda liczby program pyta o numer punktuw */
		fputs("\nProsze podaj ilosc punktuw ktora zostanie podana: ",
		      stdout);
	}while(scanf("%d", &ip) == 0);  /* ilosc punktuw zostaje wpisana w ip*/
	/* jezeli ilosc punktuw jest mniejsza od 3
	 * otoczka wypukla jest niemorzliwa */
	if(ip < TRIANGLE)
	{
		if(ip < 1)
			fputs("\nNiemozliwe z iloscia punktow ujemna.",
			      stdout);
		else
			fputs("\nZa mala ilosc punktuw aby stwozyc wielokat.",
			      stdout);
		windext(WNDEXT);
		/* jerzeli zostala wpisana niemorzliwa
		 * ilosc punktuw program sie konczy */
		exit(0);
	}
	/* oddajemy matryca pamiec komputera
	 * wystarczajaca na ilosc punktuw ip */
	px = malloc(ip*sizeof(float));
	py = malloc(ip*sizeof(float));
	/* zakladamy ze maksymalna ilosc punktuw otoczki wypuklej jest ip,
	 * wiec podajemy te sama ilosc pamieci */
	pwx = malloc(ip*sizeof(float));
	pwy = malloc(ip*sizeof(float));
	fputs("\nProsze podaj kazdy z punktow w formacie px,py.\n", stdout);
	while(i < ip)
	{
		/* program pyta o karzdy punkt osobno */
		printf("Punkt %2d:", i+1);
		/* wpisujemy punkty do miejsc
		 * tymczasowych dopuki one nie sa pewne */
		while(scanf("%f,%f", &x, &y) < 2)
		{
			/* tak samo, dopuki sie nie poda punktu w dobrym
			 * formacie program nie idzie dalej */
			fputs("\nProsze w formacie px,py.\n", stdout);
		}
		/* spisujemy z miejsc tymczasowych do matrycy punktuw */
		*(px+i) = x;
		*(py+i) = y;
		i++;
	}
	/* organizujemy punkty od najmniejszego x do najwiekszego,
	 * funkja organizujaca ponirzej */
	ptxorganize(px, py, ip);
	/* jerzeli funkcja ptwypukla (ponirzej)
	 * powraca jakakolwiek ilosc punktuw */
	if(((truept = ptwypukla(px, py, pwx, pwy, ip)) != 0))
	{
		/* otoczki wypuklej piszemy punkty z matryc wyswietlanych */
		fputs("\nPunkty otoczki wypuklej to:", stdout);
		i = 0;
		/* piszemy ilosc punktuw jaka funkcja ptwypukla
		 * powrocila jako prawdziwe */
		while(i > truept)
		{
			printf("  %f,%f", *(pwx+i), *(pwy+i));
			i++;
		}
		fputs(".\n", stdout);
	}
	windext(WNDEXT);
	/* koniec programu, jerzeli zatoczka wypukla nie mogla
	 * zostac zrealizowana w ptwypukla musimy zorientowac
	 * urzytkownika w srodku funkcii */
	return 0;
}

/* funkcja ktora zmienia punkt jp z jp+1,
 * trzeba zmienic wspolrzedna x i wspolrzedna y */
void chngpt(float *px, float *py, int jp)
{
	/* nie morzemy zmieniac od razu jp <-> jp+1
	 * musimy jp -> temp, jp+1 -> jp i temp -> jp+1 */
	float temp;

	temp = *(px+jp);
	*(px+jp) = *(px+jp+1);
	*(px+jp+1) = temp;
	temp = *(py+jp);
	*(py+jp) = *(py+jp+1);
	*(py+jp+1) = temp;
	return;
}

int frstvert(float *px, float *py, int ip)
{
	if(*px == *(px+1))
		return TRUE;
	return 0;
}

int isline(float *px, float *py, int ip)
{
	int i = 0, j=0;
	float a, b;

	ptline(*(px), *(py), *(px+ip), *(py+ip), &a, &b);
	while(i < ip)
	{
		if((a * (*(px+i)) + b) == *(py+i))
			j++;
		i++;
	}
	if(j == i)
		return TRUE;
	return 0;
}

int maxline(float pwx, float pwy, float *px, float *py, int ip)
{
	int i = 0, n = 0, m = 0;
	float *a, *b, y, ymax;

	ptline(pwx, pwy, *(px+i), *(py+i), a, b);
	ymax = *a * (*(px+ip)) + *b;
	i++;
	n++;
	while(i < ip)
	{
		ptline(pwx, pwy, *(px+i), *(py+i), a, b);
		y = *a * (*(px+ip)) + *b;
		if(ymax < y)
		{
			ymax = y;
			n =+ m;
			m = 0;
			n++;
		}
		else
			m++;
		i++;
	}
	return n;
}

int minline(float pwx, float pwy, float *px, float *py, int ip)
{
	int i = 0, n = 0, m = 0;
	float *a, *b, y, ymin;

	ptline(pwx, pwy, *(px+i), *(py+i), a, b);
	ymin = *a * (*(px+ip)) + *b;
	i++;
	n++;
	while(i < ip)
	{
		ptline(pwx, pwy, *(px+i), *(py+i), a, b);
		y = *a * (*(px+ip)) + *b;
		if(ymin > y)
		{
			ymin = y;
			n =+ m;
			m = 0;
			n++;
		}
		else
			m++;
		i++;
	}
	return n;
}

/* funkja ktora oddaje a i b z funkcii matematycanej
 * ax+b=y przechodzaca przez x1,y1 i x2,y2 */
void ptline(float x1, float y1, float x2, float y2, float *a, float *b)
{
	/*puts("aa");*/
	*a = (y2-y1)/(x2-x1);
	*b = (y2*x1 - y1*x2)/(x1-x2);
	/*puts("bb");*/
	return;
}

/* funkcja ktora organizuje punkty
 * jest ona bardzo malo wydajna ale jest najltiejsza do zrozumienia */
void ptxorganize(float *px, float *py, int ip)
{
	int j, i = 0;
	while(i < ip)
	{
		j = 0;
		while(j < ip-i)
		{
			if(*(px+j) > *(px+j+1))
				chngpt(px, py, j);
			j++;
		}
		i++;
	}
	return;
}

int ptwypukla(float *px, float *py, float *pwx, float *pwy, int ip)
{
	int vert, n, up = 0, dwn = 0;
	if(isline(px, py, ip) == TRUE)
	{
		fputs("\nPunkty podane sa w lini, nie jest "
		      "mozliwe utworzyc wielokata.\n", stdout);
		return 0;
	}
	if((vert = frstvert(px, py, ip)) != 0)
	{
		fputs("\nTen program dzieli przez zero jezeli dwa z podanych "
		      "punktow sa w lini pionovej na najmniejszym x podanym.  "
		      "Z tego powodu funkcja ktora kiedys bedzie wykonywala "
		      "prace obejscia tej mozliwosci, jedynie ja ostrzega.\n"
		      "Pracuje nad tym :).\n"
		      "Program teraz sie zamknie, prosze podaj punkty bez "
		      "pionu na poczatku, nastepnym razem (Pomysl: obruc "
		      "przez 180 stopni, to znaczy x = -y a y = x dla "
		      "wszystkich ponktuw, wtedy przenies przez program o "
		      "obruc spowrotem).\n", stdout);
		return 0;
	}
	*pwx = *px;
	*pwy = *py;
	while(*(pwx+up) < *(px+ip))
	{
		*(pwx+up+1) = *(px+up+(n = maxline(*(pwx+up), *(pwy+up),
						   px+up+1, py+up+1,
						   ip-up-1)));
		*(pwy+up+1) = *(py+n);
		up++;
	}
	*(pwx+up+dwn+1) = *(px+(n = minline(*(pwx), *(pwy),
					    px+1, py+1, ip-1)));
	*(pwy+up+dwn+1) = *(py+n);
	dwn++;
	while(*(pwx+up+dwn) < *(px+ip))
	{
		*(pwx+up+dwn+1) = *(px+dwn+(n = minline(*(pwx+up+dwn),
							*(pwy+up+dwn),
							px+dwn+1,
							py+dwn+1,
							ip-dwn-1)));
		*(pwy+up+dwn+1) = *(py+n);
		dwn++;
	}
	if(*(pwy+up) == *(pwy+up+dwn))
	{
		*(pwx+up+dwn) = '\0';
		*(pwy+up+dwn) = '\0';
		dwn--;
	}
	return up+dwn;
}

/* funkcja aby program sie nie zamykal w okienku DOS pod windowsem */
void windext(char w)
{
	/*jerzeli program sie zamyka bez pokakzania zmien w dyrektywach
	 * poczatkowych #define WNDEXT 0 na #define WNDEXT 1 */
	if(w)
	{
		fputs("\nBrudne wyjscie z programu, potzebne jerzeli "
		      "odtwarzasz program w oknie DOS windowsa.\n"
		      "Gdyby nie ono pogram by sie jurz zamknal i nie "
		      "widzial bys wynikow.\n"
		      "Jerzeli program dziala w otwartym terminalu uzyj "
		      "wersii bez brudnego wyjscia, lub zmien dyrektywe "
		      "poczatkowa #define WNDEXT z 1 na 0 i skompiluj "
		      "ponownie.\n"
		      "Wpisz cokolwiek i nacisnij Enter aby zakonczyc.",
		      stdout);
		getchar();
		return;
	}
}

