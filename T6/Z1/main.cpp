#include <iostream>
#include <cmath>
#include <exception>
#include <limits>
template <typename TipElementa>
TipElementa *GenerirajStepeneDvojke(int BrojElemenata)
{

	if(BrojElemenata<=0) throw std::domain_error ("Broj elemenata mora biti pozitivan");
	if(std::numeric_limits<TipElementa>::max() < powl(2, BrojElemenata-1))
		throw std::overflow_error("Prekoracen dozvoljeni opseg");
		
	TipElementa *pok=nullptr;
	try {
		pok = new TipElementa[BrojElemenata];
		pok[0] = 1;
		for(int i=1; i<BrojElemenata; i++) {
			pok[i] = pok[i-1] * 2;
			if(pok[i]< pok[i-1]) {
				delete[] pok; //ovdje bilo curenje
				throw std::overflow_error ("Prekoracen dozvoljeni opseg");
			}
		}


	} catch(std:: bad_alloc) {
		delete[] pok;
		throw std::runtime_error ("Alokacijanije uspjela");

	}

	return pok;

}
int main ()
{
	int n;
	std::cout<<"Koliko zelite elemenata: ";
	std::cin>>n;
	try {
		auto pok=GenerirajStepeneDvojke<int>(n);
		for(int i=0; i<n; i++) {
			std::cout<<std::fixed<<pok[i]<<" ";
		}
		delete[] pok;
	} catch(std::domain_error izuzetak) {		
		std::cout<<"Izuzetak: "<<izuzetak.what()<<std::endl;
	} catch(std::runtime_error izuzetak) {		
		std::cout<<"Izuzetak: "<<izuzetak.what()<<std::endl;
	} catch(std::overflow_error izuzetak) {		
		std::cout<<"Izuzetak: "<<izuzetak.what()<<std::endl;
	}

	return 0;
}
		
