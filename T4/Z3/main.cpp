//TP 2018/2019: Tutorijal 4, Zadatak 3
#include <iostream>
#include <string>
#include <vector>


std::string PretvoriUVelika(std::string rijec)
{
    std::string RijecVelikaSlova;
    for(int i=0; i<rijec.length(); i++) {
        if(rijec.at(i)>='a' && rijec.at(i)<='z') {
            RijecVelikaSlova.push_back(char(std::toupper(rijec.at(i))));
        } else RijecVelikaSlova.push_back(rijec.at(i));
    }
    return RijecVelikaSlova;
}
void IzdvojiKrajnjeRijeci(std::vector<std::string> &VektorRijeci, std::string &PrvaAbecedno, std::string &ZadnjaAbecedno)
{
    if(VektorRijeci.size()==0) {
        std::string s;
        PrvaAbecedno=s;
        ZadnjaAbecedno=s;
    } else {
        std::string MaxLeksitografski = VektorRijeci.at(0);
        std::string MinLeksitografski = VektorRijeci.at(0);
        for(int i=1; i<VektorRijeci.size(); i++) {
            if( PretvoriUVelika(VektorRijeci.at(i)) < PretvoriUVelika(MinLeksitografski)) {
                MinLeksitografski=VektorRijeci.at(i);
            }
            if( PretvoriUVelika(VektorRijeci.at(i)) > PretvoriUVelika(MaxLeksitografski)) {
                MaxLeksitografski=VektorRijeci.at(i);
            }
        }
        PrvaAbecedno = MinLeksitografski;
        ZadnjaAbecedno = MaxLeksitografski;
    }


}

template< typename ProizvoljanTip>

void IzbaciIzVektora(std::vector<ProizvoljanTip> &Vektor, int index)
{
    for(int i=0; i<Vektor.size(); i++) {
        if(i==index) {
            for(int j=i; j<Vektor.size()-1; j++)
            Vektor.at(j)=Vektor.at(j+1);
        }
        

    }
    //int velicina = Vektor.size() - 1;
    
     Vektor.resize(Vektor.size()-1);
    // for(auto x: Vektor){
    //     std::cout<<x<<" ";
    // }
}
void ZadrziDuplikate(std::vector<std::string> &VektorRijeci)
{
    //ostaviti samo rijeci koje su ponovljene u vektoru
    bool izbacila = false;
    for(int i=0; i<VektorRijeci.size(); i++) {
        for(int j=i+1; j<VektorRijeci.size(); j++) {
            if(VektorRijeci.at(i)==VektorRijeci.at(j)) {
                IzbaciIzVektora(VektorRijeci, j);
                j--;
                izbacila = true;
            }
        
        }
        if(!izbacila){
            IzbaciIzVektora(VektorRijeci, i);
            i--;
        }
        izbacila=false;
    }
}
int main ()
{
    
    int BrojRijeci;
    std::cout<<"Koliko zelite unijeti rijeci: ";
    std::cin>>BrojRijeci;
    //std::cin>>std::ws;
    std::cout<<"Unesite rijeci: ";
    std::vector< std::string > VektorRijeci(BrojRijeci);
    for(int i=0; i<BrojRijeci; i++){
        std::cin>>std::ws;
        std::cin>>VektorRijeci.at(i); //vidjeti koji je nacin bolji
    }
    std::string PrvaRijec;
    std::string PosljednjaRijec;
    IzdvojiKrajnjeRijeci(VektorRijeci, PrvaRijec, PosljednjaRijec);
    std::cout<<std::endl<<"Prva rijec po abecednom poretku je: "<<PrvaRijec<<std::endl;
    std::cout<<"Posljednja rijec po abecednom poretku je: "<<PosljednjaRijec<<std::endl;
    ZadrziDuplikate(VektorRijeci);
    std::cout<<"Rijeci koje se ponavljaju su: ";
    for(int i=0; i<VektorRijeci.size(); i++){
        if(i==VektorRijeci.size()-1) std::cout<<VektorRijeci.at(i);
        else std::cout<<VektorRijeci.at(i)<<" ";
    }

    
    return 0;
}
