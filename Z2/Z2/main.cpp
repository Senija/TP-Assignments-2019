//TP 2018/2019: Zadaća 2, Zadatak 2
#include <iostream>
#include <algorithm>
#include <cmath>
#include <vector>
#include <iterator>
#include <cstdlib>
#include <set>

typedef unsigned long long int DugiInt;
template<typename CjelobrojniTip>
bool SlobodanOdKvadrata(CjelobrojniTip broj)
{


    if(broj == 1 || broj == 0) return false;
    for(DugiInt i=2; i<=(llabs(broj)/i); i++) {
        if(broj % (i*i) == 0) return true;
    }
    return false;
}
template<typename CjelobrojniTip>
bool ProstBroj(CjelobrojniTip broj)
{
    // if(broj < 0) {
    //     std::string pomocna = std::to_string(broj);
    //     pomocna.erase(pomocna.begin());
    //     broj = std::stoll(pomocna);
    // }
    DugiInt pomocna = llabs(broj);
    if(broj == 1 || broj == 0) return false;
    if (broj == 2) return true;
    //CjelobrojniTip pomocna = sqrtl(std::abs(broj));
    for(DugiInt i=2; i <=pomocna/i; i++) {
        if(broj % i == 0) return false;
    }
    return true;
}

template<typename CjelobrojniTip>
CjelobrojniTip SumaProstihFaktora(CjelobrojniTip broj)
{

    CjelobrojniTip Suma = 0;
    if(ProstBroj(broj)) return broj;
    // auto pomocna2 = broj/2;
    /*unsigned long long int*/
    DugiInt pomocna = llabs(broj);
    for( DugiInt i = 2; i<=pomocna; i++) { //overflow protect
        if(pomocna%i == 0 && ProstBroj(i)) {
            pomocna = pomocna/i; ///suma prostih
            Suma+=i;
            while(pomocna%i ==0)
                pomocna = pomocna/i;
        }
    }
    return Suma;

}

//bool IstiPoSumi()

template <typename IterTipCjlb>
auto Izdvajanje(IterTipCjlb It1, IterTipCjlb &It2, int &BrojSlobodnihOdKvadrata) ->typename std::remove_reference<decltype(*It1)>::type*
{

    int BrojacSlobodnih = 0;
    for(auto i = It1; i!= It2; i++) {
        if(!SlobodanOdKvadrata(*i) && std::find(It1, It2, *i) == i) BrojacSlobodnih++;
    }
    BrojSlobodnihOdKvadrata = BrojacSlobodnih;

    typename std::remove_reference<decltype(*It1)>::type *PokNaDinamicki = nullptr;
    try {
        PokNaDinamicki = new typename std::remove_reference<decltype(*It1)>::type[BrojacSlobodnih] {};
        typename std::remove_reference<decltype(*It1)>::type *tmpZaUnos = nullptr;
        tmpZaUnos = PokNaDinamicki;
        // int brojac = 0;
        for(auto i = It1; i != It2; i++) {
            if(!SlobodanOdKvadrata(*i) ) {
                if(std::count(PokNaDinamicki, PokNaDinamicki + BrojacSlobodnih, *i) ==0) {
                    // PokNaDinamicki[brojac] = *i;
                    // brojac++;
                    *tmpZaUnos = *i;
                    tmpZaUnos++;
                }
            }
        }

        for(auto i = It1; i!= It2; i++) {
            double pomocna = -1;
            bool ista = false;
            for(auto j=It1; j!= It2; j++) {
                if(i != j && *i != *j && SumaProstihFaktora(*i) == SumaProstihFaktora(*j)) {
                    pomocna = *j;
                    It2 = std::remove(It1, It2, pomocna);
                    j --;
                }
                if((*i ==*j || *i == -1* *j) && i != j) {
                    ista = true;

                }

            }
            if(pomocna != -1 || ista) {
                auto pomocna2 = *i;
                It2 = std::remove(It1, It2, pomocna2);
                It2 = std::remove(It1, It2, -1*pomocna2);
                i--;
            }
        }

        // std::vector<int> pomocni;
        // for(auto i=It1; i!=It2; i++) {
        //     pomocni.push_back(SumaProstihFaktora(*i));

        // }
        // for(int i=0; i<12; i++) {
        //     std::cout<<pomocni[i]<<" ";
        // }
        // std::cout<<"\n";


        tmpZaUnos = nullptr;


    } catch(std::bad_alloc) {
        delete[] PokNaDinamicki;
        throw std::range_error ("Nedovoljno memorije!");
    }

    return PokNaDinamicki;

}
template<typename IterTipCjlb>
void Ispisi(IterTipCjlb it1, IterTipCjlb it2)
{
    for(auto i= it1; i!= it2; i++) {
        if(i!= it2 - 1) std::cout<<*i<<", ";
        else std::cout<<*i;
    }
}
int ProizvodCifara( int broj)
{
    int Proizvod = 1;
    while(broj !=0) {
        int cifra = broj % 10;
        Proizvod *= cifra;
        broj = broj /10;
    }
    return Proizvod;
}




int main ()
{
    // std::cout<<ProstBroj(6779);
    // std::cout<<"\n"<<SumaProstihFaktora(49);
    try {
        std::vector<int> vektor;//= {5, 10, 15, 20, 25, 30, -30, -25, -20, -15, -10, -5};
        int BrojacSlobodnih = 0;
        int *Pok = nullptr;
        std::cout<<"Unesite brojeve: ";
        for(;;) {
            int broj;
            std::cin>>broj;
            if(broj == -1) break;
            vektor.push_back(broj);
        }
        //spisi(vektor.begin(), vektor.end());
        std::vector<int>::iterator iza_kraja= std::end(vektor);
        Pok = Izdvajanje(std::begin(vektor), iza_kraja, BrojacSlobodnih);
        int *kopija = Pok;
        std::cout<<"Izdvojeni brojevi: ";
        for(int i=0; i<BrojacSlobodnih; i++) {
            if( i!= BrojacSlobodnih-1) std::cout<<*kopija++<<", ";
            else std::cout<<*kopija;
        }
        std::cout<<std::endl;
        std::cout<<"Modificirani kontejner (prije sortiranja): ";
        Ispisi(vektor.begin(), iza_kraja);
        std::cout<<std::endl<<"Modificirani kontejner (nakon sortiranja): ";
        std::sort(vektor.begin(), iza_kraja, [](int broj1, int broj2) {
            if(ProizvodCifara(broj1) != ProizvodCifara(broj2)) return ProizvodCifara(broj1) < ProizvodCifara(broj2);
            else return broj1 >broj2;
        });
        Ispisi(vektor.begin(), iza_kraja);

        delete[] Pok;
    } catch (std::range_error izuzetak) {
        std::cout << "Nedovoljno memorije" << std::endl;
    }
    return 0;
}
