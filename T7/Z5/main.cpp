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
        std::shared_ptr<PametniPokString> DupliNaShared (new PametniPokString[broj_recenica], [] (PametniPokString *pok){ delete[] pok;}); //oametni pok pokazuje na dinamicki niz shared ptr od broj recenica elemenata????
        try {
            for(int i=0; i<broj_recenica; i++) {
                (DupliNaShared.get())[i] = std::make_shared<std::string>();
                //std::string pomocna;
                std::getline(std::cin, *(DupliNaShared.get())[i]);
                
                //std::cin>>std::ws;
            }
            //sort
            for(int i=0; i<broj_recenica; i++) {
                int min = i;
                for(int j = i+1; j<broj_recenica; j++) {
                    if(*(DupliNaShared.get())[j] < *(DupliNaShared.get())[min]) min= j;
                }
                auto tmp = (DupliNaShared.get())[i];
                (DupliNaShared.get())[i] = (DupliNaShared.get())[min];
                (DupliNaShared.get())[min] = tmp;
            }
            std::cout<<"Sortirane recenice:"<<std::endl;
            for(int i=0; i<broj_recenica; i++) std::cout<< *(DupliNaShared.get())[i]<<std::endl;
        } catch(...) {
            throw;
        }
    } catch(...) {
        std::cout <<"Problemi s memorijom!"<< std::endl;
    }

    return 0;
}