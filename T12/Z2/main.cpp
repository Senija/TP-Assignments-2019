#include <iostream>
#include <set>
#include <iterator>
#include <algorithm>
#include <utility>

template<typename Tip>
std::set<Tip> operator +(const std::set<Tip> &skup1, const std::set<Tip> &skup2)
{
    std::set<Tip> UnijaSkupova;
    for(auto i=skup1.begin(); i!=skup1.end(); i++) {
        UnijaSkupova.insert(*i);
    }
    for(auto i=skup2.begin(); i!=skup2.end(); i++) {
        UnijaSkupova.insert(*i);
    }
    return UnijaSkupova;
}
template<typename Tip>
std::set<Tip> &operator +=(std::set<Tip> &skup1, const std::set<Tip> &skup2)
{
    //std::set<Tip> UnijaSkupova;
    for(auto i=skup2.begin(); i!=skup2.end(); i++) {
        skup1.insert(*i);
    }
    return skup1;
}
template<typename Tip>
std::set<Tip> operator *(const std::set<Tip> &skup1, const std::set<Tip> &skup2)
{
    std::set<Tip> PresjekSkupova;
    for(auto i = skup1.begin(); i != skup1.end(); i++) {
        if(std::binary_search(skup2.begin(), skup2.end(), *i)) PresjekSkupova.insert(*i);
    }
    return PresjekSkupova;
}
template<typename Tip>
std::set<Tip> &operator *=(std::set<Tip> &skup1, const std::set<Tip> skup2)
{
    auto pomocna = skup1;
    for(auto i = pomocna.begin(); i != pomocna.end(); i++) {
        if(!std::binary_search(skup2.begin(), skup2.end(), *i)) skup1.erase(*i);
    }
    return skup1;
}
template<typename Tip>
std::ostream &operator <<(std::ostream &tok, const std::set<Tip> &skup)
{
    tok<<"{";
    for(auto i = skup.begin(); i != skup.end(); i++) {
        if(i != skup.begin()) tok<<",";
        tok<<*i;
    }
    tok<<"}";
    return tok;
}
template<typename Tip1, typename Tip2>
std::set<std::pair<Tip1, Tip2>> operator %(const std::set<Tip1> &skup1, const std::set<Tip2> &skup2)
{
    std::set<std::pair<Tip1, Tip2>> DekartovProizvod;
    for(auto i = skup1.begin(); i != skup1.end(); i++) {
        for(auto j = skup2.begin(); j != skup2.end(); j++) {
            DekartovProizvod.insert(std::make_pair(*i, *j));
        }
    }
    return DekartovProizvod;
}
template<typename Tip1, typename Tip2>
std::ostream &operator <<(std::ostream &tok, const std::set<std::pair<Tip1, Tip2>> &DekProizvod)
{
    tok<<"{";
    for(auto i = DekProizvod.begin(); i != DekProizvod.end(); i++) {
        if(i != DekProizvod.begin()) tok<<",";
        tok<<"("<<i->first<<","<<i->second<<")";
    }
    tok<<"}";
    return tok;
}


int main ()
{
//AT4 testiranje Dekartovog proizvoda
std::set<char> s3{'A', 'B'};
std::set<int> s4{1, 2, 3};
std::cout << s3 % s4 << std::endl;
    return 0;
}
