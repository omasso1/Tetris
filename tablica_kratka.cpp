#include <iostream>
#include "Header.h"
using namespace std;
extern int punkty;
void pokaz(int , int ,char);
kratka::kratka()
{
	x = 1;
	y = 1;
	wek_x = 0;
	wek_y = 0;
	czesc = true;
	typ = 1;
}
kratka::kratka(const kratka &kratka_)
{
	x = kratka_.x;
	y = kratka_.y;
	wek_x = kratka_.wek_x;
	wek_y = kratka_.wek_y;
}
kratka::~kratka()
{
	;
}


tablica::tablica()
{
	rozmiar = 0;
	tab = NULL;
}
tablica::~tablica()
{
	;
}

void tablica::dodaj(kratka* tab_)
{
	kratka* tab_nowe = new kratka[4];
	int j = 0;
	tab_nowe = new kratka[rozmiar + 4];
	memcpy(tab_nowe, tab, rozmiar * sizeof(kratka));
	for (int i = rozmiar; i < rozmiar + 4; i++)
	{
		tab_nowe[i] = tab_[j];
		j++;
	}
	delete[] tab;
	rozmiar += 4;
	tab = new kratka[rozmiar];
	tab = tab_nowe;
}


bool tablica::sprawdz()
{
	int w;
	int tab_[26];
	for (int i = 0; i < 26; i++)
	{
		tab_[i] = 0;
	}
	for (int i = 0; i < rozmiar; i++)
	{
		tab_[tab[i].y]++;
		if ((tab_[tab[i].y]) == 10) {
			w = tab[i].y;
			usun(tab[i].y);
			for (int j = 0; j < rozmiar; j++)
			{
				if (tab[j].y < w) tab[j].y++;
			}
			i = rozmiar;
			return sprawdz();
			break;
		}
		if (tab[i].y <=5) return false;
	}
	return true;
}

void tablica::usun(int y)
{
	kratka* tab_nowe = new kratka[rozmiar - 10];
	int j = 0;
	for (int i = 0; i < rozmiar; i++)
	{
		if (tab[i].y != y) {
			tab_nowe[j] = tab[i];
			j++;
		}
	}
	delete[] tab;
	tab = new kratka[rozmiar - 10];
	memcpy(tab, tab_nowe, sizeof(kratka)*(rozmiar - 10));
	rozmiar -= 10;
	punkty++;

}

void tablica::wyswietl()
{
	for (int i = 0; i < rozmiar; i++)
	{
		pokaz(tab[i].x, tab[i].y,tab[i].typ);
		//cout << tab[i].y;
	}
}

kratka tablica::z(int indeks)
{
	return tab[indeks];
}


