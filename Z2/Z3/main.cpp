//TP 2018/2019: Zadaća 2, Zadatak 3
#include <iostream>
#include <vector>
#include <iomanip>

long long int **StirlingoviBrojeviF(int n)
{

    if(n<0) throw std::domain_error ("Parametar ne smije biti negativan");


    long long int **DupliPok; // = nullptr;
    try {
        DupliPok = nullptr;
        DupliPok = new long long int*[n+1];
        try {
            for(int i=0; i<n+1; i++) {
                DupliPok[i] = nullptr;
                DupliPok[i] = new long long int [i+1];
            }

            DupliPok[0][0] = 1;

            for(int i=1; i<n+1; i++) {
                DupliPok[i][0] = 0;
                for(int j=1; j<i+1; j++) {
                    //if(i==0 && j==0)

                    if(j>i-1) DupliPok[i][j] = DupliPok[i-1][j-1];
                    else DupliPok[i][j] = DupliPok[i-1][j-1] + j * DupliPok[i-1][j];

                }
            }

        } catch(...) {
            throw;
        }
    } catch(...) {
        for(int i=0; i<n+1; i++) delete[] DupliPok[i];
        delete[] DupliPok;
        throw std::range_error ("Parametar prevelik za raspolozivu memoriju");
    }
    return DupliPok;
}

long long int **StirlingoviBrojeviK(int n)
{

    if(n<0) throw std::domain_error ("Parametar ne smije biti negativan");

    long long int **DupliPok = nullptr;
    try {
        DupliPok = new long long int*[n+1];
        DupliPok[0] = nullptr;
        try {
            DupliPok[0] = new long long int[n*(n+1)/2 + (n+1)];
            //try{
            for(int i=1; i<n+1; i++) {
                DupliPok[i] = nullptr;
                DupliPok[i] = DupliPok[i-1] +i;
            }
            DupliPok[0][0] = 1;
            for(int i=1; i<n+1; i++) {
                DupliPok[i][0] = 0;
                for(int j=1; j<i+1; j++) {
                    if(j> i-1) DupliPok[i][j] = DupliPok[i-1][j-1];
                    else DupliPok[i][j] = DupliPok[i-1][j-1] + j * DupliPok[i-1][j];

                }
            }

        } catch(...) {
            throw;
        }
    } catch(...) {
        delete[] DupliPok[0];
        delete[] DupliPok;
        throw std::range_error ("Parametar prevelik za raspolozivu memoriju");
    }
    return DupliPok;
}
int SirinaBroja(long long int broj)
{
    int brojacCif = 0;
    do {

        broj = broj/10;
        brojacCif ++;

    } while(broj != 0);
    return brojacCif;
}
int NajsiriBroj(long long int **DupliPok, int br_redova)
{
    if(br_redova < 0) throw std::domain_error ("Parametar ne smije biti negativan");
    auto max_cifara = 0;
    if(br_redova >= 0) {
        for(int j=0; j<br_redova+1; j++) {
            if(SirinaBroja(DupliPok[br_redova][j]) >max_cifara) max_cifara = SirinaBroja(DupliPok[br_redova][j]);

        }

    }
    return max_cifara+1;
}

int main ()
{
    int n;
    std::cout<<"Unesite broj n: ";
    std::cin>>n;
    try {
        auto DupliPokF = StirlingoviBrojeviF(n);
        std::cout<<std::endl<<"Stirlingovi brojevi - fragmentirana alokacija:"<<std::endl;
        for(int i=0; i<n+1; i++) {
            for(int j=0; j<i+1; j++) {
                //std::cout<<"////"<<NajsiriBroj(DupliPokF, n)+1<<"//////"<<std::endl;
                std::cout<<std::fixed<<std::setw(NajsiriBroj(DupliPokF, n))<<DupliPokF[i][j];  //NajsiriBroj(DupliPokF, n) + 1
            }
            std::cout<<std::endl;
        }
        for(int i=0; i<n+1; i++) delete[] DupliPokF[i];
        delete[] DupliPokF;

        //std::cout<<"vvvv "<<BrElemenataGrbava(5);

        auto DupliPokK = StirlingoviBrojeviK(n);
        std::cout<<std::endl<<"Stirlingovi brojevi - kontinualna alokacija:"<<std::endl;
        for(int i=0; i<n+1; i++) {
            for(int j=0; j<i+1; j++) {
                std::cout<<std::fixed<<std::setw(NajsiriBroj(DupliPokK, n))<<DupliPokK[i][j]; //NajsiriBroj(DupliPokK, n) + 1
            }
            std::cout<<std::endl;
        }
        delete[] DupliPokK[0];
        delete[] DupliPokK;
    } catch (std::domain_error izuzetak) {
        std::cout<<"Izuzetak: "<<izuzetak.what()<<"!"<<std::endl;
    } catch(std::range_error izuzetak) {
        std::cout<<"Izuzetak: "<<izuzetak.what()<<"!"<<std::endl;
    }

    return 0;
}