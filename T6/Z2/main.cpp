#include <iostream>
#include <type_traits>
#include <new>
#include <vector>
#include <algorithm>
#include <utility>
#include <forward_list>

template <typename IterTip>
auto KreirajIzvrnutiNiz(IterTip pocetak, IterTip iza_kraja) -> typename std::remove_reference<decltype(*pocetak)>::type* {
	
	auto pomocna=pocetak;
	int brojac=0;
	for(auto i=pomocna; i!=iza_kraja; i++){
		brojac++;
	}
	
	typename std::remove_reference<decltype(*pocetak)>::type *pok=nullptr;
	pok= new typename std::remove_reference<decltype(*pocetak)>::type [brojac];
	try{
		
		for(int i=0; i<brojac; i++){
			pok[brojac-1-i] = *pocetak++;
		}
		
	}
	catch(std::bad_alloc){
		delete pok;
		throw;
	}
	return pok;
}
int main ()
{
	

	try{
		int br_elemenata;
		std::cout<<"Koliko zelite elemenata: ";
		std::cin>>br_elemenata;
		std::vector<double> Vektor(br_elemenata);
		std::cout<<"Unesite elemente: ";
		for(int i=0; i<br_elemenata; i++){
			std::cin>>Vektor.at(i);
		}
		double *pok=&Vektor[0];
		auto PokNaDinamicki = KreirajIzvrnutiNiz(pok, pok + br_elemenata);
		
		std::cout<<"Kreirani niz: ";
		auto pokPrintanje = PokNaDinamicki;
		for(int i=0; i<br_elemenata; i++){
			std::cout<< *pokPrintanje++<<" ";
		}
		delete[] PokNaDinamicki;
		
	}
	catch(std::bad_alloc){
		std::cout<<"Nedovoljno memorije!"<<std::endl;
	}
	return 0;
}