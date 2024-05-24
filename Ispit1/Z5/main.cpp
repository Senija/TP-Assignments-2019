//TP 2018/2019: Ispit 1, Zadatak 5
#include <iostream>
#include <string>
#include <deque>
#include <algorithm>
int main ()
{
    // std::deque<std::string> DekS(5);
    // std::cout<<"Unesite 5 recenica: ";
    // for(int i=0; i<5; i++) {
    //     std::getline(std::cin, DekS.at(i));
    //     // std::cin.ignore(1000, '\n');
    // }
    // std::cin.ignore(1000, '\n');
    // int br_samo;
    // std::cout<<"Unesite dozvoljeni broj samoglasnika: ";
    // std::cin>>br_samo;
    // std::copy_if(DekS.begin(), DekS.end(), DekS.begin(), [br_samo](std::string recenica) {
    //     int samoglasnici = 0;
    //     for(int i=0; i!=recenica.length(); i++) {
    //         if(recenica.at(i) == 'A' || recenica.at(i) == 'E'|| recenica.at(i) == 'I' || recenica.at(i) == 'O'|| recenica.at(i) == 'U'||recenica.at(i) == 'a'||recenica.at(i) == 'e'||recenica.at(i) == 'i'||recenica.at(i) == 'o'||recenica.at(i) == 'u') {
    //             samoglasnici++;
    //         }
    //     }
    //     if(samoglasnici > br_samo) return false;
    //     else return true;
    // });
    // std::cout<<"Preostale recenice:"<<std::endl;
    // for(int i=0; i!=DekS.size(); i++) std::cout<<DekS.at(i)<<std::endl;
    std::deque<std::string> Dek(5);
    std::cout<<"Unesite 5 recenica: ";
    for(int i = 0; i < 5; i++){
        std::getline(std::cin, Dek[i]);
    }
    int brS;
    std::cout<<"Unesite dozvoljeni broj samoglasnika: ";
    std::cin >> brS;
    std::deque<std::string> Modificirani(5);
    std::copy_if(Dek.begin(), Dek.end(), Modificirani.begin(), [brS](std::string rec){
        auto brojac = std::count_if(rec.begin(), rec.end(), [brS](char s){
            return s == 'a' || s == 'e' || s == 'i' || s == 'o' || s == 'u' || s == 'A' || s == 'E' || s == 'I' || s == 'O' || s == 'U';
        });
        return brojac <= brS;
    });
    std::cout<<"Preostale recenice:"<<std::endl;
    for(int i = 0; i < 5; i++){
        if(Modificirani[i].size() == 0){
            Modificirani.resize(i);
            break;
        }
        else{
            std::cout<<Modificirani[i]<<std::endl;
        }
    }
    
    
    // for(int i=0; i!=DekS.size(); i++) std::cout<<DekS.at(i)<<std::endl;
    return 0;
}
