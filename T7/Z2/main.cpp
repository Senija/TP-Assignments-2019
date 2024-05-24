#include <iostream>
#include <new>
#include <cstring>
#include <algorithm>
int main ()
{
    
    
    char **PokRecenice = nullptr;
    try {
        int broj_recenica;
        std::cout<<"Koliko zelite recenica: ";
        std::cin>>broj_recenica;
        std::cin>>std::ws;
        std::cout<<"Unesite recenice:"<<std::endl;
        PokRecenice = new char*[broj_recenica];
        
        for(int i=0; i<broj_recenica; i++) {
            char radni_prostor[1000];
            //std::cin>>std::ws;
            std::cin.getline(radni_prostor, sizeof radni_prostor);
            PokRecenice[i] = new char[std::strlen(radni_prostor)+1];
            std::strcpy(PokRecenice[i], radni_prostor);
        }
        //for(int i=0;)
        std::sort(PokRecenice, PokRecenice + broj_recenica, []( char *a, char *b) ->bool { return std::strcmp(a, b) < 0; } );
        std::cout<<"Sortirane recenice:"<<std::endl;
        for(int i=0; i<broj_recenica; i++) std::cout<<PokRecenice[i]<<std::endl;
        for(int i=0; i<broj_recenica; i++) delete[] PokRecenice[i];
        delete[] PokRecenice;
    } catch(...) {
        delete[] PokRecenice;
        std::cout <<"Problemi s memorijom!"<< std::endl;
    }


    return 0;
}