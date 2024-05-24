//TP 2018/2019: Tutorijal 4, Zadatak 1
#include <iostream>
#include <cmath>
//#include <limits>
int Cifre(long long int n, int& c_min, int& c_max){
    //if(n<0) n= n*-1;
    int min_pom=10, max_pom=-1, brojac=0;
    do{
        
        brojac++;
        if(std::abs(n%10) < min_pom) min_pom=std::abs(n%10);
        if(std::abs(n%10) > max_pom) max_pom=std::abs(n%10); 
        n=n/10;

        
    }while(n!=0);
    c_min=min_pom;
    c_max=max_pom;
    return brojac;
}
int main ()
{
    long long int broj=0;
    int min , max ;
    std::cout<<"Unesite broj: ";
    std::cin>>broj;
    std::cin.ignore(10000,'\n');
    int povratnik =  Cifre(broj,min,max);
    std::cout<<"Broj "<<broj<<" ima "<< povratnik <<" cifara, najveca je "<<max<<" a najmanja "<<min<<".";
    //std::cout<<std::abs(-54746639%10);
	return 0;
}