//TP 2018/2019: Ispit 1, Zadatak 4
#include <iostream>
#include <new>
#include <vector>
#include <stack>
#include <type_traits>
//typedef std::vector<std::stack<int>> VekStekova
int BrojElemenata(const std::vector<std::stack<int>> &vek){
    int brEl = 0;
    for(int i = 0; i < vek.size(); i++){
        brEl += vek[i].size(); 
    }
    return brEl;
}
int **NapraviDinamickuKopiju(std::vector<std::stack<int>> &vek){
    int **DupliPok = nullptr;
    auto brEl = BrojElemenata(vek);
    try{
        DupliPok = new int *[vek.size()]{};
        DupliPok[0] = new int[brEl]{};
        for(int i = 1; i < vek.size(); i++){
            DupliPok[i] = DupliPok[i-1] + vek[i - 1].size();
        }
        for(int i = 0; i < vek.size(); i++){
            auto duzina = vek[i].size();
            for(int j = duzina - 1; j >= 0; j--){
                //std::cout<<vek[i].top()<<" ";
                int broj = vek[i].top();
                DupliPok[i][j] = broj;
                vek[i].pop();
                if(vek[i].size() == 0) break;
            }
        }
        
    }
    catch(...){
        delete[] DupliPok[0];
        delete DupliPok;
    }
    return DupliPok;
}
int main ()
{
    //AT3

try {
    std::vector<std::stack<int>> M(5);
    for(int i = 0; i < 5; i++) {
      for(int j = 0; j <= i; j++) {
        M[i].push(j);
      }
    }
    auto m = NapraviDinamickuKopiju(M);
    
    for(int i = 0; i < M.size(); i++) {
        std::cout<<"DUZINA"<<M[i].size()<<std::endl;
      for(int j = 0; j < M[i].size(); j++)
        std::cout << m[i][j] << " ";
      std::cout << std::endl;
    }
    delete[] m[0];
delete[] m;
  }
  catch(...) {
    std::cout << "GRESKA!";
  }
	return 0;
}