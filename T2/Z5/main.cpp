//TP 2018/2019: Tutorijal 2, Zadatak 5
#include <iostream>
#include <cmath>
#include <complex>
int main ()
{
    const double PI=4*atan(1);
    int brojElemenata;
    std::cout<<"Unesi broj elemenata: ";
    std::cin>>brojElemenata;
    std::cout<<std::endl;
    double z, fi;
    std::complex<double> impedansa(0);
    std::complex<double> polarni(0);
    for(int i=0; i<brojElemenata; i++) {
        std::cout<<"Z"<<i+1<<" = ";
        std::cin>>z;
        std::cout<<"fi"<<i+1<<" = ";
        std::cin>>fi;
        polarni=std::polar(z, fi*(PI/180));
        impedansa+=1./polarni;
        std::cout<<std::endl;
    }
    impedansa=1./impedansa;
    std::cout<<"Paralelna veza ovih elemenata ima Z = "<< std::abs(impedansa)<<" i fi = "<< std::arg(impedansa)*180./PI<<".";
    return 0;
}
