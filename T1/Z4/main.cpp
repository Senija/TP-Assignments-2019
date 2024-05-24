//TP 2016/2017: Tutorijal 1, Zadatak 4
#include <iostream>
#include <cmath>
int main ()
{
    double broj=1;
    int suma=0;
    std::cout<<"Unesite prirodan broj ili 0 za kraj: ";
    while(1) {
        std::cin>>broj;
        if(!(std::cin) || broj<0 || int(broj)!=broj) {
            std::cout<<"Niste unijeli prirodan broj!"<<std::endl;
            std::cin.clear();
            std::cin.ignore(1000, '\n');
            std::cout<<"Unesite prirodan broj ili 0 za kraj: ";

        }
        else if(broj>=0){
            if(broj==0) break;
            suma=0;
            for(int i=1; i<int(broj); i++)
                if(int(broj)%i==0) suma+=i;
            if(suma>broj) std::cout<<"Broj "<<broj<<" je obilan!"<<std::endl;
            if(suma<broj) std::cout<<"Broj "<<broj<<" je manjkav!"<<std::endl;
            if(suma==broj) std::cout<<"Broj "<<broj<<" je savrsen!"<<std::endl;
            std::cout<<"Unesite prirodan broj ili 0 za kraj: ";

        }
    }
    std::cout<<"Dovidjenja!";
    return 0;
}
