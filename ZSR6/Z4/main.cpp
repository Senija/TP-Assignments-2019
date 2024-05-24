//TP 2018/2019: ZSR 6, Zadatak 4
#include <iostream>
#include <cmath>
#include<iomanip>
#include <string>
#include <algorithm>

int main() {
    std::string s = "KAZMVAPJAZWVCVCQKZMHJYSWHMSWHCKYJMSWEMUWVWQMRBWQC";
    // for(auto i = 'A'; i <= 'Z'; i++){
    //     std::cout<<"Slovo "<<i<<" se pojavljuje "<< std::count(s.begin(), s.end(), i)<<" puta."<<std::endl;
    // }
    std::string desifrovanaPoruka;
    for(auto i = s.begin(); i != s.end(); i++){
        double temp = (-3**i + 1)/26.;
        desifrovanaPoruka.push_back(65 + ((-3**i + 1) - 26 * std::floor(temp)));
    }
    std::cout<<desifrovanaPoruka<<std::endl;
    return 0;
}
