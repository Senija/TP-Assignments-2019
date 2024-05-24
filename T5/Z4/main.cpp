#include <iostream>
#include <algorithm>
#include <cmath>
#include <deque>

int main ()
{
	
	int BrElemenata;
	std::cout<<"Unesite broj elemenata: ";
	std::cin>>BrElemenata;
	std::deque<int> Dek(BrElemenata);
	std::cout<<"Unesite elemente: ";
	std::for_each(std::begin(Dek), std::begin(Dek)+BrElemenata, [](int &x) {std::cin>>x;}); //[](int &x) {std::cin>>x;}

	std::cout<<"Najveci element deka je "<<* (std::max_element(std::begin(Dek), std::begin(Dek)+BrElemenata))<<std::endl;
	
	int minumun = * (std::min_element(std::begin(Dek), std::begin(Dek)+BrElemenata));
	std::cout<<"Najmanji element deka se pojavljuje "<<std::count(std::begin(Dek), std::begin(Dek)+ BrElemenata, minumun)<<" puta u deku"<<std::endl;
	
	std::cout<<"U deku ima "<<std::count_if(std::begin(Dek), std::begin(Dek)+ BrElemenata, [](int x) -> bool { if(x>=0) return int(std::sqrt(x)) * int(std::sqrt(x)) == x; else return false;}) <<" brojeva koji su potpuni kvadrati"<<std::endl;
	
	std::cout<<"Prvi element sa najmanjim brojem cifara je "<< *( std::min_element(std::begin(Dek), std::begin(Dek)+ BrElemenata, [] (int broj1, int broj2) {return int(std::log10(std::fabs(broj1))) < int(std::log10(std::fabs(broj2)));}) )<<std::endl;
	std::deque<int> BezTrocifrenih(BrElemenata);
	typename std::deque<int>::iterator iza_kraja = std::remove_copy_if(std::begin(Dek), std::begin(Dek)+ BrElemenata, std::begin(BezTrocifrenih), [] (int broj) {return int(std::log10(std::fabs(broj))) +1 == 3;});
	std::cout<<"Elementi koji nisu trocifreni su: ";
	std::for_each(std::begin(BezTrocifrenih), iza_kraja, [](int x){std::cout<<x<<" ";});
	return 0;
}