#include <iostream>
#include <new>
#include <string>
#include <algorithm>
int main ()
{
    
    
    std::string **PokRecenice = nullptr; //2 struki pok
    try {
        int broj_recenica;
        std::cout<<"Koliko zelite recenica: ";
        std::cin>>broj_recenica;
        std::cin.ignore(10000,'\n');
        std::cout<<"Unesite recenice:"<<std::endl;
        PokRecenice = new std::string *[broj_recenica]; 
        
        for(int i = 0; i<broj_recenica; i++){
            PokRecenice[i] = nullptr;
        }
        
        for(int i=0; i<broj_recenica; i++) {
            PokRecenice[i] = new std::string;
            std::getline(std::cin, *PokRecenice[i]);
            //std::cin>>std::ws;
        }

        std::sort(PokRecenice, PokRecenice + broj_recenica, []( std::string *a, std::string *b) ->bool { return *a < *b ; } );
        std::cout<<"Sortirane recenice:"<<std::endl;
        for(int i=0; i<broj_recenica; i++) std::cout<< PokRecenice[i][0]<<std::endl;
        for(int i=0; i<broj_recenica; i++) delete PokRecenice[i];
        delete[] PokRecenice;
    } catch(...) {
        delete[] PokRecenice;
        std::cout <<"Problemi s memorijom!"<< std::endl;
    }


    return 0;
}
    