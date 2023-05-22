#include <iostream>
#include <cstring>
#include <cstdlib>
#include <vector>
#include <algorithm>
#include <stdexcept>
#include <random>
#ifdef _MSC_VER
#define _CRT_SECURE_NO_WARNINGS
#endif
using namespace std;

class Incaltaminte;
class Brand;
class Angajat;
class Cumparator;
class Director;


class Brand
{
	const char* denumire;
	const char* locatie;
	int nr_perechi;

public:
	friend istream& operator >> (istream& in, Brand& f);
	friend ostream& operator << (ostream& out, const Brand& f);

	Brand() = default;
	Brand(const char* n, const char* a, int nr)
		: denumire(n), locatie(a), nr_perechi(nr)
	{
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

	void afisare_detalii() const
	{
		cout << "Denumirea brand-ului: " << denumire << endl;
		cout << "Locatia coletului: " << locatie << endl;
		cout << "Numarul de perechi comandante: " << nr_perechi << endl;
	}
};



class Incaltaminte
{
protected:
	int marime;
	Brand brand;
	int pret;

public:
	Incaltaminte() = default;
	Incaltaminte(int mar, const Brand& b, int p)
		: marime(mar), brand(b), pret(p)
	{
	}

	int check_marime() const
	{
		if (marime >= 40 && marime < 50)
			return 1;
		else
			return 0;
	}

	int get_pret() const
	{
		return pret;
	}

	int get_marime() const
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

	void set_brand(const char* denumire, const char* locatie, int nr_perechi)
	{
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

	void afisare() const
	{
		cout << "Pretul total al comenzii dumneavoastra este: " << pret * brand.get_nr_perechi() << endl;
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

	Cumparator(const char* n, const char* p, const char* e, const char* nr)
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

	~Cumparator()
	{
		delete[] nume;
		delete[] prenume;
		delete[] email;
		delete[] nr_telefon;
	}

	void set_Cumparator(const char* n, const char* p, const char* e, const char* nr)
	{
		if (strcmp(nume, n) != 0)
		{
			delete[] nume;
			nume = new char[strlen(n) + 1];
			strcpy_s(nume, strlen(n) + 1, n);
		}

		if (strcmp(prenume, p) != 0)
		{
			delete[] prenume;
			prenume = new char[strlen(p) + 1];
			strcpy_s(prenume, strlen(p) + 1, p);
		}

		if (strcmp(email, e) != 0)
		{
			delete[] email;
			email = new char[strlen(e) + 1];
			strcpy_s(email, strlen(e) + 1, e);
		}

		if (strcmp(nr_telefon, nr) != 0)
		{
			delete[] nr_telefon;
			nr_telefon = new char[strlen(nr) + 1];
			strcpy_s(nr_telefon, strlen(nr) + 1, nr);
		}
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


class Creare {
public:
	static Incaltaminte createIncaltaminte(int marime, const Brand& brand, int pret) {
		return Incaltaminte(marime, brand, pret);
	}

	static Cumparator createCumparator(const char* nume, const char* prenume, const char* email, const char* nr_telefon) {
		return Cumparator(nume, prenume, email, nr_telefon);
	}
};



class Director {
public:
	virtual void afisareDetalii() = 0;
	virtual double calculeazaSalariu() = 0;
	virtual ~Director() {}
};

class Lucrator {
protected:
	string nume;
	int varsta;

public:
	Lucrator(string n, int v) : nume(n), varsta(v) {}

	virtual void afisareDetalii() {
		cout << "Nume: " << nume << "\n";
		cout << "Varsta: " << varsta << "\n";
	}

	virtual double calculeazaSalariu() = 0;
	virtual int calculeazaOreSuplimentare() = 0;
};

class Vanzator : public Lucrator {
private:
	double comision;
	int oreSuplimentare;

public:
	Vanzator(string n, int v, double c, int os) : Lucrator(n, v), comision(c), oreSuplimentare(os) {}

	void afisareDetalii() override {
		Lucrator::afisareDetalii();
		cout << "Comision: " << comision << "\n";
		cout << "Ore suplimentare: " << oreSuplimentare << "\n";
	}

	double calculeazaSalariu() override {
		return 2000 + comision * 0.1 + oreSuplimentare * 10;
	}

	int calculeazaOreSuplimentare() override {
		return oreSuplimentare;
	}
};

class Casier : public Lucrator {
private:
	double salariuFix;
	int oreSuplimentare;

public:
	Casier(string n, int v, double s, int os) : Lucrator(n, v), salariuFix(s), oreSuplimentare(os) {}

	void afisareDetalii() override {
		Lucrator::afisareDetalii();
		cout << "Salariu fix: " << salariuFix << "\n";
		cout << "Ore suplimentare: " << oreSuplimentare << "\n";
	}

	double calculeazaSalariu() override {
		return salariuFix + oreSuplimentare * 10;
	}

	int calculeazaOreSuplimentare() override {
		return oreSuplimentare;
	}
};

bool comparareSalariu(Lucrator* a, Lucrator* b) {
	return a->calculeazaSalariu() > b->calculeazaSalariu();
}

class Cos_cumparaturi
{
protected:
	int nr_incaltari, nr_produse;
	static int nr_incaltarii, nr_produsee;
public:
	void set_nr_incaltari(int nr)
	{
		nr_incaltari = nr;
	}
	void set_nr_incaltarii(int nr)
	{
		nr_incaltarii = nr;
	}

	int get_nr_incaltari()
	{
		return nr_incaltari;
	}
	void set_nr_produse(int nr)
	{
		nr_produse = nr;
	}
	void set_nr_produsee(int nr)
	{
		nr_produsee = nr;
	}
	int get_nr_produse()
	{
		return nr_produse;
	}
	static int nrincaltari()
	{
		return nr_incaltarii;
	}
	static int nrproduse()
	{
		return nr_produsee;
	}
};


int Cos_cumparaturi::nr_incaltarii = 0;


class Incaltaminte_Cos : virtual public Cos_cumparaturi
{
protected:
	string denumire;
	int marime;
	int pret;
	int pret_total_incaltaminte;
public:
	int get_pret()
	{
		return pret;
	}
	Incaltaminte_Cos() = default;
	Incaltaminte_Cos(string d, int m, int p)
	{
		denumire = d;
		marime = m;
		pret = p;
	}
	void set_pret_total_incaltaminte(int nr)
	{

		pret_total_incaltaminte = nr;
	}
	int get_pret_total_incaltaminte()
	{
		return pret_total_incaltaminte;
	}
	friend ostream& operator<<(ostream& os, const vector<Incaltaminte_Cos>& v) {
		for (const auto& incaltaminte : v) {
			os << "Denumire: " << incaltaminte.denumire << "\n";
			os << "Marime: " << incaltaminte.marime << "\n";
			os << "Pret: " << incaltaminte.pret << "\n";
		}
		return os;
	}
};
int Cos_cumparaturi::nr_produsee = 0;
class Accesorii_incaltaminte : virtual public Cos_cumparaturi
{
protected:
	string nume_produs;
	int pret;
	int pret_total_accesorii;
public:
	Accesorii_incaltaminte() = default;
	int get_pret()
	{
		return pret;
	}
	Accesorii_incaltaminte(string n, int p)
	{
		nume_produs = n;
		pret = p;
	}
	void set_pret_total_accesorii(int n)
	{
		pret_total_accesorii = n;
	}
	int get_pret_total_accesorii()
	{
		return pret_total_accesorii;
	}
	friend ostream& operator<<(ostream& os, const vector<Accesorii_incaltaminte>& v) {
		for (const auto& accesorii : v) {
			os << "Nume produs: " << accesorii.nume_produs << "\n";
			os << "Pret: " << accesorii.pret << "\n";
		}
		return os;
	}
};

class Total_Comanda : virtual public Incaltaminte_Cos, virtual public Accesorii_incaltaminte
{
protected:
	int taxe_incaltaminte = 20;
	int taxe_produse = 10;
	int taxa_livrare = 40;
	int pret_total_incaltaminte;
	int pret_total_accesorii;
	int pret_total;
public:
	int calcul_taxa_incaltaminte()
	{
		if (get_nr_incaltari() != 0)
			return taxe_incaltaminte * get_nr_incaltari();
	}
	int calcul_taxa_produse()
	{
		if (get_nr_produse() != 0)
			return taxe_produse * get_nr_produse();
	}
protected:
	int get_pret_total()
	{
		int pret = 0;
		if (get_nr_incaltari() != 0)
			pret = pret + pret_total_incaltaminte + calcul_taxa_incaltaminte();
		if (get_nr_produse() != 0)
			pret = pret + pret_total_accesorii + calcul_taxa_produse();
		pret_total = pret + taxa_livrare;
		return pret_total;
	}
public:
	void set_pret_total_accesorii(int nr)
	{
		pret_total_accesorii = nr;
	}
	void set_pret_total_incaltaminte(int nr)
	{
		pret_total_incaltaminte = nr;
	}
	void afisare_comanda()
	{
		cout << "Totalul comenzii dumneavoastra este: " << get_pret_total() << "\n";
	}

};


class Angajat {
private:
	string nume;
	string parola;

public:
	Angajat(const string& nume) : nume(nume) {}

	void introducereParola() {
		try {
			cout << "Introduceti parola: ";
			cin >> parola;

			if (parola != "proiect_poo") {
				throw invalid_argument("Parola incorecta!");
			}

			cout << "Parola corecta. Acces permis." << endl;
			afisareCastig(); // Upcasting
		}
		catch (const invalid_argument& ex) {
			cout << "Eroare: " << ex.what() << endl;
			throw runtime_error("Accesul este blocat.");
		}
	}

	virtual void afisareCastig() const {
		cout << "Castig: 0" << endl;
	}
};

class AngajatVanzari : public Angajat {
public:
	AngajatVanzari(const string& nume) : Angajat(nume) {}

	void afisareCastig() const override {
		cout << "Castig in vanzari: 1000" << endl;
	}
};

class AngajatMarketing : public Angajat {
public:
	AngajatMarketing(const string& nume) : Angajat(nume) {}

	void afisareCastig() const override {
		cout << "Castig in marketing: 2000" << endl;
	}
};

template <typename T>
int calculateDeliveryDays() {
	random_device rd;
	mt19937 gen(rd());
	T minDays = 1;
	T maxDays = 10;
	uniform_int_distribution<T> dist(minDays, maxDays);

	return dist(gen);
}


template <typename T>
class Curier {
private:
	string name;
	T deliveryFee;

public:
	Curier(const string& name, const T& deliveryFee) : name(name), deliveryFee(deliveryFee) {}

	string getName() const {
		return name;
	}

	T getDeliveryFee() const {
		return deliveryFee;
	}
};

template <>
class Curier<double> {
private:
	string name;
	double deliveryFee;

public:
	Curier(const string& name, double deliveryFee) : name(name), deliveryFee(deliveryFee) {}

	string getName() const {
		return name;
	}

	double getDeliveryFee() const {
		return deliveryFee;
	}

	string getCategory() const {
		return "Fan Courier";
	}
};


int main()
{
	cout << "--- Selecteaza una dintre cele 3 optiuni. ---" << "\n";
	cout << "1.Director " << "\n";
	cout << "2.Cumparator " << "\n";
	cout << "3.Gestioneaza cosul de cumparaturi." << "\n";
	cout << "4.Angajat " << "\n";
	cout << "5.Curier " << "\n";
	int optiune;
	cin >> optiune;
	system("CLS");
	if (optiune == 2)
	{
		cout << "Nume si prenume: \n";
		char nume[30];
		char prenume[30];
		cin >> nume >> prenume;
		cout << "Numar de telefon: \n";
		char nr[11];
		cin >> nr;
		cout << "Email-ul personal: \n";
		char mail[30];
		cin >> mail;
		Cumparator cumparator=Creare::createCumparator(nume, prenume, mail, nr);
		system("CLS");
		cout << "Alegeti brand-ul: " << "\n";
		cout << "1. Nike - 500 de lei/pereche \n";
		cout << "2. Adidas - 400 de lei/pereche \n";
		cout << "3. Vans - 300 de lei/pereche \n";
		Brand incaltare("", "", 0);
		Incaltaminte obiect=Creare::createIncaltaminte(0,incaltare,0);
		int nume_firma;
		cin >> nume_firma;
		if (nume_firma == 1)
		{
			int nr;
			cout << "Cate perechi doriti? \n";
			cin >> nr;
			Brand papuc("Nike", "Romania", nr);
			const char* den = papuc.get_denumire();
			const char* loc = papuc.get_locatie();
			int numar = papuc.get_nr_perechi();
			incaltare.set_Brand(den, loc, numar);
		}

		else if (nume_firma == 2)
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
	if (optiune == 3)
	{
		Cos_cumparaturi cos;
		vector <Incaltaminte_Cos> v;
		vector <Accesorii_incaltaminte> v2;
		cout << "Doriti incaltaminte?" << "\n";
		cout << "Daca da, apasati tasta 1. " << "\n";
		int numar_comenzi;
		bool ok, ok1, ok2;
		cin >> ok;
		if (ok == 1)
		{
			ok1 = 1;
			cout << "Cate perechi de incaltaminte doriti?" << "\n";
			int ct;
			cin >> ct;
			system("CLS");

			cos.set_nr_incaltari(ct);
			cos.set_nr_incaltarii(ct);
			for (int i = 1; i <= ct; ++i)
			{
				string denumire;
				cout << "Denumire: " << "\n";
				cin >> denumire;
				int marime;
				cout << "Marime: " << "\n";
				cin >> marime;
				int pret;
				cout << "Pret: " << "\n";
				cin >> pret;
				Incaltaminte_Cos aux(denumire, marime, pret);
				v.push_back(aux);
				system("CLS");
			}
		}
		cout << "Doriti accesorii pentru incalataminte? " << "\n";
		cout << "Daca da, apasati tasta 1. " << "\n";
		cin >> ok;
		if (ok == 1)
		{
			ok2 = 1;
			cout << "Cate accesorii pentru incaltaminte doriti? " << "\n";
			int ct;
			cin >> ct;
			system("CLS");
			cos.set_nr_produse(ct);
			cos.set_nr_produsee(ct);
			for (int i = 1; i <= ct; ++i)
			{
				string nume;
				cout << "Nume produs: " << "\n";
				cin >> nume;
				int pret;
				cout << "Pretul produsului: " << "\n";
				cin >> pret;
				Accesorii_incaltaminte aux(nume, pret);
				v2.push_back(aux);
				system("CLS");
			}

		}
		if (ok1 == 1 && ok2 == 0)
		{
			cout << "In cosul de cumparaturi s-au regasit doar incaltaminte.\n";
			cout << "Comanda dumneavostra este urmatoarea: \n";
			cout << v << '\n';
			system("CLS");
		}
		if (ok1 == 0 && ok2 == 1)
		{
			cout << "In cosul de cumparaturi s-au regasit doar accesorii pentru incaltaminte.\n";
			cout << "Comanda dumneavoastra este urmatoarea: \n";
			cout << v2 << "\n";
			system("CLS");
		}
		if (ok1 == 1 && ok2 == 1)
		{
			cout << "Cosul de cumparaturi arata astfel: \n";
			cout << "-----Incaltaminte----- \n";
			cout << v << '\n';
			cout << "-----Accesorii de incaltaminte----- \n";
			cout << v2 << "\n";
		}
		Incaltaminte_Cos incal;
		Accesorii_incaltaminte acces;

		Total_Comanda comanda;
		int p1, p2;
		int pret_t = 0;
		int cate;
		cate = cos.get_nr_incaltari();
		for (int i = 0; i < cate; ++i)
			pret_t = pret_t + v[i].get_pret();
		if (cos.get_nr_incaltari() >= 10)
		{
			cout << "Felicitari, beneficiati de o reducere de 10% deoarece ati cumparat cel putin 10 perechi!\n";
			pret_t = pret_t - pret_t * 10 / 100;
		}
		incal.set_pret_total_incaltaminte(pret_t);
		pret_t = 0;
		for (int i = 0; i < cos.get_nr_produse(); ++i)
			pret_t = pret_t + v2[i].get_pret();
		if (cos.get_nr_produse() >= 5)
		{
			cout << "Felicitari, beneficiati de o reducere de 20% deoarece ati cumparat cel putin 5 accesorii pentru incaltaminte!\n";
			pret_t = pret_t - pret_t * 20 / 100;
		}
		acces.set_pret_total_accesorii(pret_t);
		comanda.set_pret_total_accesorii(acces.get_pret_total_accesorii());
		comanda.set_pret_total_incaltaminte(incal.get_pret_total_incaltaminte());
		comanda.afisare_comanda();
		return 0;
	}
	if (optiune == 1)
	{
		cout << "Pentru a afisa detaliile despre angajtii magazinului apasati tasta 1.\n";
		bool ok;
		cin >> ok;
		if (ok == 1)
		{
			system("CLS");
			vector<Lucrator*> lucratori;

			lucratori.push_back(new Vanzator("Ana", 30, 1000, 10));
			lucratori.push_back(new Vanzator("Maria", 25, 1200, 5));
			lucratori.push_back(new Casier("Ion", 35, 2000, 15));
			lucratori.push_back(new Casier("Mihai", 28, 1800, 8));

			sort(lucratori.begin(), lucratori.end(), comparareSalariu);
			


			cout << "Lucratorul cu cel mai mare salariu:\n";
			lucratori[0]->afisareDetalii();
			system("pause");
			system("cls");
			auto lucratorCuCeleMaiMulteOre = max_element(lucratori.begin(), lucratori.end(),
				[](Lucrator* a, Lucrator* b) {
					return a->calculeazaOreSuplimentare() < b->calculeazaOreSuplimentare();
				});

			cout << "Lucratorul cu cele mai multe ore suplimentare:\n";
			(*lucratorCuCeleMaiMulteOre)->afisareDetalii();
			system("pause");
			system("cls");
			for (const auto& lucrator : lucratori) {
				lucrator->afisareDetalii();
				cout << "-------------------" << endl;
			}
			
		}
	}
	if (optiune == 4)
		try {
		Angajat* angajat = nullptr;
		string nume;

		cout << "Introduceti numele angajatului: ";
		cin >> nume;

		cout << "--- Selectati un departament ---" << endl;
		cout << "1. Vanzari" << endl;
		cout << "2. Marketing" << endl;
		int optiunee;
		cin >> optiunee;
		system("CLS");
		if (optiunee == 1) {
			angajat = new AngajatVanzari(nume);
		}
		else if (optiunee == 2) {
			angajat = new AngajatMarketing(nume);
		}
		else {
			throw invalid_argument("Optiune invalida!");
		}

		angajat->introducereParola();

		delete angajat;
	}
	catch (const exception& ex) {
		cout << "Eroare: " << ex.what() << endl;
		cout << "Programul se inchide." << endl;
		return 0;
	}
	if (optiune == 5)
	{
		cout << "Pentru a afisa datele despre curierul dumnevoastra apasati tasta 1.\n";
			bool okcurier;
		cin >> okcurier;
		if (okcurier == 1)
		{
			system("cls");
			Curier<double> curier2("Marius", 20.5);
			cout << "Nume curier: " << curier2.getName() << endl;
			cout << "Taxa de livrare: " << curier2.getDeliveryFee() << endl;
			cout << "Categorie: " << curier2.getCategory() << endl;
			int deliveryDaysInt = calculateDeliveryDays<int>();
			cout << "Numarul de zile pentru livrare: " << deliveryDaysInt << endl;
			return 0;
		}
	}
	return 0;
}

