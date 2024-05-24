#include <iostream>
#include <list>
#include <set>
#include <algorithm>
#include <iterator>

template <typename UporedivaLista>

void SortirajListu(UporedivaLista &lista){
	
	std::multiset<typename std::remove_reference<decltype(*lista.begin())>::type> SortiraniSkup;
	std::copy(lista.begin(), lista.end(), std::inserter(SortiraniSkup, SortiraniSkup.begin()));
	UporedivaLista ListaSortirana;
	std::copy(SortiraniSkup.begin(), SortiraniSkup.end(),  lista.begin());
}

int main ()
{
	int br_elemenata;
	std::cout<<"Koliko ima elemenata: ";
	std::cin>>br_elemenata;
	std::list<int> lista;
	std::cout<<"Unesite elemente: ";
	for(int i=0; i<br_elemenata; i++){
		int element;
		std::cin>>element;
		lista.push_back(element);
	}


	SortirajListu (lista);
	std::list<int>::iterator it(lista.begin());
	std::cout<<"Sortirana lista: ";
	for(int i=0; i<br_elemenata; i++){
		std::cout<<*it++<<" ";
	}
	return 0;
}