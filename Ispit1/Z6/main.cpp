//TP 2018/2019: Ispit 1, Zadatak 6
#include <iostream>
#include <functional>
#include <list>
#include <vector>
template<typename TipE>
TipE Mapiraj(const TipE &Kontejner, std::function<decltype(*Kontejner.begin() + *Kontejner.begin()) (decltype(*Kontejner.begin() + *Kontejner.begin()))> funk){
    TipE novi;
    //auto it = novi.begin();
    for(auto i = Kontejner.begin(); i != Kontejner.end(); i++){
        auto value = funk(*i);
        int brojac = 0;
        novi.insert(brojac, value);
        brojac++;
    }
    return novi;
}
int main ()
{
     //AT3
    std::list<int> lista{3, 6, 1, 4, 2};
    auto funkcija = [] (int i) {return (i-1);};
    std::list<int> rezultujuca = Mapiraj(lista, funkcija);
    for (auto i : rezultujuca)
    {
        std::cout << i << " ";
    }
    
	return 0;
}