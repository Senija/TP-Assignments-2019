//TP 2018/2019: Tutorijal 3, Zadatak 1
#include <iostream>
#include <deque>
#include <cmath>
#include<limits>
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
std::deque<int> IzdvojiElemente(std::deque<int> v1, bool istina)
{
    std::deque<int> novi;
    if(istina) {

        for(int i=v1.size()-1; i>=0; i--) {
            if(sumaCifara(v1[i])) {
                novi.push_front(v1[i]);
            }
        }
    }
    if(!istina) {
        for(int i=v1.size()-1; i>=0; i--) {
            if(!sumaCifara(v1[i])) {
                novi.push_front(v1[i]);
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
        std::deque<int> v;
        std::cout<<"Unesite elemente: ";
        for(int i=0; i<br_elemenata; i++) {
            int element;
            std::cin>>element;
            v.push_back(element);
        }
        auto b=IzdvojiElemente(v, true);
        auto c=IzdvojiElemente(v, false);
        for(int i=0; i<b.size(); i++) {
          if(i==b.size()-1) std::cout<<b[i];
          else std::cout<<b[i]<<",";
        }
        std::cout<<std::endl;
        for(int i=0; i<c.size(); i++) {
            if(i==c.size()-1) std::cout<<c[i];
            else std::cout<<c[i]<<",";
        }
    }

    return 0;
}