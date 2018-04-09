#include <iostream>
#include <stack>
#include <ctime>
#include <cstdlib>
#include <vector>
#include <string>
#include <conio.h>
#include <stdio.h>
#include <iomanip>
#include <Windows.h>

using namespace std;

const int rozmiar_pociagu = 100;
const int dl_szyny = 20;

struct rozjazd
{
	char warunek[4];
	vector<char> szyna;
	int il_wagonow;
	bool dobrze;
};

void losuj_wagony(stack<char>&);
void wywolaj_warunki(stack<char>, rozjazd&, rozjazd&, rozjazd&, rozjazd&, rozjazd&);
void menu_glowne(stack<char>, rozjazd, rozjazd, rozjazd, rozjazd, rozjazd, int);

void rozpocznij_gre(stack<char>, rozjazd, rozjazd, rozjazd, rozjazd, rozjazd, int);
void wypisz_ekran_gry(stack<char>, rozjazd, rozjazd, rozjazd, rozjazd, rozjazd, int);
void wypisz_ostatnie_wagony(stack<char>);
void wypisz_szyne(rozjazd);
void wyswietl_tor(rozjazd);
void dodaj_wagon(stack<char>&, rozjazd&, int&);
bool sprawdz_nowy_wagon(rozjazd&);
void czyszczenie_szyny(rozjazd&);

void rys_menu();
void rys_legende();
void wprowadzenie();


// Funkcja glowna programu
int main()
{
	stack <char> wagony;
	rozjazd tor1, tor2, tor3, tor4, tor5;
	tor1.il_wagonow = tor2.il_wagonow = tor3.il_wagonow = tor4.il_wagonow = tor5.il_wagonow = 0;
	int punkty = 20;

		losuj_wagony(wagony);
		wywolaj_warunki(wagony, tor1, tor2, tor3, tor4, tor5);
		menu_glowne(wagony, tor1, tor2, tor3, tor4, tor5, punkty);

	system("Pause");
	return 0;
}

//Funkcja losujaca wagony do pociagu
void losuj_wagony(stack<char> & wagony)
{
	int tab[4] = { 68, 71, 82, 87 };
	srand(time(NULL));
	while (true)
	{
		int wagon = 68 + rand() % (87 - 68 + 1);//int wagon = rand() % (19 + 68);
		for (int j = 0; j < 4; j++)
		{
			if (wagon == tab[j])
				wagony.push(static_cast<char>(wagon));
		}
		if (wagony.size() == rozmiar_pociagu)
			break;
	}
}

//Funkcja wywolujaca zapotrzebowanie do torow w zaleznosci od wylosowanych wagonow
void wywolaj_warunki(stack<char> wagony, rozjazd &tor1, rozjazd &tor2, rozjazd &tor3, rozjazd &tor4, rozjazd &tor5)
{
	char* temp;
	temp = new char[wagony.size()];
	for (int i = 0; i<wagony.size(); i++)
	{
		temp[i] = wagony.top();
		wagony.pop();
	}
	for (int i = 3, j=0; i >=0; i--, j+=5)
	{
		tor4.warunek[i] = temp[j];
		tor3.warunek[i] = temp[j + 1];
		tor1.warunek[i] = temp[j + 2];
		tor2.warunek[i] = temp[j + 3];
		tor5.warunek[i] = temp[j + 4];

	}
	for (int i = 0; i < dl_szyny; i++)
	{
		tor1.szyna.push_back('=');
		tor2.szyna.push_back('=');
		tor3.szyna.push_back('=');
		tor4.szyna.push_back('=');
		tor5.szyna.push_back('=');
	}
}
//Wywolanie menu glownego programu
void menu_glowne(stack<char> wagony, rozjazd tor1, rozjazd tor2, rozjazd tor3, rozjazd tor4, rozjazd tor5, int punkty)
{
	int wybor;
	while (true)
	{
		rys_menu();
		cout << "Wybierz: ";
		cin >> wybor;
		switch (wybor)
		{
		case 1:
			system("cls");
			wprowadzenie();
			break;
		case 2:
			system("cls");
			rozpocznij_gre(wagony, tor1, tor2, tor3, tor4, tor5, punkty);
			break;
		case 3:
			system("cls");
			exit(0);
			break;
		}
		getchar();getchar();
		system("cls");

	}
}
//Funkcja glowna dzialania gry
void rozpocznij_gre(stack<char> wagony, rozjazd tor1, rozjazd tor2, rozjazd tor3, rozjazd tor4, rozjazd tor5, int punkty)
{
	while (true)
	{
		string zwolnij;
		wypisz_ekran_gry(wagony, tor1, tor2, tor3, tor4, tor5, punkty);
		cin >> zwolnij;
		if (zwolnij == "1w")
			dodaj_wagon(wagony, tor1, punkty);
		else if (zwolnij == "2w")
			dodaj_wagon(wagony, tor2, punkty);
		else if (zwolnij == "3w")
			dodaj_wagon(wagony, tor3, punkty);
		else if (zwolnij == "4w")
			dodaj_wagon(wagony, tor4, punkty);
		else if (zwolnij == "5w")
			dodaj_wagon(wagony, tor5, punkty);
		else if (zwolnij == "z")
			break;
		else
		{
			cout << endl << "Brak takiego toru!" << endl;
			Sleep(1800);
			system("cls");
		}
		if (punkty < 0)
		{
			cout << "Niestety nie udalo Ci sie wygrac :(. Liczba Twoich punktow spadla ponizej 0." << endl;
			cout << " Aby wrocic do MENU nacisnij ENTER" << endl;
			//getchar();getchar();
			break;
		}
		if (punkty >= 50) {
			cout << "Gratulacje! Udalo Ci sie osiagnac 50 punktow! Wygrywasz!" << endl;
			cout << "Aby wrocic do menu wcisnij ENTER." << endl;
			//getchar();getchar();
			break;
		}
	}

}
//Wypisuje aktualny stan gry
void wypisz_ekran_gry(stack<char> wagony, rozjazd tor1, rozjazd tor2, rozjazd tor3, rozjazd tor4, rozjazd tor5, int punkty)
{
	system("cls");
	cout << "Twoje punkty: " << punkty << endl << "8 ostatnich wagonow pociagu" << endl;
	wypisz_ostatnie_wagony(wagony);
	cout << "    =====";
	wypisz_szyne(tor1);
	cout << "    TOR1  ZAPOTRZEBOWANIE: ";
	wyswietl_tor(tor1);
	for (int i = 0; i < 9; i++) cout << setw(3) << " ";
	cout << "\\\\ (2)";
	wypisz_szyne(tor2);
	cout << "    TOR2  ZAPOTRZEBOWANIE: ";
	wyswietl_tor(tor2);
	for (int i = 0; i < 9; i++) cout << setw(3) << " ";
	cout << "\\\\ (3)";
	wypisz_szyne(tor3);
	cout << "    TOR3  ZAPOTRZEBOWANIE: ";
	wyswietl_tor(tor3);
	for (int i = 0; i < 9; i++) cout << setw(3) << " ";
	cout << "\\\\ (4)";
	wypisz_szyne(tor4);
	cout << "    TOR4  ZAPOTRZEBOWANIE: ";
	wyswietl_tor(tor4);
	for (int i = 0; i < 9; i++) cout << setw(3) << " ";
	cout << "\\\\ (5)";
	wypisz_szyne(tor5);
	cout << "    TOR5  ZAPOTRZEBOWANIE: ";
	wyswietl_tor(tor5);
	rys_legende();
	cout << "Wybierz numer toru oraz uzyj klawisza 'w' aby zwolnic ostatni wagon z pociagu(np.'2w'): ";
}
//Wypisuje ostanie 8 wagonow pociagu, ktore beda przydzielane do wybranych torow
void wypisz_ostatnie_wagony(stack<char> wagony)
{
	char* temp;
	temp = new char[wagony.size()];
	for (int i = 0; i<wagony.size(); i++)
	{
		temp[i] = wagony.top();
		wagony.pop();
	}
	for (int i = 7; i >= 0;i--)
	{
		cout << setw(3) << temp[i];
	}
	delete[] temp;
}

// Wypisuje szyne poszczegolnego toru
void wypisz_szyne(rozjazd tor)
{
	for (int i = 0; i < tor.szyna.size(); i++)
		cout << tor.szyna[i];
}
//Funkcja wyswietlajaca warunek - zapotrzebowanie toru
void wyswietl_tor(rozjazd tor)
{
	cout << "[";
	for (int i = 0; i < 4; i++)
		cout << setw(3) << tor.warunek[i];
	cout << "  ]" << endl;
}
//Funkcja dodajaca wagon do szyny konkretnego toru
void dodaj_wagon(stack<char> &wagony, rozjazd &tor, int &punkty)
{
	tor.szyna[tor.szyna.size() - tor.il_wagonow - 1] = wagony.top();
	tor.il_wagonow++;
	wagony.pop();
	if (!sprawdz_nowy_wagon(tor))
	{
		punkty -= 10;
		cout << endl << "Nie udalo sie dopasowac wagonow do zapotrzebowania ( -10 punktow ) !" << endl;
		Sleep(2500);
		czyszczenie_szyny(tor);
	}
	if (tor.dobrze == true && tor.il_wagonow == 4)
	{
		punkty += 10;
		cout << endl << "Gratulacje! Udalo Ci sie zlozyc jeden sklad! ( +10 punktow ) !" << endl;
		Sleep(2500);
		czyszczenie_szyny(tor);
	}
}
//Funkcja sprawdzajaca czy nowododany wagon zgadza sie z zapotrzebowaniem
bool sprawdz_nowy_wagon(rozjazd &tor)
{
	bool temp = false;
	for (int i = 0, j = 3; i < tor.il_wagonow && j >= 0; i++, j--)
	{
		if (tor.szyna[tor.szyna.size() - i - 1] == tor.warunek[j])
		{
			if (tor.il_wagonow == 4)
				tor.dobrze = true;
			temp = true;
		}
		else
		{
			tor.dobrze = false;
			temp = false;
			break;
		}
	}
	return temp;
}

//Ustawia szyne na stan domyslny i ustawia ilosc wagonow na 0
void czyszczenie_szyny(rozjazd &tor)
{
	tor.szyna.clear();
	for (int i = 0; i < dl_szyny; i++)
	{
		tor.szyna.push_back('=');
	}
	tor.il_wagonow = 0;
}

void rys_menu()
{
	cout << "|";
	for (int i = 0; i<40; i++)
		cout << "-";
	cout << "|" << endl;

	for (int i = 0; i<12; i++) cout << " ";
	cout << "MENU GLOWNE PROGRAMU" << endl;

	cout << "|";
	for (int i = 0; i<40; i++)
		cout << "-";
	cout << "|" << endl;

	for (int i = 0; i<10; i++) cout << " ";
	cout << "1. Instrukcja o programie" << endl;

	cout << "|";
	for (int i = 0; i<40; i++)
		cout << "-";
	cout << "|" << endl;

	for (int i = 0; i<10; i++) cout << " ";
	cout << "2. Rozpocznij Gre" << endl;

	cout << "|";
	for (int i = 0; i<40; i++)
		cout << "-";
	cout << "|" << endl;

	for (int i = 0; i<10; i++) cout << " ";
	cout << "3. Zakoncz dzialanie programu";

	cout << endl << "|";
	for (int i = 0; i<40; i++)
		cout << "-";
	cout << "|" << endl;
}
void wprowadzenie()
{
	cout << "Witamy w programie obslugi bocznicy kolejowej!" << endl;
	cout << "Program polega na dopasowaniu odpowiednich wagonow do poszczegolnych torow - zgodnie z podpowiedziami obok kazdego toru." << endl;
	cout << "Sterowanie rozjazdami odbywa sie poprzez klawisze 2-5, zwalnianie wagonu klawiszem 'w'" << endl;
	cout << "Po skompletowaniu prawidlowego skladu tor jest zwalniany, a uzytkownik otrzymuje 10pkt." << endl;
	cout << "W przypadku gdy niemozliwa jest prawidlowa kompletacja(uzytkownik sie pomylil) odejmowanych jest 10pkt." << endl;
	cout << "Uzytkownik wygrywa, gdy osiagnie 50 pkt, przegrywa jesli liczba punktow bedzie mniejsza od zera." << endl;
	cout << "Na start masz 3 zycia - 20 punktow!" << endl;
	cout << "Komputer w zaleznosci od dlugosci poci¹gu losowo generuje typy wagonow, ktore okreslane sa nastepujaco:" << endl;
	cout << " litera W - wagon z weglem" << endl;
	cout << " litera D - wagon z drewnem" << endl;
	cout << " litera R - wagon z ropa" << endl;
	cout << " litera G - wagon z gazem" << endl;
	cout << "Wcisnij Enter aby  wrocic do menu!" << endl;
}

void rys_legende()
{
	cout << endl << "\\\\ - rozjazd pomiedzy torami" << endl;
	cout << "==== - tory" << endl;
	cout << " litera W - wagon z weglem" << endl;
	cout << " litera D - wagon z drewnem" << endl;
	cout << " litera R - wagon z ropa" << endl;
	cout << " litera G - wagon z gazem" << endl;
	cout << "Zapotrzebowanie powinno byc ulozone w takiej kolejnosci jaka jest podana w nawiasach []." << endl << endl;
}
