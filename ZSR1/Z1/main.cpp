//TP 2018/2019: ZSR 1, Zadatak 1 Prijmer ispita I 1. zadatak
#include <iostream>
#include <list>
#include <complex>

struct Kompleksni{
    double re, im;
    Kompleksni*sljedeci;
    
};

Kompleksni* KreirajListu(const std::list<std::complex<double>> &Lista){
    Kompleksni *pocetak = nullptr, *prethodni;
    for(auto i = Lista.begin(); i != Lista.end(); i++){
        Kompleksni *novi = new Kompleksni{i->real(), i->imag(), nullptr};
        if(!pocetak) pocetak = novi;
        else prethodni->sljedeci = novi;
        prethodni = novi;
    }
    return pocetak;
}
int main ()
{
    std::list<std::complex<double>> lista{{2,5}, {3,4}, {4,8}};
    auto pocetak = KreirajListu(lista);
    for(auto i = pocetak; i != nullptr; i = i->sljedeci){
        std::cout<<i->re<<","<<i->im<<std::endl;
    }
    for(auto i = pocetak; i != nullptr; i = i->sljedeci){
        delete i;
        i = nullptr;
    }
    
	return 0;
}