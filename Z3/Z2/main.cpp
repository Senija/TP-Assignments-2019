//TP 2018/2019: Zadaća 3, Zadatak 2
#include <iostream>
#include <map>
#include <string>
#include <vector>
#include <tuple>
#include <set>
#include <iterator>
#include <exception>



typedef std::map<std::string, std::vector<std:: string>> Knjiga;
typedef std::map<std::string, std::set<std::tuple<std::string, int, int>>> Pojmovnik;

std::string PretvoriUMala(std::string rijec)
{
    for(int i=0; i!= rijec.length(); i++) {
        if(rijec.at(i) >='A' && rijec.at(i) <= 'Z') rijec.at(i) = char(std::tolower(rijec.at(i)));
    }
    return rijec;
}

Pojmovnik KreirajIndeksPojmova(const Knjiga &k)
{
    Pojmovnik MapaRijeci;
    if(k.size() == 0) return MapaRijeci;
    for(auto it = k.begin(); it !=k.end(); it++) {
        for(int i = 0; i !=it->second.size(); i++) {
            for(auto j = it->second.at(i).begin() ; j != it->second.at(i).end(); j++) {
                std::string pomocna;
                int pozicija;
                if(((*j >= 'A' && *j <= 'Z') || (*j >= 'a' && *j <= 'z') || (*j >= '0' && *j <= '9'))) pozicija = std::distance(it->second.at(i).begin(), j);
                while((*j >= 'A' && *j <= 'Z') || (*j >= 'a' && *j <= 'z') || (*j >= '0' && *j <= '9')) {
                    pomocna.push_back(*j);
                    if( j != it->second.at(i).end()-1) j++;
                    else break;

                }
                if(pomocna.length() != 0 && MapaRijeci.find(PretvoriUMala(pomocna)) == MapaRijeci.end()) {
                    // MapaRijeci[pomocna] = std::make_tuple(it->first, i+1, pozicija);
                    //std::pair<std::string, std::set<std::tuple<std::string, int, int>>> zaInserta(  pomocna, std::set<  std::tuple<std::string, int, int>  >{std::make_tuple(it->first, i+1, pozicija) }  );
                    MapaRijeci.insert(std::pair<std::string, std::set<std::tuple<std::string, int, int>>> (PretvoriUMala(pomocna), std::set<  std::tuple<std::string, int, int>  > {std::make_tuple(it->first, i+1, pozicija) }  ));
                } else if(pomocna.length() != 0) {
                    auto PozTrojke =  MapaRijeci.find(PretvoriUMala(pomocna));
                    PozTrojke->second.insert(std::make_tuple(it->first, i+1, pozicija));
                }
            }
        }
    }
    return MapaRijeci;
}

std::set<std::tuple<std::string, int, int>> PretraziIndeksPojmova(const std::string &rijec, const Pojmovnik &MapaRijeci)
{

    if(MapaRijeci.find(rijec) == MapaRijeci.end()) throw std::logic_error ("Pojam nije nadjen");
    return MapaRijeci.find(rijec)->second;

}
void IspisiIndeksPojmova(const Pojmovnik &MapaRijeci)
{
    if(MapaRijeci.size() == 0) return;
    for(auto it = MapaRijeci.begin(); it != MapaRijeci.end(); it++) {

        std::cout<<it->first<<": ";
        auto pom = MapaRijeci.begin();
        std::advance(pom, MapaRijeci.size()-1);
        for(auto itSet = it->second.begin(); itSet != it->second.end(); itSet++) {
            if ( itSet != it->second.begin() )
                std::cout <<", ";
            //if() std::cout<<std::get<0>(*itSet)<<"/"<<std::get<1>(*itSet)<<"/"<<std::get<2>(*itSet)<<std::endl;
            std::cout<<std::get<0>(*itSet)<<"/"<<std::get<1>(*itSet)<<"/"<<std::get<2>(*itSet);
        }
        if(it != pom) std::cout<<std::endl;

    }
}

int main ()
{
    Knjiga k;

    std::string poglavlje;
    while(1) {
        std::cout<<"Unesite naziv poglavlja: ";
        std::getline(std::cin, poglavlje);
        if(poglavlje == ".") break;
        //std::cin>>std::ws;
        //std::cin.ignore(10000, '\n');
        std::vector<std::string> Stranice;
        int br_stranica = 1;
        while(1) {

            std::cout<<"Unesite sadrzaj stranice "<< br_stranica <<": ";
            std::string tekst;
            std::getline(std::cin, tekst);
            if(tekst == std::string(".")) break;
            Stranice.push_back(tekst);
            br_stranica++;
        }
        k.insert(std::pair<std::string, std::vector<std::string>> (poglavlje, Stranice));
    }
    std::cout<<std::endl<<"Kreirani indeks pojmova: "<<std::endl;
    //k.insert(std::pair<std::string, std::vector<std::string>> (poglavlje, Stranice));
    auto MapaRijeci = KreirajIndeksPojmova(k);
    IspisiIndeksPojmova(MapaRijeci);
    while(1) {
        try {
            std::cout<<std::endl<<"Unesite rijec: ";
            std::string rijec;
            std::getline(std::cin, rijec);
            if(rijec == ".") break;
            auto pozicije = PretraziIndeksPojmova(rijec, MapaRijeci);
            for(auto itSet = pozicije.begin(); itSet != pozicije.end(); itSet++) {
            if ( itSet != pozicije.begin() )
                std::cout <<" ";
            //if() std::cout<<std::get<0>(*itSet)<<"/"<<std::get<1>(*itSet)<<"/"<<std::get<2>(*itSet)<<std::endl;
            std::cout<<std::get<0>(*itSet)<<"/"<<std::get<1>(*itSet)<<"/"<<std::get<2>(*itSet);
        }
            

        } catch(std::logic_error izuzetak) {
            //std::cout<<izuzetak.what()<<std::endl;
            std::cout<<"Unesena rijec nije nadjena!";
        }
    }
    return 0;
}
