//TP 2018/2019: Tutorijal 4, Zadatak 5
#include <iostream>
#include <vector>
template<typename ProizvoljanTip>
std::vector<ProizvoljanTip> Presjek(std::vector<ProizvoljanTip> &v1, std::vector<ProizvoljanTip> &v2)
{
    std::vector<ProizvoljanTip> presjek;
    for(int i=0; i<v1.size(); i++) {
        for(int j=0; j<v2.size(); j++) {
            if(v1.at(i)==v2.at(j)) {
                presjek.push_back(v1.at(i));
            }
        }
    }
    for(int i=0; i<presjek.size(); i++) {
        for(int j=i+1; j<presjek.size(); j++) {
            if(presjek.at(i)==presjek.at(j)) {
                presjek.erase(presjek.begin()+j);
                j--;
            }
        }
    }
    return presjek;
}
int main ()
{

    std::cout<<"Test za realne brojeve..."<<std::endl;
    int brElemenataPrvi;
    std::cout<<"Unesite broj elemenata prvog vektora: ";
    std::cin>>brElemenataPrvi;
    std::vector<double> v1(brElemenataPrvi);
    std::cout<<"Unesite elemente prvog vektora: ";
    for(int i=0; i<brElemenataPrvi; i++) {
        std::cin>>v1.at(i);
    }
    int brElemenataDrugi;
    std::cout<<"Unesite broj elemenata drugog vektora: ";
    std::cin>>brElemenataDrugi;
    std::vector<double> v2(brElemenataDrugi);
    std::cout<<"Unesite elemente drugog vektora: ";
    for(int i=0; i<brElemenataDrugi; i++) {
        std::cin>>v2.at(i);
    }
    auto presjek_vektora=Presjek(v1, v2);
    std::cout<<"Zajednicki elementi su: ";
    for(int i=0; i<presjek_vektora.size(); i++) {
        if(i==presjek_vektora.size()-1) std::cout<<presjek_vektora.at(i);
        else std::cout<<presjek_vektora.at(i)<<" ";
    }
    std::cout<<std::endl<<"Test za stringove..."<<std::endl;
    int brElemenataString1;
    std::cout<<"Unesite broj elemenata prvog vektora: ";
    std::cin>>brElemenataString1;
    std::cin.ignore(10000, '\n');
    std::vector<std::string> v1Sting;
    std::cout<<"Unesite elemente prvog vektora (ENTER nakon svakog unosa): ";
    for(int i=0; i<brElemenataString1 ; i++) {

        std::string pomocna; 
        std::getline(std::cin, pomocna);
        std::cin.clear();
        v1Sting.push_back(pomocna);

        
    }
    int brElemenataString2;
    std::cout<<"Unesite broj elemenata drugog vektora: ";
    std::cin>>brElemenataString2;
    std::vector<std::string> v2Sting;
    std::cin.ignore(10000, '\n');
    std::cout<<"Unesite elemente drugog vektora (ENTER nakon svakog unosa): ";
    for(int i=0; i<brElemenataString2 ; i++) {

        std::string pomocna;
        std::getline(std::cin, pomocna); 
        std::cin.clear();
        v2Sting.push_back(pomocna);
    }
    auto presjek_string=Presjek(v1Sting, v2Sting);
    std::cout<<"Zajednicki elementi su:"<<std::endl;
    for(int i=0; i<presjek_string.size(); i++){
        if(i==presjek_string.size()-1) std::cout<<presjek_string.at(i);
        else std::cout<<presjek_string.at(i)<<std::endl;
    }

    return 0;
}
