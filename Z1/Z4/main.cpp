//TP 2016/2017: Zadaća 1, Zadatak 4 POSLALA SI OVAJ NE SALJI VISE
#include <iostream>
#include <cmath>
#include <string>

bool JeLiSlovoVokal(char c)
{
    bool vokal=false;
    if(c=='a' || c=='e' || c=='i' || c=='o' || c=='u' || c=='A' || c=='E' || c=='I' || c=='O' || c=='U' ) vokal= true;
    return vokal;
}

bool JeLiRijecRitmicna(std::string &rijec)
{
    //prazan string
    //if(rijec.length() == 0)
    bool ritmicna=true;
    if(rijec.length() == 1) return false;
    for(int i=0; i<rijec.length(); i++) {
        if(JeLiSlovoVokal(rijec.at(i))) {
            for(int j=i+1; j<rijec.length(); j++) {
                if( j%2!=0 && JeLiSlovoVokal(rijec.at(j))) {

                    ritmicna=false;
                    break;
                }
                if( j%2==0 && !JeLiSlovoVokal(rijec.at(j))) {
                    ritmicna=false;
                    break;
                }
            }

        } else if(!JeLiSlovoVokal(rijec.at(i))) {
            for(int j=i+1; j<rijec.length(); j++) {
                if(j%2!=0 && !JeLiSlovoVokal(rijec.at(j))) {
                    ritmicna=false;
                    break;
                }
                if(j%2==0 && JeLiSlovoVokal(rijec.at(i))) {
                    ritmicna=false;
                    break;
                }
            }

        }
        if(ritmicna == false || i==0) break;
    }
    return ritmicna;
}

std::string IstakniSavrsenoRitmicneRijeci(std::string recenica)
{
    bool razmak = true;
    for(int i=0; i<recenica.length(); i++) {
        if(recenica.at(i)==' ') {
            razmak=true;
        } 
        else if(razmak) {
            razmak=false;
            // dosla do slova
            std::string pomocna;
            int pozicija1=i;
            int pozicija2=i;
            for(int j=i; j<recenica.length(); j++ ) {
                pomocna.push_back(recenica.at(j));
                pozicija2++;
                if(j==recenica.length()-1 || recenica.at(j+1)==' ') {
                    i=j; //i++
                    break;
                }
            }
            if(JeLiRijecRitmicna(pomocna)){
                recenica.insert(recenica.begin() + pozicija1, '(');
                recenica.insert(recenica.begin() + pozicija2+1, ')'); //jer je umetnuo (
            }
        }
    }
    return recenica;
}
int main ()
{
    
    std::string recenica;
    std::cout<<"Unesite recenicu (ENTER za kraj): ";
    std::getline(std::cin, recenica);
    //std::cin.ignore(1000, '\n');
    //std::cout<<recenica.length();
    std::cout<<"Recenica sa istaknutim savrseno ritmicnim rijecima glasi:"<<std::endl<<IstakniSavrsenoRitmicneRijeci(recenica)<<std::endl;

    return 0;
}
