//TP 2018/2019: Tutorijal 3, Zadatak 7
#include <iostream>
#include <vector>
#include <iomanip>
#include <stdexcept>
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
Matrica PascalovTrougao(int n)
{
    if(n<0) throw std::domain_error("Broj redova ne smije biti negativan");

    Matrica grbava(n);
    for(int i=0; i<n; i++) {
        grbava[i].resize(i+1);
        for(int j=0; j<i+1; j++) {
            if(j==0 || i==j) grbava[i][j]=1;
            else grbava[i][j]=grbava[i-1][j]+grbava[i-1][j-1];
        }
    }
    return grbava;
}
int NajvecaSirina(Matrica m)
{
    int max=0;
    if(m.size()!=0 && m[0].size()!=0) max=SirinaBroja(m[0][0]);
    for(int i=0; i<m.size(); i++) {
        for(int j=0; j<m[i].size(); j++) {
            if(SirinaBroja(m[i][j])>max) max=SirinaBroja(m[i][j]);
        }
    }
    return max;
}
int main ()
{
    std::cout<<"Unesite broj redova: "; 
    int br_redova;
    std::cin>>br_redova;
    try {
        auto mat=PascalovTrougao(br_redova);
        std::cout <<std::endl;
        for(int i=0; i<br_redova; i++) {
            for(int j=0; j<i+1; j++) {
                std::cout<<std::right<<std::setw(NajvecaSirina(mat)+1)<<mat.at(i).at(j);
            }
            std::cout <<std::endl;
        }

    }
    catch(std::domain_error izuzetak){
        std::cout<<izuzetak.what()<<std::endl;
    }
    return 0;
}
