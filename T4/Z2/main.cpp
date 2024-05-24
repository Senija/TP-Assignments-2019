//TP 2018/2019: Tutorijal 4, Zadatak 2
#include <iostream>
#include <string>
void Zamijeni(char& a, char& b){
    char pomocna=a;
    a=b;
    b=pomocna;
}
void IzvrniString(std:: string& recenica){
    for(int i=0; i<recenica.length()/2; i++){
            Zamijeni(recenica.at(i), recenica.at(recenica.length()-1-i));
    }
}
int main ()
{
    std::string recenica;
    std::cout<<"Unesi string: ";
    std::getline(std::cin, recenica);
    IzvrniString(recenica);
    std::cout<<"Izvrnuti string je: "<< recenica;
	return 0;
}