#include <iostream>
#include <memory>
#include <string>
#include <algorithm>

typedef std::shared_ptr<std::string> PametniPokString;
int main ()
{

    try {

        int broj_recenica;
        std::cout<<"Koliko zelite recenica: ";
        std::cin>>broj_recenica;
        std::cin.ignore(10000,'\n');
        std::cout<<"Unesite recenice:"<<std::endl;
        std::unique_ptr<PametniPokString []> JednistveniPok (new PametniPokString[broj_recenica]); //oametni pok pokazuje na dinamicki niz shared ptr od broj recenica elemenata????
        try {
            for(int i=0; i<broj_recenica; i++) {
                JednistveniPok[i] = std::make_shared<std::string>();
                //std::string pomocna;
                std::getline(std::cin, *JednistveniPok[i]);
                
                //std::cin>>std::ws;
            }
            //sort
            for(int i=0; i<broj_recenica; i++) {
                int min = i;
                for(int j = i+1; j<broj_recenica; j++) {
                    if(*JednistveniPok[j] < *JednistveniPok[min]) min= j;
                }
                auto tmp = std::move(JednistveniPok[i]);
                JednistveniPok[i] = std::move(JednistveniPok[min]);
                JednistveniPok[min] = std::move(tmp);
            }
            std::cout<<"Sortirane recenice:"<<std::endl;
            for(int i=0; i<broj_recenica; i++) std::cout<< *JednistveniPok[i]<<std::endl;
        } catch(...) {
            throw;
        }
    } catch(...) {
        std::cout <<"Problemi s memorijom!"<< std::endl;
    }

    return 0;
}
