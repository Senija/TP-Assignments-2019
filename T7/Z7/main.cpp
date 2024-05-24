#include <iostream>
#include <set>
#include <iterator>
#include <algorithm>

template<typename Tip>
std::set<Tip> Unija(std::set<Tip> skup1, std::set<Tip> skup2)
{
	std::set<Tip> UnijaSkupova;
	for(auto i=skup1.begin(); i!=skup1.end(); i++) {
		UnijaSkupova.insert(*i);
	}
	for(auto i=skup2.begin(); i!=skup2.end(); i++) {
		UnijaSkupova.insert(*i);
	}
	return UnijaSkupova;
}
template<typename Tip>
std::set<Tip> Presjek(std::set<Tip> skup1, std::set<Tip> skup2)
{
	// std::multiset<Tip> UnijaSkupova;
	// for(auto i=skup1.begin(); i!=skup1.end(); i++) {
	// 	UnijaSkupova.insert(*i);
	// }
	// for(auto i=skup2.begin(); i!=skup2.end(); i++) {
	// 	UnijaSkupova.insert(*i);
	// }
	// std::set<Tip> PresjekSkupova;
	// for(auto i=UnijaSkupova.begin(); i!=UnijaSkupova.end(); i++) {
	// 	if(UnijaSkupova.count(*i)==2) PresjekSkupova.insert(*i);
	// }
	// return PresjekSkupova;
	std::set<Tip> PresjekSkupova;
	for(auto i = skup1.begin(); i != skup1.end(); i++){
		if(std::binary_search(skup2.begin(), skup2.end(), *i)) PresjekSkupova.insert(*i);
	}
	return PresjekSkupova;
}


int main ()
{
	//fali main	
	return 0;
}
