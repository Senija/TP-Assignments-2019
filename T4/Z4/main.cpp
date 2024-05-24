//TP 2018/2019: Tutorijal 4, Zadatak 4
#include <iostream>
#include <string>
template<typename ProizvoljniBrojcaniTip>
void UnosBroja(const std::string &ulaz, const std::string &upozorenje, ProizvoljniBrojcaniTip &x)
{
    ProizvoljniBrojcaniTip pomocna;
    for(;;) {
        std::cout<<ulaz;
        std::cin>>pomocna;
        if(std::cin.peek()!='\n' || !(std::cin)) {  
            std::cout<<upozorenje<<std::endl;
            std::cin.clear();
            std::cin.ignore(1000, '\n');
        }
        else if(std::cin){
            x=pomocna;
             break;
        }

    }
    //return x;
}
int main ()
{
    double baza;
    int eksponent;
    UnosBroja("Unesite bazu: \n", "Neispravan unos, pokusajte ponovo...\n", baza);
    UnosBroja("Unesite cjelobrojni eksponent: \n", "Neispravan unos, pokusajte ponovo...\n", eksponent);
    double rezultat=1;;
    for(int i=0; i<std::abs(eksponent); i++){
        if(eksponent<0){
            rezultat*=1./baza;
        }
        else rezultat*=baza;
    }
    std::cout <<baza<<" na "<<eksponent<<" iznosi "<<rezultat<< std::endl;
    return 0;
}
