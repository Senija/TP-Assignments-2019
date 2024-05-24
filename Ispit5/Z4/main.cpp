//TP 2018/2019: Ispit 5, Zadatak 4
#include <iostream>
#include <vector>
#include <vector>
#include <deque>
#include <string>
#include <list>
template<typename Tip1, typename Tip2>

auto ZbirKontejnera(const Tip1 &k1, const Tip2 &k2)-> std::vector<decltype(*(k1.begin()) + *(k2.begin()))>
{
    std::vector<decltype(*(k1.begin()) + *(k2.begin()))> novi;
   
    int brojac = 0;
    if(k1.size() >= k2.size()) {
        auto it = k2.begin();
        for(auto i = k1.begin(); i != k1.end(); i++) {
            if(brojac < k2.size()) {
                auto broj = *i + *it;
                novi.push_back(broj);
                it++;
                brojac++;
            } else {
                novi.push_back(*i);
            }

        }

    } else {
        auto it = k1.begin();
        for(auto i = k2.begin(); i != k2.end(); i++) {
            if(brojac < k1.size()) {
                auto broj = *i + *it;
                novi.push_back(broj);
                it++;
                brojac++;
            } else {
                novi.push_back(*i);
            }

        }

    }
    return novi;
}

int main ()
{
    std::vector<int> v{4,4,4,4};
    std::list<int> l{4,4,4,4};
    auto v1 = ZbirKontejnera(v,l);
    for(int x :v1) std::cout<<x<<" ";
    return 0;
}
