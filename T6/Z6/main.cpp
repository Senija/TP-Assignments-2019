#include <iostream>
#include <type_traits>
#include <new>
#include <vector>
#include <algorithm>
#include <deque>
template<typename KontejnerskiTip>
int BrojElemenata(KontejnerskiTip c){
    int br_elemenata=0;
    for(int i=0; i<c.size(); i++){
        for(int j=0; j<c[i].size(); j++){
            br_elemenata++;
        }
    }
    return br_elemenata;
}

template<typename KontejnerskiTip>
auto KreirajDinamickuKopiju2D(KontejnerskiTip c) -> decltype(c[0][0] + c[0][0])**{
    
    decltype(c[0][0] + c[0][0])** pok = nullptr;
    try{
        pok = new decltype(c[0][0] + c[0][0]) *[c.size()];
        pok[0] = new decltype(c[0][0] + c[0][0]) [BrojElemenata(c)];
        
        for(int i=1; i<c.size(); i++){
            pok[i]= pok[i-1] + c[i-1].size();
        }
        for(int i=0; i<c.size(); i++) {
            for(int j=0; j<c[i].size(); j++) {
                pok[i][j] = c[i][j];
            }
        }
    }
    catch(std::bad_alloc){
        //delete[] pok[0];
        delete[] pok;
        throw;
    }
    return pok;
}

int main ()
{
    try {
         int dimenzijeMatrice;
        std::cout<<"Unesite broj redova kvadratne matrice: ";
        std::cin>>dimenzijeMatrice;
        std::vector<std::deque<int>> VektorDekova(dimenzijeMatrice, std::deque<int>(dimenzijeMatrice));
        std::cout <<"Unesite elemente matrice: ";
        for(int i=0; i<dimenzijeMatrice; i++) {
            for(int j=0; j<dimenzijeMatrice; j++) {
                std::cin>>VektorDekova[i][j];
                //VektorDekova[i][j].push_back(broj);
            }
        }
        auto pok = KreirajDinamickuKopiju2D(VektorDekova);
        for(int i=0; i<dimenzijeMatrice; i++){
            for(int j=0; j<dimenzijeMatrice; j++){
                std::cout<<pok[i][j]<<" ";
            }
            std::cout<<std::endl;
        }
        
        delete[] pok[0];
        delete[] pok;
    }
    catch(std::bad_alloc){
        std::cout<<"Nedovoljno memorije"<<std::endl;
    }

    

    return 0;
}