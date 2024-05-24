//TP 2018/2019: Tutorijal 3, Zadatak 8
#include <iostream>
#include <string>
#include <stdexcept>
std::string IzdvojiRijec(std::string recenica, int broj){
    if(broj<1 || recenica.length()==0) throw std::range_error("Pogresan redni broj rijeci!");
    int br_rijeci=0;
    bool razmak=true;
    std::string rijec;
    for(int i=0; i<=recenica.length()-1; i++){
        if(recenica[i]==' '){
            razmak=true;
        }
        else if(razmak){
            br_rijeci++;
            razmak=false;
            if(br_rijeci==broj){
                for(int j=i; j<=recenica.length()-1; j++){
                    if(recenica[j]==' ') break;
                    rijec.push_back(recenica[j]);
                }
            }
        }
    }
    if(broj>br_rijeci) throw std::range_error("Pogresan redni broj rijeci!");
    return rijec;
}
int main ()
{
    int redni_br_rijeci;
    std::cout<<"Unesite redni broj rijeci: ";
    std::cin>>redni_br_rijeci;
    std::string recenica;
    std::cout<<"Unesite recenicu: ";
    std::cin.ignore(1000, '\n');
    std::getline(std::cin, recenica);
    try{
        std::string izdvojena=IzdvojiRijec(recenica, redni_br_rijeci);
        std::cout<<"Rijec na poziciji "<<redni_br_rijeci<<" je "<<izdvojena<<std::endl;
    }
    catch(std::range_error izuzetak){
        std::cout<<"IZUZETAK: "<<izuzetak.what()<<std::endl;
    }
    
    
	return 0;
}