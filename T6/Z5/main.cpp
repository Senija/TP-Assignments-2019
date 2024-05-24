#include <iostream>
#include <type_traits>
#include <new>
#include <vector>
#include <algorithm>
#include <deque>

template<typename KontejnerskiTip>
auto KreirajDinamickuKopiju2D(KontejnerskiTip c) -> decltype(c[0][0] + c[0][0])**
{

    decltype(c[0][0] + c[0][0]) **pok=nullptr;
    try {
        pok = new decltype(c[0][0] + c[0][0])*[c.size()];
        for(int i=0; i<c.size(); i++) {
            pok[i] = new decltype(c[0][0] + c[0][0])[c[i].size()];
        }
        for(int i=0; i<c.size(); i++) {
            for(int j=0; j<c[i].size(); j++) {
                pok[i][j] = c[i][j];
            }
        }
    } catch(std::bad_alloc) {
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
        
        for(int i=0; i<dimenzijeMatrice; i++) delete[] pok[i];
        delete[] pok;
    }
    catch(std::bad_alloc){
        std::cout<<"Nedovoljno memorije"<<std::endl;
    }
    

    return 0;
}
