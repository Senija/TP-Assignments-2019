#include <iostream>
#include <algorithm>
#include <vector>
#include <cmath>

int SumaCifara(int broj, int &suma){
	
	suma+=(std::abs (broj))%10;
	if(broj != 0) SumaCifara(broj/10, suma);
	else return suma;
}

bool ManjiPoSumiCifara(int broj1, int broj2){
	int suma1 = 0, suma2 = 0; 
	if( SumaCifara(broj1, suma1) == SumaCifara(broj2, suma2)) return broj1<broj2;
	//std::cout<<SumaCifara(broj1, suma1)<<" "<<SumaCifara(broj2, suma2)<<" ";
	return SumaCifara(broj1, suma1)< SumaCifara(broj2, suma2);
}



void Unos(int &x){
	std::cin>>x;
}

int main ()
{
	int brElemenata;
	std::cout<<"Unesite broj elemenata: ";
	std::cin>>brElemenata;
	std::vector<int> Vektor(brElemenata);
	std::cout<<"Unesite elemente: ";
	std::for_each(std::begin(Vektor), std::begin(Vektor) + brElemenata, Unos);
	std::sort(std::begin(Vektor), std::end(Vektor), ManjiPoSumiCifara);
	std::cout<<"Niz sortiran po sumi cifara glasi: ";
	for(int element : Vektor){
		std::cout<<element<<" ";
	}
	int BrojKojiTrazimo;
	std::cout<<std::endl<<"Unesite broj koji trazite: ";
	std::cin>>BrojKojiTrazimo;
	typename std::vector<int> ::iterator it = std::lower_bound(std::begin(Vektor), std::end(Vektor), BrojKojiTrazimo, ManjiPoSumiCifara);
	if(*it == BrojKojiTrazimo) std::cout<<"Trazeni broj nalazi se na poziciji "<<it - std::begin(Vektor) ;
	else std::cout<<"Trazeni broj ne nalazi se u nizu!";
	return 0;
}