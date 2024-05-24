//TP 2018/2019: Tutorijal 2, Zadatak 2
#include <iostream>
#include <vector>
bool TestPerioda(std::vector<double> v, int p){
    bool periodican=true;
    if(p<1 || p>=v.size()) {
        periodican=false;
        return periodican;
    }
    for(int i=0; i<v.size()-p; i++) {
       // std::cout<<i<<" ";
        if(v[i]!=v[i+p]) {
            periodican=false;
            break;
        }
    }
    //if(int(v.size())-p==0) periodican=false;
    return periodican;
}
int OdrediOsnovniPeriod(std::vector<double>v)
{
    int periodican=0;
    for(int i=0; i<v.size(); i++) {
        if(i>0 && TestPerioda(v, i)==true) {
            periodican=i;
            break;
        }
    }
    return periodican;
}
int main ()
{
    std::vector<double> v;
    double broj;
    std::cout<<"Unesite slijed brojeva (0 za kraj): ";
    for(;;) {
        std::cin>>broj;
        if(broj==0) break;
        v.push_back(broj);
    }
    if(OdrediOsnovniPeriod(v) != 0)std::cout<<"Slijed je periodican sa osnovnim periodom "<<OdrediOsnovniPeriod(v)<<".";
    else std::cout<<"Slijed nije periodican!";
    // std::vector<double> v1 (1000, 7.7);
//std::cout << OdrediOsnovniPeriod(v1) << std::endl; //1
    // std::cout << std::boolalpha << TestPerioda({1, 2, 3, 1, 2}, 2) << " "
    //           << TestPerioda({1, 2, 3, 1, 2}, 3) << " "
    //           << TestPerioda({1, 2, 3, 1, 2, 3}, 2) << " "
    //           << TestPerioda({1, 2, 3, 1, 2, 5, 1}, 4) << " "
    //           << TestPerioda({1, 2, 3, 1, 2, 5, 1}, 6) << " "
    //           << TestPerioda({1}, 1) << " "
    //           << TestPerioda({1}, 2) << " "
    //           << TestPerioda({1}, 0);
    return 0;
}
