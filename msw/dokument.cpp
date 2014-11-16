#include <iostream>
#include <string>
#include <cstdlib>
#define P(msg) cout << ":::" << msg << endl

using namespace std;

class Dokument{
	public:
		virtual ~Dokument(){P("usuwam Dokument");}
		virtual void drukuj()=0; // czysto wirtualna
		virtual void czytaj(){}
	};

class Dok: public Dokument{
	protected:
		string tresc;
	public:
		virtual ~Dok(){P("usuwam Doc");}
		virtual void drukuj(){ cout << tresc << endl;}
	};

class DokStd: public Dok{
	public:
		~DokStd(){P("usuwam DokStd");}
		void czytaj(){
			cout<< "Wpisz tresc dokumentu: "<< endl;
			cin >> tresc;
		}
	};

class Dekorator: public Dokument{
	Dokument *ptrDok;
	public:
		Dekorator(Dokument *ptr):ptrDok(ptr){}
		virtual ~Dekorator(){
			P("usuwam Dekorator");
			delete ptrDok;
		}
		void drukuj(){ptrDok->drukuj();}
	};

class Naglowek: public Dekorator{
	void drukujNaglowek();
	public:
		Naglowek(Dokument *ptr):Dekorator(ptr){}
		void drukuj();
		~Naglowek(){
			P("usuwam Naglowek");
		}
	};

void Naglowek::drukuj(){
	drukujNaglowek();
	Dekorator::drukuj();
}

void Naglowek:: drukujNaglowek(){
	cout << "........NAGLOWEK........"<< endl;
}

class Stopka: public Dekorator{
	void drukujStopka();
	public:
		Stopka(Dokument *ptr):Dekorator(ptr){}
		void drukuj();
		~Stopka(){
			P("usuwam Stopka");
		}
	};

void Stopka::drukuj(){
	drukujStopka();
	Dekorator::drukuj();
}

void Stopka:: drukujStopka(){
	cout << "----------STOPKA----------"<< endl;
}

int main (int argc, char *argv[])
{
	Dokument *ptr1=new DokStd;
	ptr1->czytaj();
	ptr1->drukuj();

	Dokument *ptr2= new Naglowek(ptr1);
	ptr2->drukuj();
	//delete ptr2;

	ptr2= new Stopka(ptr1);
	ptr2->drukuj();
	//delete ptr2;

	ptr1=new Stopka(new Stopka(new Naglowek(ptr2)));
	ptr1->drukuj();
	//delete ptr2;
	delete ptr1;
	system("PAUSE");
	return 0;
}

