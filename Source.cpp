#include <iostream>
#include <conio.h>
#include <time.h>
#include <windows.h>
#include <cstdlib>
#include "Header.h"
using namespace std;
void pokaz(int, int,char);
int punkty = 0;
void tlo()
{
	char a = '8';
	for (int i = 35; i < 45; i++) {
		for (int j = 5; j < 25; j++)
		{
			pokaz(i, j,a);
		}
		if ((i+1) % 2 == 0) a = '9';
		else a = '8';
	}
}

figura* losuj()
{
	srand(time(NULL));
	int r = rand() % 7 + 1;

	switch (r)
	{
	case 1:  return new linia; break;
	case 2:  return new kwadrat; break;
	case 3:  return new trojkat; break;
	case 4:  return new L; break;
	case 5:  return new L_2; break;
	case 6:  return new Z; break;
	case 7:  return new Z_2; break;
	}
}

/*****************************************/
int main()
{
    unsigned long long i = 0;
	figura* figura_ = losuj();
	figura* figura_next= losuj();
	tablica tab_;

	int y = 0;
	int x = 0;
	int d = 0;
	bool dalej =true;
	char kr;
	//linia_->przesun(0, 4, tab_);
	do
	{
		int spr = figura_->sprawdz(tab_, 3);
		if (spr == 5 && i % 10 == 0)
		{
			tab_.dodaj(figura_->seg);
			dalej=tab_.sprawdz();
			//delete linia_;
			delete figura_;
			figura_ = new figura(*figura_next);
			delete figura_next;
			figura_next = losuj();
		}
		else  d = 1;

			while (_kbhit()&&d==1)
			{
				kr = _getch();
				switch (kr)
				{
				case 'a': x = -1; break;
				case 'd': x = 1; break;
				case 'w': figura_->obroc(tab_); break;
				case 's': y = 1; break;
				default: break;
				}
				if (!figura_->sprawdz(tab_, -x))
				{
					figura_->przesun(x, 0, tab_);
				}//przesuwanie przez gracza
				if (!figura_->sprawdz(tab_, 3))
					figura_->przesun(0, y, tab_);
				x = 0;
				y = 0;
				d = 0;
				system("cls");
				tlo();
				figura_->wyswietl();
				figura_next->wyswietl(50, 7);
				SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_GREEN | FOREGROUND_BLUE | FOREGROUND_RED);
				cout << endl << "Punkty: " << punkty;
				tab_.wyswietl();
			}
		
		 spr = figura_->sprawdz(tab_,3);
		if (spr != 5 && i % 20 == 0) {
			figura_->przesun(0, 1, tab_);
			system("cls");
			tlo();
			figura_->wyswietl();
			figura_next->wyswietl(50, 7);
			SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_GREEN | FOREGROUND_BLUE | FOREGROUND_RED);
			cout << endl << "Punkty: " << punkty;
			tab_.wyswietl();//przesuwanie w dol
		}

		
			//	linia_->obroc(tab_);
	
		Sleep(25);
		i++;
		//wyswietlanie
		/*system("cls");
		    tlo();
	        figura_->wyswietl();
			figura_next->wyswietl(50,7);
			SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_GREEN | FOREGROUND_BLUE | FOREGROUND_RED);
			cout << endl << "Punkty: " << punkty;
	        tab_.wyswietl();*/
	} while (dalej);

	HANDLE h = GetStdHandle(STD_OUTPUT_HANDLE);
	COORD c;
	c.X = 1- 1;
	c.Y = 8- 1;
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), c);
	SetConsoleTextAttribute(h, FOREGROUND_INTENSITY);
	cout << "Przegrales ";
	//system("cls");
	delete figura_;
	delete figura_next;
	//linia_.wsk->seg = new kratka[4];
	//linia_.Wsk()->wyswietl();
	//cout<<typeid(*linia_).name();
	_getch();
	_getch();

	return 0;
}
/****************************************/





