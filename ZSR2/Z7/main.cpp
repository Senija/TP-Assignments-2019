//Periodican, Zadatak 7
#include <iostream>
#include <list>
#include <iterator>
//ono epsilon mamu mu

int PeriodListe(std::list<double> lista)
{
    std::list<double>::iterator it = lista.begin();
    it++;
    for(auto i = lista.begin(); i != lista.end(); i++) {
        while(*i == *it) {
            i++;
            it++;
        }
        if(it == lista.end()) {
            if(std::distance(i, it) != lista.size()) return std::distance(i, it);
            else return 0;
        } else {
            i = lista.begin();
            i--;
            it++;
        }
    }
    // else {
    //     i--;
    //     it++;
    // }
    return 0;
}
int main ()
{
    std::list<double> lista = {5, 9, 5, 9, 5,9};
    std::cout<<PeriodListe(lista);
    return 0;
}
