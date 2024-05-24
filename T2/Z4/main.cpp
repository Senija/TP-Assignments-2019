//TP 2018/2019: Tutorijal 2, Zadatak 4
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
    double re, im;
    for(int i=0; i<brojElemenata; i++) {
        std::cout<<"R"<<i+1<<" = ";
        std::cin>>re;
        std::cout<<"X"<<i+1<<" = ";
        std::cin>>im;
        z.real(re);
        z.imag(im);
        std::cout<<std::endl;
        impedansa+= 1./z;
    }
    impedansa = 1./impedansa;
    std::cout<<std::endl<<"Paralelna veza ovih elemenata ima R = "<<impedansa.real() <<" i X = "<<impedansa.imag()<<".";
    return 0;
}
