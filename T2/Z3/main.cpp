//TP 2018/2019: Tutorijal 2, Zadatak 3
#include <iostream>
#include <complex>
int main ()
{
    int brojElemenata;
    std::cout<<"Unesite broj elemenata: ";
    std::cin>>brojElemenata;
    std::cout<<std::endl;
    std::complex<double> z;
    std::complex<double> impedansa(0);
    for(int i=0; i<brojElemenata; i++){
        std::cout<<"Z_"<<i+1<<" = ";
        std::cin>>z;
        impedansa+= 1./z;
    }
    std::cout<<std::endl<<"Paralelna veza ovih elemenata ima impedansu Z_ = "<< 1./impedansa<<".";
	return 0;
}