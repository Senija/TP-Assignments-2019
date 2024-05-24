//ISPIT Zadatak 6
#include <iostream>
#include <string>
#include <exception>
std::string IzdvojiRijec(std::string recenica, int n){
    if(n < 1) throw std::domain_error ("Broj rijeci ne smije biti negativan");
    bool razmak = true;
    int br_rijeci = 0;
    for(int i=0; i<recenica.length(); i++){
        if(recenica.at(i) == ' '){
            razmak = true;
        }
        else if(razmak){
            br_rijeci++;
            razmak = false;
            if(br_rijeci == n){
                std::string pomocna;
                //int j=0;
                for(int j=i; j < recenica.length(); j++){
                    if(recenica.at(j) == ' ') return pomocna;
                    pomocna.push_back(recenica.at(j));
                    if( j+1 == recenica.length()) return pomocna;
                }
            }
        }
    }
    if(br_rijeci < n ) throw std::domain_error ("ne postoji toliko rijeci u recenici.");
    //return pomocna;
}
int main ()
{
    int n;
    //std::cin>>n;
    std::string recenica = "   Ja    idem   na   ETF";
    std::cout<<IzdvojiRijec(recenica, 0);
	return 0;
}