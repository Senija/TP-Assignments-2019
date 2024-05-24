//TP 2018/2019: ZSR 1, Zadatak 7
#include <iostream>
#include <iterator>
#include <algorithm>
#include <vector>
#include <string>
template<typename IterTip1, typename IterTip2>
IterTip2 KopirajBezDuplikata(IterTip1 pocetak, IterTip1 iza_kraja, IterTip2 odrediste){
    auto vrati = std::remove_copy_if(pocetak, iza_kraja, odrediste, [pocetak, iza_kraja](typename std::remove_reference<decltype(*pocetak)>::type element){
            if(std::count(pocetak, iza_kraja, element) == 1) return false;
            else return true;
    });
    return vrati;
}
int main ()
{
    std::vector<int> v1 = {1,1,1,1,2,2,2,3,3,4};
    std::vector<int> v2(v1.size());
    typename std::vector<int>::iterator it1 = v2.begin();
    auto it = KopirajBezDuplikata(v1.begin(), v1.end(), v2.begin());
    for(auto i = it1; i != it; i++) std::cout<<*i;
	return 0;
}