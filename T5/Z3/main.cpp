#include <iostream>
#include <algorithm>
#include <cmath>


void Unos(int &x){
 	std::cin>>x;
}

bool PotpuniKvadrat(int x){
	if(x>=0){
		return int(std::sqrt(x)) * int(std::sqrt(x)) == x;
	} 
	else return false;
}

bool NajmanjiBrojCifara(int broj1, int broj2){
	return int(std::log10(std::fabs(broj1))) < int(std::log10(std::fabs(broj2)));
	
}

bool Trocifren(int broj){
	return int(std::log10(std::fabs(broj))) +1 == 3;
}

void Ispisi(int x){
	std::cout<<x<<" ";
}


int main ()
{
	
	int BrElemenata;
	std::cout<<"Unesite broj elemenata (max. 1000): ";
	std::cin>>BrElemenata;
	int Niz[1000];
	std::cout<<"Unesite elemente: ";
	std::for_each(std::begin(Niz), std::begin(Niz)+BrElemenata, Unos); //[](int &x) {std::cin>>x;}
	// for(int i=0; i<BrElemenata; i++){
	// 	std::cout<<Niz[i]<<", ";
	// }
	std::cout<<"Najveci element niza je "<<* (std::max_element(std::begin(Niz), std::begin(Niz)+BrElemenata))<<std::endl;
	int minumun = * (std::min_element(std::begin(Niz), std::begin(Niz)+BrElemenata));
	std::cout<<"Najmanji element niza se pojavljuje "<<std::count(std::begin(Niz), std::begin(Niz)+ BrElemenata, minumun)<<" puta u nizu"<<std::endl;
	std::cout<<"U nizu ima "<<std::count_if(std::begin(Niz), std::begin(Niz)+ BrElemenata, PotpuniKvadrat) <<" brojeva koji su potpuni kvadrati"<<std::endl;
	std::cout<<"Prvi element sa najmanjim brojem cifara je "<< *( std::min_element(std::begin(Niz), std::begin(Niz)+ BrElemenata, NajmanjiBrojCifara) )<<std::endl;
	int BezTrocifrenih[100];
	int *iza_kraja = std::remove_copy_if(std::begin(Niz), std::begin(Niz)+ BrElemenata, std::begin(BezTrocifrenih), Trocifren);
	std::cout<<"Elementi koji nisu trocifreni su: ";
	std::for_each(std::begin(BezTrocifrenih), iza_kraja, Ispisi);
	return 0;
}