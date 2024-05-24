//TP 2018/2019: Tutorijal 2, Zadatak 1
#include <iostream>
#include <vector>
#include <cmath>
#include <limits>
bool DaLiJeProst(int n){
    bool prost=true;
    if(n<2) prost=false;
    for(int i=2; i<=std::sqrt(n); i++){
        if(n%i==0){
            prost=false;
            break;
        }
    }
    return prost;
}
std::vector<int> ProstiBrojeviUOpsegu(int a, int b){
    std::vector<int> prosti;
    for(int i=a; i<=b; i++){
        if(DaLiJeProst(i)==true){
            prosti.push_back(i);
        }
        if(i==b) break;
    }
    return prosti;
}
int main ()
{
    int pocetna, krajnja;
    std::cout<<"Unesite pocetnu i krajnju vrijednost: ";
    std::cin>>pocetna>>krajnja;
    //std::cout<<std::endl;
    std::vector<int>prosti;
    if(pocetna>1) prosti=ProstiBrojeviUOpsegu(pocetna, krajnja);
    else prosti=ProstiBrojeviUOpsegu(2, krajnja);
    if(prosti.size()!=0){
        std::cout<<"Prosti brojevi u rasponu od "<<pocetna<<" do "<<krajnja<<" su: ";
        for(int i=0; i<prosti.size(); i++){
            if(i != prosti.size()-1 ) std::cout<<prosti.at(i)<<", ";
            else std::cout<<prosti.at(i);
        } 
        std::cout<<std::endl;
        
    }
    else std::cout<<"Nema prostih brojeva u rasponu od "<<pocetna<<" do "<<krajnja<<"!";
	return 0;
}