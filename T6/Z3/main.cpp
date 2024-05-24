#include <iostream>
#include <type_traits>
#include <new>
#include <vector>
#include <type_traits>
#include <forward_list>
#include <algorithm>

int **KreirajTrougao(int BrojRedova)
{
    if(BrojRedova<=0) throw std::domain_error ("Broj redova mora biti pozitivan");
    int **pok=nullptr;
    pok=new int*[BrojRedova];
    try {
        for(int i=0; i<BrojRedova; i++) {
            pok[i] = new int[i*2 + 1];
        }
        for(int i =0; i<BrojRedova; i++) {
            for(int j=0; j< i*2 + 1; j++) {
                if(j<= (i*2 +1)/2) pok[i][j]=i+1-j;
                else pok[i][j] = pok[i][j-1]+1;
            }
        }
        return pok;
    } catch(std::bad_alloc) {
        for(int i=0; i<BrojRedova; i++) delete[] pok[i];
        delete[] pok;
        throw;
    }

}
int main ()
{
    try {
        int broj_redova;
        std::cout<<"Koliko zelite redova: ";
        std::cin>>broj_redova;
        int **Pok=KreirajTrougao(broj_redova);
        for(int i=0; i<broj_redova; i++) {
            for(int j=0; j<i*2 + 1; j++) {
                std::cout<<Pok[i][j]<<" ";
            }
            std::cout<<std::endl;
        }
        for(int i=0; i<broj_redova; i++) delete[] Pok[i];
        delete[] Pok;
    } 
    catch(std::domain_error izuzetak) {
        std::cout<<"Izuzetak: "<<izuzetak.what()<<std::endl;
    } 
    catch(...) {
        std::cout<<"Izuzetak: Nedovoljno memorije!"<<std::endl;
    }

    return 0;
}
