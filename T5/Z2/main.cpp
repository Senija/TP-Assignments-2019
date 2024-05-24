#include <iostream>
#include <cmath>
#include <algorithm>
#include <vector>
#include <algorithm>
template<typename RazmijeljiviTip1, typename RazmijeljiviTip2>
void Razmijeni(RazmijeljiviTip1 &x, RazmijeljiviTip2 &y){
	RazmijeljiviTip1 tmp=x;
	x=y;
	y=tmp;
}
template<typename IterPok1, typename IterPok2>
IterPok2 RazmijeniBlokove(IterPok1 pocetak, IterPok1 iza_kraj, IterPok2 destinacija){
	//std::remove_reference<decltype(pocetak)>::type Kolekcija; 
	for(auto i=pocetak; i!=iza_kraj; i++){
		Razmijeni(*i, *destinacija);
		destinacija++;
	}
	return destinacija;
}

int main ()
{
	std::string s="Ja idem na ETF";
	int niz[14] = {1,2,3,4,5,6,7,8,9,10,11,12,13,14};
	RazmijeniBlokove(std::begin(s), std::end(s), niz);
	for(int i=0; i<14; i++){
		std::cout<<char(niz[i]);
	}
	
	
	
	return 0;
}