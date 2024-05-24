//TP 2018/2019: Ispit 1, Zadatak 1
#include <iostream>
#include <vector>
#include <stdexcept>
#include <algorithm>
#include<list>

bool JeLiPravilna(const std::vector<std::vector<double>> &Matrica)
{
    if(Matrica.size() == 0) return true;
    for(int i = 0; i < Matrica.size() - 1; i++) {
        for(int j = i + 1; j < Matrica.size(); j++){
            if(Matrica[i].size() != Matrica[j].size()) return false;
        }
        
    }
    return true;
}
std::list<bool> TransformirajMatricu(std::vector<std::vector<double>> &Matrica)
{

    if(!JeLiPravilna(Matrica)) throw std::domain_error ("Parametar nema formu matrice");
    std::list<bool> Lista;
    for(int i = 0; i < Matrica.size()/2; i++) {
        //auto sprijeda = Matrica[i];
        //auto szada = Matrica[Matrica.size() - i - 1];
        std::swap(Matrica[i], Matrica[Matrica.size() - i - 1]);
    }
    int duzina = 0;
    if(Matrica.size() != 0) duzina = Matrica[0].size();
    for(int i = 0; i < duzina; i++) {
        double suma = 0;
        for(int j = 0; j < Matrica.size(); j++) {
            suma += Matrica[j][i];
        }

        if(int (suma) == suma) {
            Lista.push_back(true);
        } else Lista.push_back(false);
    }
    return Lista;
}
int main ()
{
    int n,m;

    std::cout<<"Unesite broj redova: ";
    std::cin>>n;
    std::cout<<"Unesite broj kolona: ";
    std::cin>>m;
    std::vector<std::vector<double>> Matrica(n);
    std::cout<<"Unesite elemente matrice: ";
    for(int i = 0; i< n; i ++) {
        for(int j = 0; j < m; j++) {
            double broj;
            std::cin>>broj;
            Matrica[i].push_back(broj);
        }
    }
    auto lista = TransformirajMatricu(Matrica);
    std::cout<<"Transformirana matrica:";
    for(int i = 0; i < n; i++) {
        for(int j = 0; j < m; j++) {
            std::cout<<Matrica[i][j]<<" ";
        }
        std::cout<<std::endl;
    }

    std::cout<<"Rezultujuca lista: ";

    for(auto i = lista.begin(); i != lista.end(); i++) {
        
        std::cout<<std::boolalpha <<*i<<" ";
    }
    return 0;
}
