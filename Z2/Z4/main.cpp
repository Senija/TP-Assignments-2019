//TP 2018/2019: Zadaća 2, Zadatak 4
#include <iostream>
#include <string>
#include <algorithm>

std::string PretvoriUvelika(std::string recenica)
{
    for(int i=0; i<recenica.length(); i++) {
        if(recenica.at(i) >= 'a' && recenica.at(i)<= 'z') recenica.at(i) = std::toupper(recenica.at(i));
    }
    return recenica;
}

bool Veci(std::string recenica1, std::string recenica2)
{
    if(recenica1.length() != recenica2.length()) return recenica1.length() < recenica2.length();
    return PretvoriUvelika(recenica1) < PretvoriUvelika(recenica2);
}
void SortirajRecenice(std::string *pocetak, std::string *iza_kraja)
{
    if(iza_kraja < pocetak) throw std::domain_error ("Nije moguce sortiranje");
    std::sort(pocetak, iza_kraja, Veci);
}

int main ()
{
    int br_recenica;
    std::cout<<"Unesite broj recenica: ";
    std::cin>>br_recenica;
    std::cin.ignore(10000, '\n');
    std::string *PokNaString = nullptr;
    try {
        PokNaString =  new std::string[br_recenica];
        std::cout<<"Unesite recenice:"<<std::endl;
        for(int i=0; i<br_recenica; i++) {
            std::getline(std::cin, PokNaString[i]);
        }
        SortirajRecenice( PokNaString, PokNaString+br_recenica);
        std::cout<<"Recenice nakon sortiranja:"<<std::endl;
        for(int i=0; i<br_recenica; i++) {
            std::cout<<PokNaString[i]<<std::endl;
        }
        std::string TrazenaRecenica;
        std::cout<<std::endl<<"Unesite recenicu za pretragu: ";

        std::getline(std::cin, TrazenaRecenica);
        std::string *PokNaTrazenu = nullptr;
        //PokNaTrazenu = std::lower_bound(PokNaString, PokNaString+br_recenica, TrazenaRecenica, Veci);
        if(std::binary_search(PokNaString, PokNaString+br_recenica, TrazenaRecenica, Veci)) {
            PokNaTrazenu = std::lower_bound(PokNaString, PokNaString+br_recenica, TrazenaRecenica, Veci);
            std::cout<<"Recenica se nalazi na poziciji: "<<PokNaTrazenu - PokNaString;
        }
        //if(*PokNaTrazenu == TrazenaRecenica) std::cout<<"Recenica se nalazi na poziciji: "<<PokNaTrazenu - PokNaString;
        else std::cout<<"Trazena recenica se ne nalazi u nizu!";
        delete[] PokNaString;
    } catch(std::bad_alloc) {
        delete[] PokNaString;
    } catch(std::domain_error izuzetak) {
        delete[] PokNaString;
        std::cout<<"Izuzetak: "<<izuzetak.what();
    }
    return 0;
}
