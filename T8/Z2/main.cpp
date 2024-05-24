//TP 2018/2019: Tutorijal 8, Zadatak 2
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
typedef std::shared_ptr<Ucenik> SmartUcenik;

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

void UnesiJednogUcenika(SmartUcenik p_ucenik)
{
    std::cout << "  Ime: ";
    std::cin >> p_ucenik->ime;
    std::cout << "  Prezime: ";
    std::cin >> p_ucenik->prezime;
    std::cout << "  Datum rodjenja (D/M/G): ";
    UnesiDatum(p_ucenik->datum_rodjenja);
    UnesiOcjene(p_ucenik->ocjene, BrojPredmeta);

}

void UnesiUcenike(std::vector<SmartUcenik> &p_ucenici)
{
    for(int i = 0; i<p_ucenici.size(); i++) {
        std::cout<<"Unesite podatke za " << i + 1 << ". ucenika:\n";
        p_ucenici[i] = std::make_shared<Ucenik>();
        UnesiJednogUcenika(p_ucenici[i]);
    }
}
void ObradiJednogUcenika(SmartUcenik p_ucenik)
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

void ObradiUcenike(std::vector<SmartUcenik> &p_ucenici)
{
    for(auto p_ucenik = p_ucenici.begin(); p_ucenik != p_ucenici.end(); p_ucenik++) ObradiJednogUcenika(*p_ucenik);
    std::sort(p_ucenici.begin(), p_ucenici.end(), [](const SmartUcenik p_u1, const SmartUcenik p_u2) {
        return p_u1->prosjek > p_u2->prosjek;
    });
}

void IspisiDatum(const Datum &datum)
{
    std::cout<<datum.dan << "/" << datum.mjesec << "/" << datum.godina;
}
void IspisiJednogUcenika(const SmartUcenik p_ucenik)
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

void IspisiIzvjestaj(const std::vector<SmartUcenik> &p_ucenici){
    std::cout<<std::endl;
    for(auto p_ucenik = p_ucenici.begin(); p_ucenik != p_ucenici.end(); p_ucenik++){
        IspisiJednogUcenika(*p_ucenik);
    }
}

int main ()
{
    int broj_ucenika;
    std::cout<<"Koliko ima ucenika: ";
    std::cin>>broj_ucenika;
    std::vector<SmartUcenik> p_ucenici(broj_ucenika);
    UnesiUcenike(p_ucenici);
    ObradiUcenike(p_ucenici);
    IspisiIzvjestaj(p_ucenici);

    return 0;
}
