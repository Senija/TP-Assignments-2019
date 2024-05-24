#include <iostream>
#include <type_traits>
#include <new>
#include <vector>
#include <algorithm>

int **KreirajTrougao(int BrojRedova)
{
    if(BrojRedova<=0) throw std::domain_error ("Broj redova mora biti pozitivan");
    int **pok=nullptr;
    pok=new int*[BrojRedova];

    try {
        pok[0]= new int[BrojRedova * BrojRedova];
        for(int i=1; i<BrojRedova; i++) {
            pok[i]=pok[i-1] +2*i -1;
        }
        for(int i =0; i<BrojRedova; i++) {
            for(int j=0; j< i*2 + 1; j++) {
                if(j<= (i*2 +1)/2) pok[i][j]=i+1-j;
                if(j>(i*2 +1)/2) pok[i][j] = pok[i][j-1]+1;
            }
        }
        return pok;
    } catch(std::bad_alloc) {
        delete[] pok;
        throw;
    }

}
int main ()
{
    int broj_redova;
    std::cout<<"Koliko zelite redova: ";
    std::cin>>broj_redova;
    int **Pok=nullptr;
    try {

        Pok = KreirajTrougao(broj_redova);
        for(int i=0; i<broj_redova; i++) {
            for(int j=0; j<i*2 + 1; j++) {
                std::cout<<Pok[i][j]<<" ";
            }
            std::cout<<std::endl;
        }
        delete[] Pok[0];
        delete[] Pok;
    } catch(std::domain_error izuzetak) {
        std::cout<<"Izuzetak: "<<izuzetak.what()<<std::endl;
    } catch(...) {
        //delete[] Pok[0];
        delete[] Pok;
        std::cout<<"Izuzetak: Nedovoljno memorije!"<<std::endl;
    }

    return 0;
}
