#include <iostream>

class NeobicnaKlasa{
    int broj;
    public:
    explicit NeobicnaKlasa(int broj){
        NeobicnaKlasa::broj = broj;
        std::cout<<"Direktna inicijalizacija"<<std::endl;
    }
    NeobicnaKlasa(double broj){
        NeobicnaKlasa::broj = broj;
        std::cout<<"Kopirajuca inicijalizacija";
    }
    
};
int main ()
{
    NeobicnaKlasa k1(5); // Proizvodi ispis "Direktna inicijalizacija"
    NeobicnaKlasa k2 = 5;
	return 0;
}