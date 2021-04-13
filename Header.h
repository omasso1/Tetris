#include <iostream>
using namespace std;
extern class linia;
extern class tablica;
class kratka
{
public:
	int x;
	int y;
	int wek_x;
	int wek_y;
	bool czesc;
	int typ;

	kratka();
	kratka(const kratka&);
	~kratka();



};

class figura
{
public:
	linia *wsk;
	figura *wsk2;
	
	kratka *seg;
	kratka *glowa;
	int wielkosc;
	int obr;
	int przesun_;
	char typ;
	figura();
	figura(const figura&);
	virtual ~figura();
	virtual void obroc(tablica);
	void wyswietl();
	void wyswietl(int,int);
    void przesun(int,int,tablica);
	int sprawdz(tablica,int);
	void przypisz(figura);
	//figura* Wsk();
	//figura* Wsk_2();


};



class linia : public figura
{
public:
	linia();
	~linia();
};

class tablica
{
public:
	int rozmiar;
	kratka* tab;

    
	void dodaj(kratka*);
	void usun(int);
	void wyswietl();
	kratka z(int);
	bool sprawdz();

	tablica();
	~tablica();
};

class kwadrat : public figura
{
public:

    virtual void obroc(tablica);
	kwadrat();
	~kwadrat();
};

class trojkat : public figura
{
public:

	trojkat();
	~trojkat();

};

class L : public figura
{
public:

	L();
	~L();
};

class L_2 : public figura
{
public:

	L_2();
	~L_2();
};

class Z :public figura
{
public:

	Z();
	~Z();
};

class Z_2 :public figura
{
public:
	Z_2();
	~Z_2();
};

