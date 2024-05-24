//TP 2018/2019: Tutorijal 8, Zadatak 6
#include <iostream>

template<typename TipElementa>
struct Cvor {
    TipElementa element;
    Cvor *veza;
};
template <typename TipElemenata>
Cvor<TipElemenata> *KreirajPovezanuListu(TipElemenata zavrsni)
{
    Cvor<TipElemenata> *pocetak = nullptr, *prethodni;
    for(;;) {
        TipElemenata clan;
        std::cin>>clan;
        if(clan == zavrsni) break;
        Cvor<TipElemenata> *novi = new Cvor<TipElemenata>{clan, nullptr};
        if(!pocetak) pocetak = novi;
        else prethodni->veza = novi;
        prethodni = novi;
    }
    return pocetak;
}
template <typename TipElemenata>
int BrojElemenata(Cvor<TipElemenata> *pocetak)
{
    int brojac = 0;
    for(auto p = pocetak; p != nullptr; p = p->veza) {
        brojac++;
    }
    return brojac;
}
template <typename TipElemenata>
TipElemenata SumaElemenata(Cvor<TipElemenata> *pocetak)
{
    TipElemenata suma = TipElemenata();
    for(auto p = pocetak; p != nullptr; p = p->veza) {
        suma += p->element;
        
    }
    return suma;
}
template <typename TipElemenata>
int BrojVecihOd(Cvor<TipElemenata> *pocetak, TipElemenata prag)
{
    int brojac = 0;
    for(auto p = pocetak; p != nullptr; p = p->veza) {
        if(p->element > prag) brojac++;
    }
    return brojac;
}

template <typename TipElemenata>
void UnistiListu(Cvor<TipElemenata> *pocetak)
{
    for(auto p = pocetak; p != nullptr;){
        auto pomocna = p->veza;
        delete p;
        p = pomocna;
    }
}

int main ()
{
    std::cout<<"Unesite slijed brojeva (0 za kraj): ";
    auto lista = KreirajPovezanuListu(0.);
    double aritmeticka_sredina = SumaElemenata(lista)/BrojElemenata(lista);
    auto brojac = BrojVecihOd(lista, aritmeticka_sredina);
    std::cout<<"U slijedu ima "<<brojac<<" brojeva vecih od njihove aritmeticke sredine";
    UnistiListu(lista);
    return 0;
}
