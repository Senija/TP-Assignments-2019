//TP Priprema za ispit 4 zadatak prvi ispit
#include <iostream>
#include <string>
#include <algorithm>

int main ()
{
    int br_recenica;
    std::cout<<"Unesi n: ";
    std::cin>>br_recenica;
    std::cin.ignore(10000, '\n');
    std::string **DupliPok = nullptr;
    try{
        DupliPok = new std::string *[br_recenica];
        for(int i=0; i<br_recenica; i++){
            DupliPok[i] = nullptr;
            DupliPok[i] = new std::string;
            std::getline(std::cin, *DupliPok[i]);
        }
        
        std::sort(DupliPok, DupliPok+br_recenica, [](std::string *rec1, std::string *rec2){return *rec1 < *rec2;});
        
        for(int i =0; i<br_recenica; i++){
            std::cout<<*DupliPok[i]<<std::endl;
        }
        for(int i=0; i<br_recenica; i++) delete DupliPok[i];
        delete[] DupliPok;
    }
    catch(std::bad_alloc){
        for(int i=0; i<br_recenica; i++) delete DupliPok;
        delete[] DupliPok;
    }
    
	return 0;
}