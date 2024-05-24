//TP 2016/2017: Zadaća 1, Zadatak 1
#include <iostream>
#include <cmath>
#include <vector>
#include <string>
bool JeLiSimetrican(std::string StringBroj)
{
    //bool simetrican=false;
    //if(x<0) x=std::abs(x);
    //std::string StringBroj=std::to_string(x);
    if(StringBroj.at(0)=='-') StringBroj.erase(StringBroj.begin()+0);
    std::string ObrnutBroj;
    for(int i=StringBroj.length()-1; i>=0; i--) {
        ObrnutBroj.push_back(StringBroj.at(i));
    }
    return ObrnutBroj==StringBroj;
}
std::string ToTernarni(long long int DecBroj)
{
    int predznak=1;
    if(DecBroj<0) {
        predznak=-1;
       // DecBroj=std::abs(DecBroj);
    }
    std::string ostatci;
    int rez=DecBroj;
    do {
        int pomocna=std::abs(rez%3);
        std:: string StringOstatak=std::to_string(pomocna);
        rez=std::abs(rez/3);
        for(int i=0; i<StringOstatak.length(); i++) {
            ostatci.push_back(StringOstatak.at(i));
        }


    } while(rez!=0);
    std::string ternarni;
    for(int i=ostatci.length()-1; i>=0; i--) {
        ternarni.push_back(ostatci.at(i));
    }
    if(predznak == -1) ternarni.insert(std::begin(ternarni), '-');
    return ternarni;

}
std::vector<int> IzdvojiSimetricneTernarne(std::vector<int> v, bool simetrican=true)
{
    std::vector<int> rezultantni;
    if(simetrican) {
        for(int x: v) {
            if(JeLiSimetrican(std::to_string(x))) {
                if(JeLiSimetrican(ToTernarni(x))) {
                    rezultantni.push_back(x);

                }

            }
        }

    } else if(!simetrican) {
        for(int x: v) {
            if(!JeLiSimetrican(std::to_string(x))) {
                if(JeLiSimetrican(ToTernarni(x))) {
                    rezultantni.push_back(x);
                }
            }
        }
    }
    for(int i=0; i<rezultantni.size(); i++) {
        for(int j=i+1; j<rezultantni.size(); j++) {
            if(rezultantni.at(i)==rezultantni.at(j)) {
                rezultantni.erase(rezultantni.begin() + j);
                j--;
            }
        }
    }
    return rezultantni;
}
int main ()
{
    int brElemenata;
    std::cout<<"Unesite broj elemenata niza: ";
    std::cin>>brElemenata;
    std::vector<int> v(brElemenata);
    std::cout<<"Unesite elemente niza: ";
    for(int i=0; i<brElemenata; i++) {
        std::cin>>v.at(i);
    }
    bool parametar;
    std::cout<<"Unesite parametar (1 ili 0): ";
    std::cin>>parametar;//provjeriti je li broj i ta shit
    auto SimetricniVektor=IzdvojiSimetricneTernarne(v, parametar);
    std::cout<<"Izdvojeni elementi su: ";
    for(int i=0; i<SimetricniVektor.size(); i++) {
        if(i==SimetricniVektor.size()-1)  std::cout<<SimetricniVektor.at(i);
        else std::cout<<SimetricniVektor.at(i)<<", ";
    }


    return 0;
}
