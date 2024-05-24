//TP 2018/2019: Zadaća 3, Zadatak 1
#include <iostream>
#include <functional>
#include <cmath>
#include <vector>
#include <utility>
#include <exception>
#include <algorithm>

typedef std::vector<std::pair<double, double>> VektorPar;

bool JesuLiJednaki(double x, double y, double Eps = 1e-10)
{
    return std::fabs(x-y) <= Eps*(std::fabs(x) + std::fabs(y));
}

std::function <double (double)> LagrangeovaInterpolacija(VektorPar cvorovi)
{
    if(cvorovi.size() == 0) return [] (double x) {return 0;};
    for(int i = 0; i < cvorovi.size() ; i++) {
        for(int j = 0; j < cvorovi.size(); j++) {
            if(i == j) continue;
            if(JesuLiJednaki(cvorovi.at(i).first, cvorovi.at(j).first)) throw std::domain_error ("Neispravni cvorovi");
        }
    }
    //std::function <double (double)> RezInterpolacije =
    return [cvorovi] (double kooX) {
        double suma = 0;
        for(int i = 0; i < cvorovi.size(); i++) {
            double proizvod = 1;
            for(int j = 0; j < cvorovi.size(); j++) {
                if(i == j) continue;
                proizvod *= (kooX - cvorovi.at(j).first) / (cvorovi.at(i).first - cvorovi.at(j).first);
            }
            proizvod *= cvorovi.at(i).second;
            suma += proizvod;

        }
        return suma;
    };
    //return RezInterpolacije;
}//ako poc i kraj isto posalje ili korak 0
std::function<double (double)> LagrangeovaInterpolacija(std::function<double (double)> funk, double pocetak, double kraj, double korak)
{
    if(pocetak > kraj || korak <= 0) throw std::domain_error ("Nekorektni parametri");
    VektorPar cvorovi;
    for(auto x= pocetak; x <= kraj; x = x + korak) {
        double y = funk(x);
        cvorovi.push_back({x, y});
    }
    return LagrangeovaInterpolacija(cvorovi);
}

double f(double x)
{
    return x*x + sin(x) + log(x+1);
}

int main ()
{
    // VektorPar v = {{1,3}, {2,5}, {4,4}, {5,2}, {7,1}};
    // std::cout<<LagrangeovaInterpolacija(v)(2.5);
    //const NizFunk[2] = {LagrangeovaInterpolacija()}

    try {
        int broj;
        std::cout<<"Odaberite opciju (1 - unos cvorova, 2 - aproksimacija): ";
        std::cin>>broj;
        if(broj == 1) {
            int br_cvorova;
            std::cout<<"Unesite broj cvorova: ";
            std::cin>>br_cvorova;
            if(br_cvorova <= 0) {
                std::cout<<"Broj cvorova mora biti pozitivan broj!";
                return 0;
            }
            double min, max;
            VektorPar v(br_cvorova);
            std::cout<<"Unesite cvorove kao parove x y: ";
            for(int i = 0; i<br_cvorova; i++) {
                std::cin>>v.at(i).first>>v.at(i).second;
                if(i == 0) {
                    min = v.at(i).first;
                    max = min;
                }
                else{
                    if(v.at(i).first < min) min = v.at(i).first;
                    if(v.at(i).first > max) max = v.at(i).first;
                }
            }
            for(;;) {
                auto g = LagrangeovaInterpolacija(v);
                double argument;
                std::cout<<"Unesite argument (ili \"kraj\" za kraj): ";
                std::cin>>argument;
                if(!(std::cin)) break;
                if(argument < min || argument > max) std::cout<<"f("<< argument <<") = " << g(argument)<<" [ekstrapolacija]"<<std::endl;
                else std::cout<<"f("<< argument <<") = " << LagrangeovaInterpolacija(v)(argument)<<std::endl;
            }
        } else if(broj == 2) {
            double poc, kraj, korak;
            std::cout<<"Unesite krajeve intervala i korak: ";
            std::cin>>poc>>kraj>>korak;
            auto g = LagrangeovaInterpolacija(f, poc, kraj, korak);
            while(1) {
                double argument;
                std::cout<<"Unesite argument (ili \"kraj\" za kraj): ";
                std::cin>>argument;
                if(!(std::cin)) break;
                if(argument > kraj || argument < poc) std::cout<<"f(" <<argument<<") = "<<f(argument)<<" P("<<argument<< ") = "<<g(argument)<<" [ekstrapolacija]"<<std::endl;
                else std::cout<<"f(" <<argument<<") = "<<f(argument)<<" P("<<argument<< ") = "<<g(argument)<<std::endl;
            }
        } else std::cout<<"Nepoznat slucaj!";

    } catch(std::domain_error izuzetak) {
        std::cout<<"IZUZETAK: "<<izuzetak.what()<<"!"<<std::endl;
    }
    return 0;
}
