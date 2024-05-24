//TP 2016/2017: Tutorijal 1, Zadatak 1
#include <iostream>
#include <cmath>
#include <iomanip>
int main ()
{
    int a, b, c;
    for(;;) {
        std::cout<<"Unesite duzinu, sirinu i dubinu bazena u metrima: ";
        std::cin>>a>>b>>c;
        if(std::cin) break;
        std::cin.clear();
        std::cin.ignore(1000, '\n');
        std::cin>>a>>b>>c;
    }
    int d;
    for(;;) {
        std::cout<<"Unesite sirinu plocice u centimetrima: "<<std::endl;
        std::cin>>d;
        if(std::cin) break;
        std::cin.clear();
        std::cin.ignore(1000, '\n');
        std::cin>>d;
    }
    double br_plocica=(a*b + 2*a*c + 2*b*c)/ (d * d * std::pow(10, -4));
    if(a*100 % d ==0 && b*100 % d==0 && c*100 % d==0) 
        std::cout<<"Za poplocavanje bazena dimenzija "<<a<<"x"<<b<<"x"<<c<<"m sa plocicama dimenzija "<<d<<"x"<<d<<"cm"<<std::endl<< "potrebno je "<<br_plocica<<" plocica.";
    else std::cout<<"Poplocavanje bazena dimenzija "<<a<<"x"<<b<<"x"<<c<<"m sa plocicama dimenzija "<<d<<"x"<<d<<"cm"<<std::endl<<"nije izvodljivo bez lomljenja plocica!";
}
