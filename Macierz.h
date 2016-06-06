#pragma once
#include<iostream>
using namespace std;

class Macierz{
	double R;
	double **macierz;
	int rozmiar;
public:
	Macierz();
	Macierz(int);
	~Macierz();
	void set_macierz(int, int, double);
	double get_macierz(int, int);
	void set_R(double);
	double get_R();
	bool check_R(double);
	Macierz dodawanie(const Macierz);
	Macierz mnozenie(const Macierz);
	Macierz odwrotnosc();
	void print_macierz();
	void mnozenie_liczba(double);
	void tworzenie(int);
	Macierz odejmowanie(const Macierz);
	Macierz zamiana_na_P();
};

Macierz::Macierz(){
	R = 0;
	rozmiar = 0;
}

Macierz::Macierz(int wielkosc){
	macierz = new double *[wielkosc];
	for (int i = 0; i < wielkosc; i++){
		macierz[i] = new double[wielkosc];
	}
	for (int i = 0; i < wielkosc; i++){
		for (int j = 0; j < wielkosc; j++){
			if (i != j)
				macierz[i][j] = 0.0;
			else
				macierz[i][j] = 1.0;
		}
	}
	R = 0.0;
	rozmiar = wielkosc;
}

Macierz::~Macierz(){
	/*for (int i = 0; i <rozmiar; i++){
		delete[] macierz[i];
	}
	delete[] macierz;*/
}

void Macierz::set_macierz(int wiersz, int kolumna, double wartosc){
	macierz[wiersz][kolumna] = wartosc;
}

double Macierz::get_macierz(int wiersz, int kolumna){
	return macierz[wiersz][kolumna];
}

void Macierz::set_R(double wartosc){
	R = wartosc;
}

double Macierz::get_R(){
	return R;
}

bool Macierz::check_R(double R2){
	if (R2 == R)
		return true;
	else
		return false;
}

Macierz Macierz::dodawanie(const Macierz A){
	Macierz B(rozmiar);
	for (int i = 0; i < rozmiar; i++){
		for (int j = 0; j < rozmiar; j++){
			B.macierz[i][j] = this->macierz[i][j] + A.macierz[i][j];
		}
	}
	B.R = A.R;
	return B;
}

Macierz Macierz::mnozenie(const Macierz A){
	Macierz B(rozmiar);
	for (int i = 0; i < rozmiar; i++){
		for (int j = 0; j < rozmiar; j++){
			B.macierz[i][j] = 0;
			for (int k = 0; k < rozmiar; k++){
				B.macierz[i][j] += this->macierz[i][k] * A.macierz[k][j];				
			}
		}		
	}
	B.R = A.R;
	return B;
}

void Macierz::print_macierz(){
	for (int i = 0; i < rozmiar; i++){
		for (int j = 0; j < rozmiar; j++){
			cout.precision(9);
			cout << this->macierz[i][j] << '\t';
		}
		cout << endl;
	}
	cout << endl;
}

Macierz Macierz::odwrotnosc(){
	Macierz A(rozmiar);
	double pomoc;	
	for (int i = 0; i < rozmiar; i++){
		pomoc = this->macierz[i][i];
		for (int j = 0; j < rozmiar; j++){
			A.macierz[i][j] /= pomoc;
			this->macierz[i][j] /= pomoc;			
		}		
		for (int k = i + 1; k < rozmiar; k++){
			if (this->macierz[k][i] != 0){
				pomoc = this->macierz[k][i];
				for (int l = 0; l < rozmiar; l++){
					this->macierz[k][l] -= this->macierz[i][l] * pomoc;
					A.macierz[k][l] -= A.macierz[i][l] * pomoc;					
				}
			}
		}	
	}
	for (int i = 1; i < rozmiar; i++){
		for (int j = i - 1; j >= 0; j--){
			if (this->macierz[j][i] != 0){
				pomoc = this->macierz[j][i];
				for (int k = 0; k < rozmiar; k++){
					this->macierz[j][k] -= this->macierz[i][k] * pomoc;
					A.macierz[j][k] -= A.macierz[i][k] * pomoc;
				}
			}
		}
	}
	A.R = this->R;
	return A;
}

void Macierz::mnozenie_liczba(double wartosc){
	for (int i = 0; i < rozmiar; i++){
		for (int j = 0; j < rozmiar; j++){
			this->macierz[i][j] *= wartosc;
		}
	}
}

void Macierz::tworzenie(int wielkosc){
	macierz = new double *[wielkosc];
	for (int i = 0; i < wielkosc; i++){
		macierz[i] = new double[wielkosc];
	}
	for (int i = 0; i < wielkosc; i++){
		for (int j = 0; j < wielkosc; j++){
			if (i != j)
				macierz[i][j] = 0.0;
			else
				macierz[i][j] = 1.0;
		}
	}
	R = 0.0;
	rozmiar = wielkosc;
}

Macierz Macierz::odejmowanie(const Macierz A){
	Macierz B(rozmiar);
	for (int i = 0; i < rozmiar; i++){
		for (int j = 0; j < rozmiar; j++){
			B.macierz[i][j] = this->macierz[i][j] - A.macierz[i][j];
		}
	}
	B.R = A.R;
	return B;
}

Macierz Macierz::zamiana_na_P(){
	Macierz A(rozmiar);	
	for (int i = 0; i < rozmiar; i++){
		for (int j = 0; j < rozmiar; j++){
			if (i == j)
				A.macierz[i][j] = 0;
			else if (j<i)
				A.macierz[i][j] = this->macierz[i][j]*(-1);
			else
				A.macierz[i][j] = this->macierz[i][j];
		}		
	}
	A.R = this->R;
	return A;
}