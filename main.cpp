#include <iostream>
#include <time.h>
#include <stdlib.h>
#include <string.h>

using namespace std;

class Ckarta  //Tworzone w talii - 52 obiekty klasy CKarta
{
private:
	char Kolor[5];
	int Wartosc;
	char Figura[10];
public:
	Ckarta(int wartosc, int kolor)
{
	switch (kolor)
	{
	case 1:
	strcpy(Kolor,"pik");  //strcpy - stringcopy, przekopiowanie ci¹gu znaków do zmiennej typu char
	break;
	case 2:
	strcpy(Kolor,"kier");
	break;
	case 3:
	strcpy(Kolor,"karo");
	break;
	case 4:
	strcpy(Kolor,"trefl");
	break;
	default:
	strcpy(Kolor,"blad");
	break;}

	switch (wartosc)
	{
	case 11:
		strcpy(Figura,"Walet");
		Wartosc=10;
		break;
	case 12:
		strcpy(Figura,"Dama");
		Wartosc=10;
		break;
	case 13:
		strcpy(Figura,"Krol");
		Wartosc=10;
		break;
	case 14:
		strcpy(Figura,"As");
		Wartosc=11;
		break;
	default:
		strcpy(Figura,"Liczba");
		Wartosc=wartosc;
		break;

	}
}


~Ckarta(void)
{
}

void jakakarta()  //wyswietlenie info o karcie
{
	cout << "Rodzaj karty: " << Figura << " Kolor: " << Kolor << " Wartosc karty: " << Wartosc <<  endl;
}

int dajwartosc()
{
return Wartosc;
}

};


int main(void)
{
int iloscgraczy;
	cout << "Zasady gry w oczko:\nCelem gry jest zdobycie liczby punktow mozliwie najblizszej 21. Gracz, ktory zdobedzie powyzej 21 punktow, przegrywa.\nKarty maja nastepujaca liczbe punktow:\nKarty 2-10 - tyle punktow, ile wynosi wartosc karty\nFigury - kazda 10 punktow\nAs - 11 punktow\nKazdy gracz losuje na poczatku 2 karty, nastepnie moze zadecydowac, czy chce losowac nastepne. W wypadku wylosowania na pcozatku dwoch asow, gracz uzyskuje 'perskie oczko' i zdobywa 21 punktow.\nKrupier ciagnie karty tak dlugo, az uzyska minimum 17 punktow, wtedy, niezaleznie od wynikow graczy, musi skoczyc gre. Jezeli zarowno gracz, jak i krupier uzyskaja powyzej 21 punktow, zwyciezca jest krupier.\n\n" << "Ilu graczy (nie liczac krupiera) bierze udzial w grze? (minimum 1, maksimum 4)" << endl;

	return 0;
}
