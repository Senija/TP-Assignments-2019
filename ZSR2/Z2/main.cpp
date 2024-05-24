//TP 2018/2019: ZSR 2, Zadatak 2
#include <iostream>

int BrElemenataGrbava (int n)
{

    int brojac = 0;
    for(int i=0; i<n+1; i++) {
        for(int j=0; j<i+1; j++)
            brojac++;
    }
    return brojac;
}
int main(){
    int n = 5;
    int pomocna = n*(n+1)/2 +(n+1);
    std::cout<<pomocna <<std::endl;
    std::cout<<BrElemenataGrbava(5);
    return 0;
    

}