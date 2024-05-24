#include <iostream>
#include <cmath>
#include <exception>
#include <deque>
#include <string>

template < typename IterTip>
auto SumaBloka(IterTip pocetak, IterTip iza_kraja) -> decltype (*pocetak + *pocetak){   
	
	if( (iza_kraja - pocetak) == 0) throw std::range_error ("Blok je prazan");
	decltype (*pocetak + *pocetak) Suma= *pocetak;
	pocetak++;
	while(pocetak != iza_kraja){
		Suma += *pocetak;
		pocetak++;
	}
	return Suma;
}
int main ()
{

	int br_elemenat;

	std::cout<<"Broj elemenata: ";
	std::cin>>br_elemenat;
	std::deque<double> d(br_elemenat);
	std::cout<<"Unesite elemente: ";
	for(int i=0; i < br_elemenat; i++){
		std::cin>>d.at(i);
	}
	std::cout<<"Suma bloka je: "<<SumaBloka(d.begin(), d.end());

	return 0;
}