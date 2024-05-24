//TP 2018/2019: ZSR 2, Zadatak 9
#include <iostream>
#include <vector>

template<typename IterTip1, typename IterTip2>
IterTip1 DaLiJeDrugiUPrvom(IterTip1 pocetak1, IterTip1 kraj1, IterTip2 pocetak2, IterTip2 kraj2)
{
    for(auto i=pocetak1; i != kraj1; i++) {
        IterTip1 pomocna;
        if(*i == *pocetak2) {
            pomocna = i;
            while(*i == *pocetak2) {
                if(pocetak2 == kraj2) break;
                pocetak2++;
                i++;
                //brojac++;
            }
            if(pocetak2 == kraj2) return pomocna;
            if(pocetak2 != kraj2) return kraj1;
        }
    }
    return kraj1;
}

int main ()
{
    std::vector<int>v1 = {1, 7, 3, 5,2,6};
    std::vector<int> v2 = {3,5,4};
    std::cout<<*DaLiJeDrugiUPrvom(v1.begin(), v1.end(), v2.begin(), v2.end());
    return 0;
}
