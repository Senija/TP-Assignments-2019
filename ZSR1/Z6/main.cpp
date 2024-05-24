//TP 2018/2019: ZSR 1, Zadatak 6
#include <iostream>
#include <string>

char BezeF(char znak){
    return znak+1;
}

//template <typename FunTip>
void FreakyFunkcija(std::string &recenica, char(*PokNaF)(char)){
    for(int i=0; i<recenica.length(); i++){
        if(recenica.at(i) != ' '){
            recenica.at(i) = PokNaF(recenica.at(i));
        }
    }
}
int main ()
{
    std::string recenica = "ABCDE"; //F
    FreakyFunkcija(recenica, BezeF); //[](char znak) {return znak+1;}
    std::cout<<recenica;
	return 0;
}