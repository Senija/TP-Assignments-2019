//TP 2018/2019: ZSR 1, Zadatak 4
#include <iostream>
#include <vector>
typedef std::vector<std::vector<double>> Matrica;
void Obrnuto(Matrica mat, double &MiniMaxi, double &MaxiMini)
{
    //da li je matrica
    //if(mat.size() != 0)double Max = mat.at(0).at(0);
    // double max_reda = mat.at(0).at(0);
    // double min_reda = mat.at(0).at(0);
    for(int i = 0; i<mat.size(); i++) {
        double max_reda = mat.at(i).at(0);
        double min_reda = mat.at(i).at(0);
        for(int j =0; j<mat.at(i).size(); j++) {
            if(mat.at(i).at(j) > max_reda) max_reda = mat.at(i).at(j);
            if(mat.at(i).at(j) < min_reda) min_reda = mat.at(i).at(j);
        }
        if(i == 0) {
            MiniMaxi = max_reda;
            MaxiMini = min_reda;
        } 
        else {
            if(max_reda < MiniMaxi) MiniMaxi = max_reda;
            if(min_reda > MaxiMini) MaxiMini = min_reda;
        }

    }
}
int main ()
{
    Matrica vat = {{-9,15,6}, {19, -5,7}, {-1 , -1, -1}};
    double MiniMaxi = 0, MaxiMini = 0;
    Obrnuto(vat, MiniMaxi, MaxiMini);
    std::cout<<MiniMaxi<<" "<<MaxiMini;
    return 0;
}
