#include <iostream>
#include <sstream>
#include <string>
using namespace std;
///Statyczne zmienne okre�laj�ce wielko�� planszy
const int M = 10;
const int N = 6;
///Funkcja sprawdzaj�ca czy podane 5 par punkt�w(po�o�enie klock�w w figurze) s� w prawid�owym miejscu
// T
void sprawdzPozycje(char **plansza, int **pozycje, char znak)
{
	bool poprawnaPozycja = true;
	for (int k = 0; k < N; k++)
	{
		for (int l = 0; l < M; l++)
		{
			if (plansza[k][l] == znak)
			{
				cout << "Wykorzystano juz ten klocek!" << endl;
				return;
			}
		}
	}
	for (int i = 0; i < 5; i++)
	{
	    //Sprawdzanie czy dany punkt znajduje si� na planszy
		if (pozycje[i][1] > M || pozycje[i][1] < 0 || pozycje[i][0] < 0 || pozycje[i][0] > N)
		{
			cout << "Nie poprawne polozenie klocka" << endl;
			poprawnaPozycja = false;
			break;
		}
		//Sprawdzanie czy dany punkt na planszy jest pusty (znak kropki)
		if (plansza[pozycje[i][0]][pozycje[i][1]] != '.')
		{
			cout << "Miejsce jest juz zajete!" << endl;
			poprawnaPozycja = false;
			break;
		}
	}
	//Je�li dla danego zestawu klock�w nie znaleziono �adnych problem�w, mo�na na planszy umie�ci� dan� figur�
	if (poprawnaPozycja)
	{
		plansza[pozycje[0][0]][pozycje[0][1]] = znak;
		plansza[pozycje[1][0]][pozycje[1][1]] = znak;
		plansza[pozycje[2][0]][pozycje[2][1]] = znak;
		plansza[pozycje[3][0]][pozycje[3][1]] = znak;
		plansza[pozycje[4][0]][pozycje[4][1]] = znak;
	}
}
void dodajKlocek(char **plansza, char znak, int rotacja, int pozX, int pozY)
{
	int **pozycje; //tablica par punkt�w dla danej figury
	pozycje = new int *[5];
	for (int i = 0; i < 5; i++)
	{
		pozycje[i] = new int[2];
	}
	int xOffset1 = 0;
	int xOffset2 = 0;
	int xOffset3 = 0;
	int xOffset4 = 0;

	int yOffset1 = 0;
	int yOffset2 = 0;
	int yOffset3 = 0;
	int yOffset4 = 0;
	int rot = rotacja / 90; //Obliczanie przypadk�w z dowolnego k�ta co 90 stopni (dla 0 stopni taka sama liczba jak dla 360)
	rot = rot % 4;
	//Case 0: 0, 360 stopni, Case 1: 90, Case 2: 180, Case 3: 270
	//R�czne ustawianie po�ozenia klock�w dla ka�dego z 4 mo�liwych obrot�w
	switch (znak)
	{
	case '#':
		switch (rot)
		{
		case 0:
			xOffset3 = 1; xOffset4 = 2;
			yOffset1 = -1; yOffset2 = -2;
			break;
		case 1:
			xOffset3 = 1; xOffset4 = 2;
			yOffset1 = 1; yOffset2 = 2;
			break;
		case 2:
			xOffset3 = -1; xOffset4 = -2;
			yOffset1 = -1; yOffset2 = -2;
			break;
		case 3:
			xOffset3 = -1; xOffset4 = -2;
			yOffset1 = -1; yOffset2 = -2;
			break;
		}
		break;
	case 'H':
		xOffset3 = -1; xOffset4 = 1;
		yOffset1 = 1; yOffset2 = -1;
		break;
	case '$':
		switch (rot)
		{
		case 0: case 2:
			yOffset1 = 1; yOffset2 = 2;
			yOffset3 = -1; yOffset4 = -2;
			break;
		case 1: case 3:
			xOffset1 = 1; xOffset2 = 2;
			xOffset3 = -1; xOffset4 = -2;
			break;
		}
		break;
	case '1':
        switch(rot)
        {
        case 0:
			xOffset3 = -1; xOffset4 = 1;
			yOffset1 = 1; yOffset2 = 2;
			break;
		case 1:
			xOffset3 = -1; xOffset4 = -2;
			yOffset1 = 1; yOffset2 = -1;
			break;
		case 2:
			xOffset3 = -1; xOffset4 = 1;
			yOffset1 = -1; yOffset2 = -2;
			break;
		case 3:
			xOffset3 = 1; xOffset4 = 2;
			yOffset1 = 1; yOffset2 = -1;
			break;
        }
		break;
    case '2':
        switch(rot)
        {
        case 0:
			xOffset4 = -1; yOffset3 = -1;
			yOffset1 = 1; yOffset2 = 2;
			break;
		case 1:
			yOffset4 = -1; xOffset3 = 1;
			xOffset1 = -1; xOffset2 = -2;
			break;
		case 2:
			xOffset4 = 1; yOffset3 = 1;
			yOffset1 = -1; yOffset2 = -2;
			break;
		case 3:
			yOffset4 = 1; xOffset3 = 1;
			xOffset1 = -1; xOffset2 = 2;
			break;
        }
        break;
     case '%':
        switch(rot)
        {
        case 0:
			yOffset1 = 1; yOffset3 = 2;
			xOffset2 = -1; yOffset2 = 1;
			xOffset4 = -1; yOffset4 = 2;
			break;
		case 1:
			xOffset1 = -1; xOffset3 = -2;
			xOffset2 = -1; yOffset2 = -1;
			xOffset4 = -2; yOffset4 = -1;
			break;
		case 2:
			yOffset1 = -1; yOffset3 = -2;
			xOffset2 = 1; yOffset2 = -1;
			xOffset4 = 1; yOffset4 = -2;
			break;
		case 3:
			xOffset1 = 1; xOffset3 = 2;
			xOffset2 = 1; yOffset2 = 1;
			xOffset4 = 2; yOffset4 = 1;
			break;
        }
        break;
    case '3':
        switch(rot)
        {
        case 0:
			xOffset3 = -1; xOffset4 = 1;
            yOffset1 = 1; xOffset1 = -1;
            yOffset2 = -1;
			break;
		case 1:
			xOffset3 = -1; yOffset3 = -1;
			xOffset4 = 1;
            yOffset1 = 1; yOffset2 = -1;
			break;
		case 2:
			xOffset3 = -1;
			xOffset4 = 1; yOffset4 = -1;
			xOffset2 = 1; yOffset1 = 1;
			break;
		case 3:
			xOffset3 = -1;
			xOffset4 = 1; yOffset4 = 1;
            yOffset1 = 1; yOffset2 = -1;
			break;
        }
        break;
     case '6':
        switch(rot)
        {
        case 0:
			xOffset4 = 1; yOffset1 = 1;
			xOffset2 = -1; yOffset2 = 1;
			xOffset3 = -2; yOffset3 = 1;
			break;
		case 1:
            yOffset1 = 1; xOffset2 = -1;
            xOffset3 = -1; yOffset3 = -1;
            xOffset4 = -1; yOffset4 = -2;
			break;
		case 2:
            xOffset1 = -1; yOffset2 = -1;
            xOffset3 = 1; yOffset3 = -1;
            xOffset4 = 2; yOffset4 = -1;
			break;
		case 3:
            yOffset1 = -1; xOffset2 = 1;
            xOffset3 = 1; yOffset3 = 1;
            xOffset4 = 1; yOffset4 = 2;
			break;
        }
        break;
    case '@':
		switch (rot)
		{
		case 0:
			xOffset1 = 1; xOffset2 = -1;
			xOffset3 = -1; yOffset3 = 1;
			xOffset4 = 1; yOffset4 = 1;
			break;
		case 1:
			yOffset1 = 1; yOffset2 = -1;
			yOffset3 = -1; xOffset3 = -1;
			yOffset4 = 1; xOffset4 = -1;
			break;
		case 2:
			xOffset1 = 1; xOffset2 = -1;
			xOffset3 = -1; yOffset3 = -1;
			xOffset4 = 1; yOffset4 = -1;
			break;
		case 3:
			yOffset1 = 1; yOffset2 = -1;
			yOffset3 = -1; xOffset3 = 1;
			yOffset4 = 1; xOffset4 = 1;
			break;
		}
		break;
    case '?':
		switch (rot)
		{
		case 0:
            xOffset1 = 1; yOffset2 = 1;
            xOffset3 = 1; yOffset3 = -1;
            xOffset4 = -1; yOffset4 = 1;
			break;
		case 1:
            xOffset1 = -1; yOffset2 = 1;
            xOffset3 = -1; yOffset3 = -1;
            xOffset4 = 1; yOffset4 = 1;
			break;
		case 2:
            xOffset1 = -1; yOffset2 = -1;
            xOffset3 = -1; yOffset3 = 1;
            xOffset4 = 1; yOffset4 = -1;
			break;
		case 3:
            xOffset1 = 1; yOffset2 = -1;
            xOffset3 = -1; yOffset3 = -1;
            xOffset4 = 1; yOffset4 = 1;
			break;
		}
		break;
    case 'V':
		switch (rot)
		{
		case 0:
            yOffset1 = -1; xOffset2 = -1;
            xOffset3 = -2; xOffset4 = -3;
			break;
		case 1:
            xOffset1 = 1; yOffset2 = -1;
            yOffset3 = -2; yOffset4 = -3;
			break;
		case 2:
            yOffset1 = 1; xOffset2 = 1;
            xOffset3 = 2; xOffset4 = 3;
			break;
		case 3:
            xOffset1 = -1; yOffset2 = 1;
            yOffset3 = 2; yOffset4 = 3;
			break;
		}
		break;
    case '0':
		switch (rot)
		{
		case 0:
            yOffset1 = -1; xOffset2 = 1;
            xOffset3 = 2; xOffset4 = 2;
            yOffset4 = 1;
			break;
		case 1:
            xOffset1 = 1; yOffset2 = 1;
            yOffset3 = 2; yOffset4 = 2;
            xOffset4 = -1;
			break;
		case 2:
            yOffset1 = 1; xOffset2 = -1;
            xOffset3 = -2; xOffset4 = -2;
            yOffset4 = -1;
			break;
		case 3:
            xOffset1 = -1; yOffset2 = -1;
            yOffset3 = -2; yOffset4 = -2;
            xOffset4 = 1;
			break;
		}
		break;
	default:
		cout << "Podano zly znak klocka!\n" << endl;
		break;
	}
	//Domyslny punkt poczatkowy
	pozycje[0][0] = N - pozY;
	pozycje[0][1] = pozX - 1;

	//Cztery dodatkowe pola, dla kazdej figury inne ulozenie klock�w
	pozycje[1][0] = (N - pozY) + yOffset1;
	pozycje[1][1] = (pozX - 1) + xOffset1;

	pozycje[2][0] = (N - pozY) + yOffset2;
	pozycje[2][1] = (pozX - 1) + xOffset2;

	pozycje[3][0] = (N - pozY) + yOffset3;
	pozycje[3][1] = (pozX - 1) + xOffset3;

	pozycje[4][0] = (N - pozY) + yOffset4;
	pozycje[4][1] = (pozX - 1) + xOffset4;

	sprawdzPozycje(plansza, pozycje, znak);
}
void wprowadzKlocek(char **plansza)
{
	string ruchy;
	cout << "\nPodaj ruchy na planszy ([Znak] [Rotacja] [X] [Y]): ";
	getline(cin, ruchy);
	stringstream sRuchy;
	sRuchy.str(ruchy);
	string s;
	int index = 0;

	///Parametry dla klocka
	char znak = ' ';
	int rotacja = 0;
	int pozX = 0;
	int pozY = 0;

	while (getline(sRuchy, s, ' ')) //Odczytywanie podanej linii znak�w i liczb, dop�ki jest, odczytuje jeden znak/liczb� rozdzielan� poprzez znak spacji
	{
		switch (index)
		{
		case 0:
			znak = s[0];
			break;
		case 1:
			istringstream(s) >> rotacja;
            //Sprawdzanie czy podana rotacja klocka jest kolejnym obrotem o 90 stopni (czy rotacja r�wna si� 0, 90, 180 itd.)
			if (rotacja % 90 != 0)
			{
				cout << "Podano bledny obrot klocka!" << endl;
				return;
			}
			break;
		case 2:
			istringstream(s) >> pozX;
			//Sprawdzanie czy pozycja po osi X jest poprawna
			if (pozX < 1 || pozX > M)
			{
				cout << "Niepoprawna pozycja klocka!" << endl;
				return;
			}
			break;
		case 3:
			istringstream(s) >> pozY;
			//Sprawdzanie czy pozycja po osi Y jest poprawna
			if (pozY < 1 || pozY > N)
			{
				cout << "Niepoprawna pozycja klocka!" << endl;
				return;
			}
			//Je�li p�tla dojdzie do tego case znaczy to �e wpisano poprawnie ca�� linie dla jednej figury i mo�na doda� klocek na plansz�
			dodajKlocek(plansza, znak, rotacja, pozX, pozY);
			break;
		}
		index++;
		if (index == 4)
			index = 0;
	}
}
void wyswietlPlansze(char **plansza)
{
	cout << endl;
	for (int i = 0; i < N; i++)
	{
		for (int j = 0; j < M; j++)
		{
			cout << " " << plansza[i][j];
		}
		cout << endl;
	}
	cout << endl;
}
bool sprawdzPlansze(char **plansza)
{
    for (int k = 0; k < N; k++)
	{
		for (int l = 0; l < M; l++)
		{
			if (plansza[k][l] == '.')
			{
				return false;
			}
		}
	}
	return true;
}
int main()
{
    //Utworzenie dynamicznej tablicy dwuwymiarowej, kt�r� mo�na �atwo przekazywa� jako argument funkcji
	char **plansza;
	plansza = new char *[M];
	for (int i = 0; i < M; i++)
	{
		plansza[i] = new char[N];
	}
    //Wype�nienie ca�ej planszy znakiem '.' w naszym przypadku oznacza to pusty element tablicy
	for (int i = 0; i < N; i++)
	{
		for (int j = 0; j < M; j++)
		{
			plansza[i][j] = '.';
		}
	}
    bool planszaZapelniona = false;
    //P�tla wykonuje si� dop�ki znajduje si� jeden niewype�niony element tablicy
	while (!planszaZapelniona)
	{
	    wyswietlPlansze(plansza);
		wprowadzKlocek(plansza);
        planszaZapelniona = sprawdzPlansze(plansza);
	}
	wyswietlPlansze(plansza);
	cout << "Zapelniono cala plansze!" << endl;
	return 0;
}

