#include <iostream>
#include <cstring>
#include <cstdlib>
#ifdef _MSC_VER
#define _CRT_SECURE_NO_WARNINGS
#endif
using namespace std;

class Incaltaminte;
class Brand;
class Angajat;
class Cumparator;

class Brand
{
	const char* denumire;
	const char* locatie;
	int nr_perechi;

public:
	friend istream& operator >> (istream& in, Brand& f);
	friend ostream& operator << (ostream& out, Brand& f);

	Brand() = default;
	Brand(const char* n, const char* a, int nr)
	{
		denumire = n;
		locatie = a;
		nr_perechi = nr;
	}

	const char* get_denumire() const
	{
		return denumire;
	}

	const char* get_locatie() const
	{
		return locatie;
	}

	int get_nr_perechi() const
	{
		return nr_perechi;
	}

	void set_Brand(const char* nume, const char* adresa, int numar)
	{
		denumire = nume;
		locatie = adresa;
		nr_perechi = numar;
	}
	void afisare_detalii()
	{
		cout << "Denumirea brand-ului: " << denumire<<endl;
		cout << "Locatia coletului: " << locatie << endl;
		cout << "Numarul de perechi comandante: " << nr_perechi << endl;
	}

};



class Incaltaminte
{
	int marime;
	Brand brand;
	int pret;
public:
	Incaltaminte() = default;
	Incaltaminte(int mar, Brand b, int p)
	{
		marime = mar;
		brand.set_Brand(b.get_denumire(), b.get_locatie(), b.get_nr_perechi());
		pret = p;
	}
	int check_marime()
	{
		if (marime >= 40 && marime < 50)
			return 1;
		else return 0;
	}
	int get_pret()
	{
		return pret;
	}
	int get_marime()
	{
		return marime;
	}
	void set_pret(int p)
	{
		pret = p;
	}

	void set_marime(int m)
	{
		marime = m;
	}
	void set_brand(const char* denumire, const char* locatie, int nr_perechi) {
		brand.set_Brand(denumire, locatie, nr_perechi);
	}
	Incaltaminte& operator=(const Incaltaminte& i)
	{
		if (this != &i)
		{
			this->marime = i.marime;
			this->brand = i.brand;
			this->pret = i.pret;
		}
		return *this;
	}
	void afisare()
	{
		cout << "Pretul total al comenzii dumneavoastra este: " << pret * brand.get_nr_perechi();;
	}
};

class Cumparator
{
	char* nume;
	char* prenume;
	char* email;
	char* nr_telefon;
public:
	Cumparator() : nume(nullptr), prenume(nullptr), email(nullptr), nr_telefon(nullptr) {}
	Cumparator(char* n, char* p, char* e, char* nr)
	{
		nume = new char[strlen(n) + 1];
		strcpy_s(nume, strlen(n) + 1, n);
		prenume = new char[strlen(p) + 1];
		strcpy_s(prenume, strlen(p) + 1, p);
		email = new char[strlen(e) + 1];
		strcpy_s(email, strlen(e) + 1, e);
		nr_telefon = new char[strlen(nr) + 1];
		strcpy_s(nr_telefon, strlen(nr) + 1, nr);
	}

	void set_Cumparator(char* n, char* p, char* e, char* nr)
	{
		if(nume!=n) nume = n;
		if(prenume!=p) prenume = p;
		if(email!=e) email = e;
		if(nr_telefon!=nr) nr_telefon = nr;
	}
	friend ostream& operator<<(ostream& os, const Cumparator& client)
	{
		os << "Nume: " << client.nume << "\n";
		os << "Prenume: " << client.prenume << "\n";
		os << "Email: " << client.email << "\n";
		os << "Numar de telefon: " << client.nr_telefon << "\n";
		return os;
	}
};
class Angajat 
{
	char nume[30];
	char prenume[30];
	int cod;
	Cumparator* cumparatori = new Cumparator [10];
	int nrcumparatori;

public:
	Angajat() : nume(), prenume(), cod(0) {}
	Angajat(char n[30], char p[30], int  c)
	{
		strcpy_s(nume, strlen(n)+1, n);
		strcpy_s(prenume,strlen(p)+1, p);
		cod = c;
	}

	int get_cod()
	{
		return cod;
	}
	char* get_nume() {
		return nume;
	}
	char* get_prenume()
	{
		return prenume;
	}
	/*void set_Angajat(char* n, char* p, int c)
	{
		nume = n;
		prenume = p;
		cod = c;
	}*/
	void set_Cumparator(int index,char* n, char* p,char *e, char* nr)
	{
		cumparatori[index].set_Cumparator(n, p, e, nr);
	}
	void set_nrcumparatori(int nrcmp)
	{
		nrcumparatori = nrcmp;
	}
	int salariu()
	{
		return 1000 * nrcumparatori;
	}
	void afisareclienti()
	{
		for (int i = 0; i < nrcumparatori; ++i)
			cout << cumparatori[i]<<" ";
	}
	~Angajat() {
		delete[] cumparatori;
	}
};



int main()
{
	cout << "--- Selecteaza una dintre cele 2 optiuni. ---" << "\n";
	cout << "1.Angajat " << "\n";
	cout << "2.Cumparator " << "\n";
	int optiune;
	cin >> optiune;
	system("CLS");
	if (optiune == 2)
	{
		cout << "Nume si prenume: \n";
		char nume[30];
		char prenume[30];
		cin >> nume>>prenume;
		cout << "Numar de telefon: \n";
		char nr[11];
		cin >> nr;
		cout << "Email-ul personal: \n";
		char mail[30];
		cin >> mail;
		Cumparator cumparator(nume, prenume, mail, nr);
		system("CLS");
		cout << "Alegeti brand-ul: " << "\n";
		cout << "1. Nike - 500 de lei/pereche \n";
		cout << "2. Adidas - 400 de lei/pereche \n";
		cout << "3. Vans - 300 de lei/pereche \n";
		Incaltaminte obiect;
		int nume_firma;
		cin >> nume_firma;
		Brand incaltare;
		if (nume_firma == 1)
		{
			int nr;
			cout << "Cate perechi doriti? \n";
			cin >> nr;
			Brand papuc("Nike", "Romania", nr);
			const char* den = papuc.get_denumire();
			const char* loc = papuc.get_locatie();
			int numar = papuc.get_nr_perechi();
			incaltare.set_Brand(den,loc,numar);
		}

		else if(nume_firma == 2)
		   {
			int nr;
			cout << "Cate perechi doriti? \n";
			cin >> nr;
			Brand papuc("Adidas", "Germania", nr);
			const char* den = papuc.get_denumire();
			const char* loc = papuc.get_locatie();
			int numar = papuc.get_nr_perechi();
			incaltare.set_Brand(den, loc, numar);
		   
		}

		    else if (nume_firma == 3)
	 	      {
			    int nr;
			    cout << "Cate perechi doriti? \n";
			    cin >> nr;
				Brand papuc("Vans", "Elvetia", nr);
				const char* den = papuc.get_denumire();
				const char* loc = papuc.get_locatie();
				int numar = papuc.get_nr_perechi();
				incaltare.set_Brand(den, loc, numar);
		      }
			else {
			cout << "Brand-ul cautat nu este in stoc.";
			return 0;
		}
		int marime;
		cout << "Ce marime doriti? \n";
		cin >> marime;
		obiect.set_marime(marime);
		if (obiect.check_marime() == 1)
		{
			if (incaltare.get_denumire() == "Nike")
			{
				int p;
				p = 500;
				Incaltaminte nike;
				nike.set_pret(p);
				obiect = nike;
			}
			if (incaltare.get_denumire() == "Adidas")
			{
				int p;
				p = 400;
				Incaltaminte adidas;
				adidas.set_pret(p);
				obiect = adidas;
			}
			if (incaltare.get_denumire() == "Vans")
			{
				int p;
				p = 300;
				Incaltaminte vans;
				vans.set_pret(p);
				obiect = vans;
			}
		}
		else
		{
			system("CLS");
			cout << "Marimea cautata nu este in stoc. Stocul disponibil pentru marimi este de la marimea 40 pana la marimea 50.  \n";
			return 0;

		}
		system("CLS");
		cout << cumparator;
		incaltare.afisare_detalii();
		cout << "Pretul total pentru comanda dumneavoastra este: " << obiect.get_pret() * incaltare.get_nr_perechi();


	}
	if (optiune == 1)
	{
		cout << "Nume si prenume: \n";
		char numeangajat[30];
		char  prenumeangajat[30];
		cin >> numeangajat >> prenumeangajat;
		cout << "Cod angajat: ";
		int nrangajat;
		cin >> nrangajat;
		Angajat angajat(numeangajat, prenumeangajat, nrangajat);
		if (angajat.get_cod() == 21)
		{
			system("CLS");
			cout << "Codul introdus este corect. Bine ai venit "<<angajat.get_nume()<<" "<<angajat.get_prenume()<<"!\n";
			int nrcump;
			cout << "Introdu numarul de persoane pe care le-ai asistat: ";
			cin >> nrcump;
			angajat.set_nrcumparatori(nrcump);
			cout << "Te rog introdu datele persoanelor (nume, prenume, email, numar de telefon): ";
			char numecump[30], prenumecump[30], emailcump[30], nrtelefon[30];
			for (int i = 0; i < nrcump; i++)
			{
				cin >> numecump >> prenumecump >> emailcump >> nrtelefon;
				angajat.set_Cumparator(i, numecump, prenumecump, emailcump, nrtelefon);

			}
			system("CLS");
			cout << "Pentru fiecare client pe ziua de azi ai castigat: " << angajat.salariu()<<"\n";
			cout << "Clientii din ziua de azi: \n";
			angajat.afisareclienti();

		}
		else {
			system("CLS");
			cout << "Codul este gresit. Acces interzis!";
			return 0;
		}

	}
	 return 0;

}


/*NU INTELEG DE CE DE LA AFISAREA LA LINIA 350 DA OVERWRITE LA TOT VECTORUL */