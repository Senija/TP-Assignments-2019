//TP 2018/2019: Ispit 1, Zadatak 3
#include <iostream>
#include <string>
#include <iterator>
// int OgradiRijec(std::string &recenica, int n)
// {
//     if(n<1) throw std::range_error ("Nekorektan redni broj rijeci");
//     bool razmak = true;
//     int br_rijeci=0;
//     for(int i=0; i<recenica.length(); i++) {
//         if(recenica.at(i) ==' ') {
//             razmak = true;
//         } else if(razmak) {
//             razmak = false;
//             br_rijeci++;
//             if(br_rijeci == n) {
//                 recenica.insert(i, "(");
//                 for(int j = i; j != recenica.length(); j++) {
//                     if(recenica.at(j) ==' ') {
//                         recenica.insert(j, ")");
//                         break;
//                     }
//                 }
//             }
//         }
//     }
//     //if(n>br_rijeci) throw std::range_error ("Nema toliko rijeci u tom stringu!");
//     return br_rijeci;
// }
int OgradiRijec(std::string &recenica, int n)
{
    if(n <= 0) throw  std::range_error ("Nekorektan redni broj rijeci");
    int br_rijeci = 0;
    for(int i = 0; i < recenica.length(); i++) {
        if(recenica.at(i) == ' ') continue;
        else {
            br_rijeci++;
            if(br_rijeci == n) {
                recenica.insert(i, "(");

                while(recenica[i] != ' ') {
                    i++;
                }
                recenica.insert(i, ")");
            }
            else{
                while(recenica[i] != ' ') {
                    i++;
                    if(i == recenica.length() - 1) break;
                }
            }
        }
    }
    if(n > br_rijeci) throw std::range_error ("Nekorektan redni broj rijeci");
    return br_rijeci;
}
int main ()
{
int br_rijeci;
    try {
        std::string recenica;
        std::cout<<"Unesite string: ";
        std::getline(std::cin, recenica);
        //std::cin.ignore(10000, '\n');
        
        std::cout<<"Redni broj rijeci: ";
        std::cin>>br_rijeci;

        auto ispisi = OgradiRijec(recenica, br_rijeci);
        //if(ispisi < br_rijeci) std::cout<<"Nema toliko rijeci u tom stringu!";
        
            std::cout<<"Modificirani string:";
            std::cout<<recenica;
            std::cout<<std::endl<<"Broj rijeci: "<<ispisi;
    } catch(std::range_error iz) {
        if(br_rijeci >= 1) std::cout<<"Nema toliko rijeci u tom stringu!";
        else std::cout<<iz.what() <<std::endl;
    }
    return 0;
}
