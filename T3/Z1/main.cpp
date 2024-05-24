//TP 2018/2019: Tutorijal 3, Zadatak 1
#include <iostream>
#include <vector>
#include <cmath>
bool sumaCifara(int x)
{
    bool parna=false;
    int suma=0;
    if(x<0) x=abs(x);
    do {
        suma+=x%10;
        x=x/10;
    } while(x!=0);

    if(suma%2==0) parna=true;
    return parna;
}
std::vector<int> IzdvojiElemente(std::vector<int> v1, bool istina)
{
    std::vector<int> novi;
    if(istina) {

        for(int x: v1) {
            if(sumaCifara(x)) {
                novi.push_back(x);
            }
        }
    }
    if(!istina) {
        for(int x: v1) {
            if(!sumaCifara(x)) {
                novi.push_back(x);
            }
        }
    }
    return novi;
}
int main ()
{
    int br_elemenata;
    std::cout<<"Koliko zelite unijeti elemenata: ";
    std::cin>>br_elemenata;
    if(br_elemenata<=0) {
        std::cout<<"Broj elemenata mora biti veci od 0!";
    } 
    else {
        std::vector<int> v;
        std::cout<<"Unesite elemente: ";
        for(int i=0; i<br_elemenata; i++) {
            int element;
            std::cin>>element;
            v.push_back(element);
        }
        auto b=IzdvojiElemente(v, true);
        auto c=IzdvojiElemente(v, false);
        for(int x: b) {
            std::cout<<x<<" ";
        }
        std::cout<<std::endl;
        for(int x: c) {
            std::cout<<x<<" ";
        }
    }

    return 0;
}
