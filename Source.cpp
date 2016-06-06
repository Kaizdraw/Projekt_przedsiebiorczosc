#include<iostream>
#include<fstream>
#include<string>
#include"Macierz.h"
using namespace std;

int main(){
	cout << "Prosze pliki z potencjalami zapisac w folderze w ktorym znajduje sie program.\nPotencjaly zdiabatyzowane beda zapisywane w tym folderze w plikach typu: \"Dpot_1.dat\" \n";
	int ilosc;
	int dlugosc;
	cout << "Ile potencjalow?\n";
	cin >> ilosc;
	cout << "Ile R?\n";
	cin >> dlugosc;	
	int i;
	int pomoc=0;
	for (i = 1; i <= ilosc; i++){
		pomoc += i;
	}
	Macierz *C = new Macierz[dlugosc];
	Macierz *Ud = new Macierz[dlugosc];
	Macierz *Ua = new Macierz[dlugosc];
	Macierz *P = new Macierz[dlugosc];
	fstream *dane = new fstream[pomoc];
	for (i = 0; i < dlugosc; i++){
		C[i].tworzenie(ilosc);
		Ud[i].tworzenie(ilosc);
		Ua[i].tworzenie(ilosc);
		P[i].tworzenie(ilosc);
	}
	double pomoc2[2];
	string nazwa_pliku = "pot_1.dat";
	//cout << nazwa_pliku << endl;
	dane[0].open(nazwa_pliku);
	if (dane[0].is_open())
	{
		for (i = 0; i < dlugosc; i++){
			dane[0] >> pomoc2[0] >> pomoc2[1];
			Ua[i].set_R(pomoc2[0]);
			Ua[i].set_macierz(0, 0, pomoc2[1]);
		}
		dane[0].close();
	}
	else
		cout << "Nieudalo sie otworzyc pliku " << nazwa_pliku << endl;
	for (i = 1; i < ilosc; i++){
		nazwa_pliku.erase(nazwa_pliku.begin()+4, nazwa_pliku.end());
		nazwa_pliku.append(to_string(i + 1) + ".dat");
		//cout << nazwa_pliku << endl;
		dane[i].open(nazwa_pliku);
		if (dane[i].is_open())
		{
			for (int j = 0; j < dlugosc; j++){
				dane[i] >> pomoc2[0] >> pomoc2[1];
				if (Ua[j].check_R(pomoc2[0]))
					Ua[j].set_macierz(i, i, pomoc2[1]);
				else{
					cout << "Blad w pliku " << nazwa_pliku << endl;
					return 1;
				}
			}
			dane[i].close();
		}
		else
			cout << "Nieudalo sie otworzyc pliku " << nazwa_pliku << endl;

	}
	int l = 0;
	for (i = 0; i < ilosc; i++){		
		for (int j = i+1; j < ilosc; j++){
			nazwa_pliku.erase(nazwa_pliku.begin() + 4, nazwa_pliku.end());
			nazwa_pliku.append(to_string(i + 1) + "_" + to_string(j + 1) + ".dat");
			//cout << nazwa_pliku << endl;
			dane[ilosc+l].open(nazwa_pliku);
			if (dane[ilosc + l].is_open())
			{
				for (int k = 0; k < dlugosc; k++){
					dane[ilosc + l] >> pomoc2[0] >> pomoc2[1];
					if (Ua[k].check_R(pomoc2[0])){
						Ua[k].set_macierz(i, j, pomoc2[1]);
						Ua[k].set_macierz(j, i, pomoc2[1]);
					}

					else{
						cout << "Blad w pliku " << nazwa_pliku << endl;
						return 1;
					}
				}
				dane[ilosc + l].close();
			}
			else
				cout << "Nieudalo sie otworzyc pliku " << nazwa_pliku << endl;
			l++;
		}
	}
	for (i = 0; i < dlugosc; i++){
		P[i] = Ua[i].zamiana_na_P();
	}
	double delta_r;
	Macierz pomoc_do_macierz1(ilosc);
	Macierz pomoc_do_macierz2(ilosc);
	Macierz pomoc_do_macierz3(ilosc);
	Macierz pomoc_do_macierz4(ilosc);
	Macierz jedostkowa(ilosc);
	C[dlugosc - 1].set_R(Ua[dlugosc - 1].get_R());
	//C[dlugosc - 1].print_macierz();
	for (i = dlugosc - 1; i > 0; i--){
		delta_r = Ua[i - 1].get_R() - Ua[i].get_R();
		P[i].mnozenie_liczba(delta_r / 2);
		//P[i].print_macierz();
		pomoc_do_macierz1 = jedostkowa.odejmowanie(P[i]);
		//pomoc_do_macierz1.print_macierz();
		pomoc_do_macierz2 = jedostkowa.dodawanie(P[i]);
		//pomoc_do_macierz2.print_macierz();
		pomoc_do_macierz3 = pomoc_do_macierz2.odwrotnosc();
		//pomoc_do_macierz3.print_macierz();
		pomoc_do_macierz4 = pomoc_do_macierz1.mnozenie(pomoc_do_macierz3);
		//pomoc_do_macierz4.print_macierz();
		C[i - 1] = pomoc_do_macierz4.mnozenie(C[i]);
		C[i - 1].set_R(C[i - 1].get_R() + delta_r);
		//C[i - 1].print_macierz();
		Ud[i] = Ua[i].mnozenie(C[i]);
		//Ud[i].print_macierz();
		//system("pause");
	}
	Ud[0] = Ua[0].mnozenie(C[0]);
	ofstream *dane_do_zapisu = new ofstream[pomoc];
	nazwa_pliku = "Dpot_1.dat";
	for (i = 0; i < ilosc; i++){
		nazwa_pliku.erase(nazwa_pliku.begin() + 5, nazwa_pliku.end());
		nazwa_pliku.append(to_string(i + 1) + ".dat");
		//cout << nazwa_pliku << endl;
		dane_do_zapisu[i].open(nazwa_pliku);
		if (dane_do_zapisu[i].is_open())
		{
			for (int j = 0; j < dlugosc; j++){
				dane_do_zapisu[i] << Ud[j].get_R() << '\t' << Ud[j].get_macierz(i, i)<<endl;
			}
			dane_do_zapisu[i].close();
		}
		else
			cout << "Nieudalo sie zapisac do pliku " << nazwa_pliku << endl;

	}
	l = 0;
	for (i = 0; i < ilosc; i++){
		for (int j = i + 1; j < ilosc; j++){
			nazwa_pliku.erase(nazwa_pliku.begin() + 5, nazwa_pliku.end());
			nazwa_pliku.append(to_string(i + 1) + "_" + to_string(j + 1) + ".dat");
			//cout << nazwa_pliku << endl;
			dane_do_zapisu[ilosc + l].open(nazwa_pliku);
			if (dane_do_zapisu[ilosc + l].is_open())
			{
				for (int k = 0; k < dlugosc; k++){
					dane_do_zapisu[ilosc + l] << Ud[k].get_R() << '\t' << Ud[k].get_macierz(i, j)<<endl;
				}
				dane_do_zapisu[ilosc + l].close();
			}
			else
				cout << "Nieudalo sie zapisac do pliku " << nazwa_pliku << endl;
			l++;
		}
	}
	delete[] C;
	delete[] Ud;
	delete[] Ua;
	delete[] P;
	delete[] dane;
	delete[] dane_do_zapisu;
	system("pause");
	return 0;
}