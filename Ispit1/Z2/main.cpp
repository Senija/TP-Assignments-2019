//TP 2018/2019: Ispit 1, Zadatak 2
#include <iostream>
#include <vector>
#include <deque>
#include <cmath>
#include <iomanip>
template<typename CjelobrojniTip>
double Elementi(CjelobrojniTip indeks)
{

}
template<typename CjelobrojniTip>
std::deque<double> IzdvojiElemente(std::vector<CjelobrojniTip> V)
{
    for(int i = 0; i!=V.size(); i++) {
        if(i%2 != 0 && V.at(i) < 0) throw std::logic_error ("Element vektora negativan!");
    }
    std::deque<double> Vrati(V.size());
    //std::transform(V.begin(), V.end(), Vrati.begin(), [V](CjelobrojniTip element){})
    for(int i =0; i!= V.size(); i++) {
        if(i  % 2 == 0) Vrati.at(i) = std::pow(V.at(i), 2);
        if( i % 2 != 0) Vrati.at(i) = std::sqrt(V.at(i));
    }
    return Vrati;
}

bool JeLiCjelobrojan(double broj){
    return int(broj)==broj;
}
int main ()
{
    //std::vector<int> Vektor;
    try {
        int br_elemenata;
        std::cout<<"Unesite broj elemenata vektora: ";
        std::cin>>br_elemenata;
        std::vector<int> Vektor(br_elemenata);
        std::cout<<"Unesite elemente vektora: ";
        for(int i=0; i<br_elemenata; i++) {
            std::cin>>Vektor.at(i);
        }

        auto dek = IzdvojiElemente(Vektor);
        std::cout<<"Rezultujuci dek: ";
        for(int i=0; i<br_elemenata; i++) {
            if(!JeLiCjelobrojan(dek.at(i))) std::cout<<std::fixed<<std::setprecision(2)<<dek.at(i)<<" "; //kako saznati je li cjelobrojan????
            else std::cout<<std::fixed<<std::setprecision(0)<<dek.at(i)<<" ";
        }
    } catch(std::logic_error izuzetak) {
        std::cout<<"Problem: "<<izuzetak.what()<<std::endl;
    }
    return 0;
}
