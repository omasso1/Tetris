#include <iostream>
#include "Header.h"
#include <cstdlib>
#include <conio.h>
#include <windows.h>


void pokaz(int x, int y, char a)
{
	//BACKGROUND_RED 
	//BACKGROUND_GREEN 
	//BACKGROUND_BLUE 
	HANDLE h = GetStdHandle(STD_OUTPUT_HANDLE);
	COORD c;
	c.X = x - 1;
	c.Y = y - 1;
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), c);
	switch (a)
	{
	case '1':    SetConsoleTextAttribute(h, FOREGROUND_GREEN);                        cout << "0";     break; //linia
	case '2':    SetConsoleTextAttribute(h, FOREGROUND_BLUE);                         cout << "0";     break; //kwadrat
	case '3':    SetConsoleTextAttribute(h, FOREGROUND_BLUE | FOREGROUND_GREEN);      cout << "0";     break; //smieszny trojkat
	case '4':    SetConsoleTextAttribute(h, FOREGROUND_GREEN | FOREGROUND_RED);       cout << "0";     break; //L
	case '5':    SetConsoleTextAttribute(h, FOREGROUND_GREEN | FOREGROUND_RED);       cout << "0";     break; //L_2
	case '6':    SetConsoleTextAttribute(h, FOREGROUND_GREEN);                        cout << "0";     break; //Z
	case '7':    SetConsoleTextAttribute(h, FOREGROUND_GREEN | FOREGROUND_INTENSITY); cout << "0";     break; //Z_2
	case '8':    SetConsoleTextAttribute(h, FOREGROUND_RED);                          cout << "\1";    break; //tlo
	case '9':    SetConsoleTextAttribute(h, FOREGROUND_RED | FOREGROUND_INTENSITY);  cout << "\1"; break;                         cout << "\1";    break; //tlo
	}
}

figura::figura()
{
	wsk = NULL;
	wsk2 = NULL;
	seg = NULL;
	glowa = NULL;
	wielkosc = 0;
	obr = 1;
}
figura::figura(const figura& figura_)
{
	wsk = figura_.wsk;
    wsk2 = figura_.wsk2;
	seg = new kratka[4];
	memcpy(seg, figura_.seg, sizeof(kratka) * 4);
	glowa = &seg[1];
	wielkosc = figura_.wielkosc;
	obr = figura_.obr;
	typ = figura_.typ;
}
figura::~figura()
{
	if(seg!=NULL)
	delete[] seg;
	//delete wsk;
	//delete wsk2;
}


linia::linia()
{
	seg = new kratka[4];
	typ = '1';
	for (int i = 2; i < 4; i++)
	{
		seg[i].typ = '1';
		seg[i].x = 40;
		seg[i].y = i + 10;
		seg[i].wek_x = 0;
		seg[i].wek_y = i - 1;
	}
	seg[0].x = 40;
	seg[0].y = 5;
	seg[0].wek_x = 0;
	seg[0].wek_y = -1;
	seg[0].typ = '1';

	glowa = &seg[1];
	glowa->x = 40;
	glowa->y = 5;
	glowa->wek_x = 0;
	glowa->wek_y = 0;
	glowa->typ = '1';
	wielkosc = 4;
	obr = 1;
	typ = '1';
	przesun_ = 4;

}
linia::~linia()
{
	/*if (this->seg != NULL)
	{
	delete [] seg;
	}
	if(this->glowa!=NULL)
	delete glowa;*/
}

void figura::przypisz(figura figura_)
{
	this->glowa = figura_.glowa;
	this->obr = figura_.obr;
	this->wielkosc = figura_.wielkosc;
	delete[] seg;
	this->seg = new kratka[4];
	memcpy(this->seg, figura_.seg, sizeof(kratka) * 4);
	glowa = &seg[1];
}
void figura::wyswietl()
{
	for (int i = 0; i < 4; i++)
	{
		int x = this->seg[i].x;
		int y = this->seg[i].y;
		pokaz(x, y,this->typ);
	}
}
void figura::wyswietl(int x, int y)
{
	for (int i = 0; i < 4; i++)
	{
		int x_ = x + this->seg[i].wek_x;
		int y_ = y + this->seg[i].wek_y;
		pokaz(x_, y_, this->typ);
	}
}
void figura::przesun(int x, int y, tablica tab)
{
	
		this->glowa->y += y;
		this->glowa->x += x;
		for (int i = 0; i < this->wielkosc; i++)
		{
			if (&seg[i] != glowa)
			{
				this->seg[i].y = this->glowa->y + this->seg[i].wek_y;
				this->seg[i].x = this->glowa->x + this->seg[i].wek_x;
			}
		}

}
void figura::obroc(tablica tab)
{

	figura lin = figura(*this);
	/*******************************************/
	int k = 1;
	if (this->obr == 1)
	{
		k = -1;
		obr = 2;
	}
	obr--;

	for (int i = 0; i < 4; i++)
	{
		lin.seg[i].wek_y *= k;
		swap(lin.seg[i].wek_y, lin.seg[i].wek_x);

		for (int i = 0; i < lin.wielkosc; i++)
		{
			{
				lin.seg[i].y = lin.glowa->y + lin.seg[i].wek_y;
				lin.seg[i].x = lin.glowa->x + lin.seg[i].wek_x;
			}
		}
	}
	int j = lin.sprawdz(tab,6);
	if (!j)
	{
		this->przypisz(lin);
	}

	else if (j == -1) {
		lin.przesun(-this->przesun_-1, 0,tab); 
		if(!lin.sprawdz(tab,6))
		this->przypisz(lin);
	}
	else if (j == 1)
	{
		lin.przesun(this->przesun_+1, 0,tab);
		if(!lin.sprawdz(tab,6))
		this->przypisz(lin);
	}



	//cout << "3";
	/*******************************************/

}
int  figura::sprawdz(tablica tab_,int kr)
{
	for (int i = 0; i < 4; i++)
	{
		if (kr == 6) { if (seg[i].y >= 25)  return 5; }
		else if (seg[i].y >= 24)  return 5;
	}

	for (int i = 0; i < 4; i++)
	{
		if (kr == 6)
		{
				if (seg[i].x <= 34) return 1;
				if (seg[i].x >= 45) return -1;
		}
		else
		{
			if (kr == 1 || kr == 2)
				if (seg[i].x <= 35) return 1;
			if (kr == -1 || kr == 2)
				if (seg[i].x >= 44) return -1;
		}
	}
	

	for (int i = 0; i < tab_.rozmiar; i++)
	{
		for (int j = 0; j < 4; j++)
		{
			/*if ((seg[j].x == tab.z(i).x-1|| seg[j].x == tab.z(i).x + 1|| seg[j].x == tab.z(i).x) && (seg[j].y == tab.z(i).y - 1|| seg[j].y == tab.z(i).y))
				if (seg[j].x < tab.z(i).x) return -1;
				else return 1;*/
			if (kr==6)
			{
					if (seg[j].x == tab_.z(i).x  && seg[j].y == tab_.z(i).y) return 5;
					if (seg[j].x == tab_.z(i).x  && seg[j].y == tab_.z(i).y) return -1;
			}
			else {
				if (kr == 3 || kr == 2)
					if (seg[j].x == tab_.z(i).x  && seg[j].y == tab_.z(i).y - 1) return 5;
				if (kr == -1 || kr == 2)
					if (seg[j].x == tab_.z(i).x - 1 && seg[j].y == tab_.z(i).y) return -1;
				if (kr == 1 || kr == 2)
					if (seg[j].x == tab_.z(i).x + 1 && seg[j].y == tab_.z(i).y) return 1;
			}
		}
	}
	return 0;
}

kwadrat::kwadrat()
{
	seg = new kratka[4];
	for (int i = 0; i < 4; i++)
	{
		seg[i].typ = '2';
	}
	typ = '2';
	
	seg[0].x = 40;
	seg[0].y = 5;
	seg[1].x = 41;
	seg[1].y = 5;
	seg[2].x = 40;
	seg[2].y = 6;
	seg[3].x = 41;
	seg[3].y = 6;
	glowa = &seg[1];
	seg[0].wek_x = -1;
	seg[0].wek_y = 0;
	seg[1].wek_x = 0;
	seg[1].wek_y = 0;
	seg[2].wek_x = -1;
	seg[2].wek_y = 1;
	seg[3].wek_x = 0;
	seg[3].wek_y = 1;
	wielkosc = 4;
}
kwadrat::~kwadrat()
{
	;
}

void kwadrat::obroc(tablica tab)
{
	;
}


trojkat::trojkat()
{
	seg = new kratka[4];
	for (int i = 0; i < 4; i++)
	{
		seg[i].typ = '3';
	}
	wielkosc = 4;
	
	glowa = &seg[1];
	obr = 1;
	typ = '3';

	seg[0].x = 39;
	seg[0].y = 5;
	seg[1].x = 40;
	seg[1].y = 5;
	seg[2].x = 41;
	seg[2].y = 5;
	seg[3].x = 40;
	seg[3].y = 6;

	seg[1].wek_x = 0;
	seg[1].wek_y = 0;
	seg[0].wek_x = -1;
	seg[0].wek_y = 0;
	seg[2].wek_x = 1;
	seg[2].wek_y = 0;
	seg[3].wek_x = 0;
	seg[3].wek_y = 1;
	przesun_ = 2;
}
trojkat::~trojkat()
{
	;
}


L::L()
{
	seg = new kratka[4];
	for (int i = 0; i < 4; i++)
	{
		seg[i].typ = '4';
	}
	wielkosc = 4;
	
	glowa = &seg[1];
	obr = 1;
	typ = '4';

	seg[1].x = 40;
	seg[1].y = 5;
	seg[0].x = 39;
	seg[0].y = 5;
	seg[2].x = 41;
	seg[2].y = 5;
	seg[3].x = 41;
	seg[3].y = 6;

	seg[1].wek_x = 0;
	seg[1].wek_y = 0;
	seg[0].wek_x = -1;
	seg[0].wek_y = 0;
	seg[2].wek_x = 1;
	seg[2].wek_y= 0;
	seg[3].wek_x = 1;
	seg[3].wek_y = 1;
	przesun_ = 2;
}
L::~L()
{
	;
}


L_2::L_2()
{
	seg = new kratka[4];
	for (int i = 0; i < 4; i++)
	{
		seg[i].typ = '5';
	}
	wielkosc = 4;
	
	glowa = &seg[1];
	obr = 1;
	typ = '5';

	seg[1].x = 40;
	seg[1].y = 5;
	seg[0].x = 39;
	seg[0].y = 5;
	seg[2].x = 41;
	seg[2].y = 5;
	seg[3].x = 39;
	seg[3].y = 6;

	seg[1].wek_x = 0;
	seg[1].wek_y = 0;
	seg[0].wek_x = -1;
	seg[0].wek_y = 0;
	seg[2].wek_x = 1;
	seg[2].wek_y = 0;
	seg[3].wek_x = -1;
	seg[3].wek_y = 1;
	przesun_ = 2;
}
L_2::~L_2()
{
	;
}


Z::Z() 
{
	seg = new kratka[4];
	for (int i = 0; i < 4; i++)
	{
		seg[i].typ = '6';
	}
	wielkosc = 4;
	
	glowa = &seg[1];
	obr = 1;
	typ = '6';

	seg[1].x = 40;
	seg[1].y = 5;
	seg[0].x = 39;
	seg[0].y = 5;
	seg[2].x = 40;
	seg[2].y = 6;
	seg[3].x = 41;
	seg[3].y = 6;

	seg[1].wek_x = 0;
	seg[1].wek_y = 0;
	seg[0].wek_x = -1;
	seg[0].wek_y = 0;
	seg[2].wek_x = 0;
	seg[2].wek_y = 1;
	seg[3].wek_x = 1;
	seg[3].wek_y = 1;
	przesun_ = 2;
}
Z::~Z()
{
	;
}


Z_2::Z_2()
{
	seg = new kratka[4];
	for (int i = 0; i < 4; i++)
	{
		seg[i].typ = '7';
	}
	wielkosc = 4;

	glowa = &seg[1];
	obr = 1;
	typ = '7';

	seg[1].x = 40;
	seg[1].y = 5;
	seg[0].x = 41;
	seg[0].y = 5;
	seg[2].x = 40;
	seg[2].y = 6;
	seg[3].x = 39;
	seg[3].y = 6;

	seg[1].wek_x = 0;
	seg[1].wek_y = 0;
	seg[0].wek_x = 1;
	seg[0].wek_y = 0;
	seg[2].wek_x = 0;
	seg[2].wek_y = 1;
	seg[3].wek_x = -1;
	seg[3].wek_y = 1;
	przesun_ = 2;
}
Z_2::~Z_2()
{
	;
}