//TP 2018/2019: Tutorijal 3, Zadatak 6
#include <iostream>
#include <vector>
#include <iomanip>
typedef std::vector<std::vector<int>> Matrica;
int SirinaBroja(int x)
{
    int brojCifara=0;
    if(x<0) {
        brojCifara++;
        x=abs(x);
    }
    do {
        brojCifara++;
        x=x/10;
    } while(x!=0);
    return brojCifara;
}

Matrica KroneckerovProizvod(std::vector<int> v1, std::vector<int> v2)
{
    Matrica m(v1.size(), std::vector<int>(v2.size()));
    for(int i=0; i<v1.size(); i++) {
        for(int j=0; j<v2.size(); j++)
            m[i][j]=v1[i]*v2[j];
    }
    return m;
}
int NajvecaSirina(Matrica m){
    int max=0, pomocna;
    if(m.size()!=0 && m[0].size()!=0)max=SirinaBroja(m[0][0]);
    for(int i=0; i<m.size(); i++){
        for(int j=0; j<m[i].size(); j++){
            if(SirinaBroja(m[i][j])>max) max=SirinaBroja(m[i][j]);
        }
    }
    return max;
}
int main ()
{
    // int broj;
    // std::cin>>broj;
    // std::cout<<SirinaBroja(broj);
    std::cout<<"Unesite broj elemenata prvog vektora: ";
    int brojElemenata1;
    std::cin>>brojElemenata1;
    std::vector<int>v1;
    std::cout<<"Unesite elemente prvog vektora: ";
    int broj;
    for(int i=0; i<brojElemenata1; i++) {
        std::cin>>broj;
        v1.push_back(broj);
    }
    std::cout<<"Unesite broj elemenata drugog vektora: ";
    int brojElemenata2;
    std::cin>>brojElemenata2;
    std::vector<int>v2;
    std::cout<<"Unesite elemente drugog vektora: ";
    for(int i=0; i<brojElemenata2; i++) {
        std::cin>>broj;
        v2.push_back(broj);
    }
    Matrica mat(brojElemenata1, std::vector<int>(brojElemenata2));
    mat=KroneckerovProizvod(v1, v2);
    //int najsiri=NajvecaSirina(mat)+1;
    std::cout<<std::endl;
    for(int i=0; i<brojElemenata1; i++){
        for(int j=0; j<brojElemenata2; j++){
            std::cout<<std::right<<std::setw(NajvecaSirina(mat)+1)<<mat.at(i).at(j);
        }
        std::cout<<std::endl;
    }

    return 0;
}
