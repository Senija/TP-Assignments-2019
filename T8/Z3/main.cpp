//TP 2018/2019: Tutorijal 8, Zadatak 3
#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <iomanip>
#include <memory>

const int BrojPredmeta = 8;
struct Datum {
    int dan, mjesec, godina;
};
struct Ucenik {
    std::string ime, prezime;
    Datum datum_rodjenja;
    int ocjene[BrojPredmeta];
    double prosjek;
    bool prolaz;
};

void OslobodiMemoriju(Ucenik **p_ucenici, int broj_ucenika)
{
    for(int i = 0; i<broj_ucenika; i++) delete p_ucenici[i];
}

void UnesiDatum(Datum &datum)
{
    char znak;
    std::cin>> datum.dan >> znak >> datum.mjesec >> znak >> datum.godina;
}

void UnesiOcjene(int ocjene [], int broj_predmeta)
{
    for(int i=0; i<broj_predmeta; i++) {
        std::cout<<"  Ocjena iz " << i + 1 << ". predmeta: ";
        std::cin>>ocjene[i];
    }
}

void UnesiJednogUcenika(Ucenik *p_ucenik)
{
    std::cout << "  Ime: ";
    std::cin >> p_ucenik->ime;
    std::cout << "  Prezime: ";
    std::cin >> p_ucenik->prezime;
    std::cout << "  Datum rodjenja (D/M/G): ";
    UnesiDatum(p_ucenik->datum_rodjenja);
    UnesiOcjene(p_ucenik->ocjene, BrojPredmeta);

}

void UnesiUcenike(Ucenik **p_ucenici, int broj_ucenika)
{
    for(int i = 0; i<broj_ucenika; i++) {
        std::cout<<"Unesite podatke za " << i + 1 << ". ucenika:\n";
        p_ucenici[i] = new Ucenik;
        UnesiJednogUcenika(p_ucenici[i]);
    }
}
void ObradiJednogUcenika(Ucenik  *p_ucenik)
{
    double suma_ocjena = 0;
    p_ucenik ->prosjek = 1;
    p_ucenik->prolaz = false;
    for(auto ocjena = p_ucenik->ocjene; ocjena != p_ucenik->ocjene + BrojPredmeta; ocjena++) {
        if(*ocjena == 1) return;
        suma_ocjena += *ocjena;
    }
    p_ucenik->prolaz = true;
    p_ucenik->prosjek = suma_ocjena/ BrojPredmeta;
}

void ObradiUcenike(Ucenik **p_ucenici, int broj_ucenika)
{
    for(auto i = 0; i != broj_ucenika; i++) ObradiJednogUcenika(p_ucenici[i]);
    std::sort(p_ucenici, p_ucenici + broj_ucenika, [](Ucenik *p_u1, Ucenik *p_u2) {
        return p_u1->prosjek > p_u2->prosjek;
    });
}

void IspisiDatum(const Datum &datum)
{
    std::cout<<datum.dan << "/" << datum.mjesec << "/" << datum.godina;
}
void IspisiJednogUcenika(const Ucenik *p_ucenik)
{
    std::cout<<"Ucenik " << p_ucenik->ime << " " << p_ucenik->prezime
             << " rodjen ";
    IspisiDatum(p_ucenik->datum_rodjenja);
    if(p_ucenik->prolaz)
        std::cout << " ima prosjek " << std::setprecision(3) << p_ucenik->prosjek;
    else
        std::cout << " mora ponavljati razred";
    std::cout << std::endl;
}

void IspisiIzvjestaj(Ucenik **p_ucenici, int broj_ucenika)
{
    std::cout<<std::endl;
    for(int i = 0; i != broj_ucenika; i++) {
        IspisiJednogUcenika(p_ucenici[i]);
    }
}

int main ()
{
    int broj_ucenika;
    std::cout<<"Koliko ima ucenika: ";
    std::cin>>broj_ucenika;
    Ucenik **p_ucenici;
    try {
        p_ucenici = new Ucenik *[broj_ucenika] {};
        try {
            UnesiUcenike(p_ucenici, broj_ucenika);
        }
        catch(...){
            OslobodiMemoriju(p_ucenici, broj_ucenika);
            throw;
        }
        ObradiUcenike(p_ucenici, broj_ucenika);
        IspisiIzvjestaj(p_ucenici, broj_ucenika);
        OslobodiMemoriju(p_ucenici, broj_ucenika);
        delete[] p_ucenici;
    } catch(std::bad_alloc) {
        delete[] p_ucenici;
    }

    return 0;
}
