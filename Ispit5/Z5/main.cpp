//TP 2018/2019: Ispit 5, Zadatak 5
#include <iostream>
#include <new>
#include <stdexcept>

void KreirajPascalovTrougao(int **(&A), int n)
{
    if(n <= 0) throw std::domain_error ("Pogresan broj redova");
    int **a = nullptr;
    try {
        a= new int*[n];
        a[0] = new int[n * (n+1)/2];
        for(int i = 1; i < n; i++) {
            a[i] = a[i-1] +i;
        }

        for(int i = 0; i < n; i++) {
            for(int j = 0; j < i+1; j++) {
                if(i == 0) a[i][j] = 1;
                else if(j == 0 || j == i ) a[i][j] = 1;
                else {
                    if(i != 0 && j != 0) a[i][j] = a[i -1][j] + a[i-1][j-1];
                }
            }
        }




    } catch(...) {
        //delete[] a[0];
        //a[0] = nullptr;
        delete[] a;
        a = nullptr;
        throw std::range_error ("Kreiranje nije uspjelo");
    }
    A = a;
}
int main ()
{
    try {
        int n;
        std::cout<<"Broj redova: ";
        std::cin>>n;
        int **A = nullptr;
        KreirajPascalovTrougao(A,n);
        for(int i = 0; i < n; i++) {
            for(int j = 0; j <= i; j++) {
                std::cout<<A[i][j]<<" ";
            }
            std::cout<<std::endl;
        }

        delete[] A[0];
        delete[] A;
    }
    catch(std::range_error e) {std::cout<<"Problem: "<<e.what()<<"!"<<std::endl;}
    catch(std::domain_error e) {std::cout <<"Problem: "<<e.what()<<"!";}

                                             return 0;
}
