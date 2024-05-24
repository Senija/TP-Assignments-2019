//TP 2016/2017: Zadaća 1, Zadatak 3 POSLALA
#include <iostream>
#include <cmath>
#include <vector>
#include <exception>
#include <iomanip>
typedef std::vector<std::vector<double>> Matrica;
typedef std::vector<std::vector<std::vector<double>>> Matrica3D;

Matrica KreirajMatricu(int br_redova, int br_kolona)
{
    return Matrica(br_redova, std::vector<double>(br_kolona));
}
int BrojRedova(Matrica m)
{
    if( m.size() != 0) return m.size();
    else return 0;
}

int BrojKolona(Matrica m)
{
    if(BrojRedova(m) != 0) return m.at(0).size(); //ne pristupati necemu sto ne postoji
    else return 0;

}

Matrica UnesiMatricu(Matrica &mat)
{
    for(int i=0; i<BrojRedova(mat); i++) {
        std::cout<<"Elementi "<<i+1<<". reda: ";
        for(int j=0; j<BrojKolona(mat); j++) {
            std::cin>>mat.at(i).at(j);
        }
    }
    return mat;
}


bool DaLiJePravilnaMatrica(Matrica &mat)
{
    bool pravilna=true;
    if(BrojRedova(mat)==0) return pravilna;
    for(int i=0; i<mat.size()-1; i++) {
        if(mat.at(i).size() != mat.at(i+1).size()) {
            pravilna=false;
            break;
        }
    }
    return pravilna;
}

Matrica MnozenjeMatrica(Matrica &mat1, Matrica &mat2)
{
    if(BrojKolona(mat1) != BrojRedova(mat2) && DaLiJePravilnaMatrica(mat1) && DaLiJePravilnaMatrica(mat2)) throw std::domain_error ("Nije moguce mnozenje matrica!");
    if(!DaLiJePravilnaMatrica(mat1) || !DaLiJePravilnaMatrica(mat2)) throw std::domain_error ("Neispravna matrica!");
    auto pomnozena=KreirajMatricu(BrojRedova(mat1), BrojKolona(mat2));
    for(int i=0; i<BrojRedova(mat1); i++) {
        for(int j=0; j<BrojKolona(mat2); j++) {
            double suma=0;
            for(int k=0; k<BrojRedova(mat2); k++) suma+=mat1.at(i).at(k) * mat2.at(k).at(j);
            pomnozena.at(i).at(j)=suma;

        }
    }
    return pomnozena;
}

bool JeLiKvadratna(Matrica &mat)
{
    if(mat.size()==0) return true;
    return BrojKolona(mat)==BrojRedova(mat);
}

Matrica3D DoolitleLU(Matrica &matH)
{
    if(!DaLiJePravilnaMatrica(matH)) throw std::domain_error ("Neispravna matrica!");
    if(!JeLiKvadratna(matH)) throw std::domain_error ("Matrica mora biti kvadratnog oblika!");

    Matrica U(BrojRedova(matH), std::vector<double>(BrojRedova(matH)));
    Matrica L(BrojRedova(matH), std::vector<double>(BrojRedova(matH)));

    for(int i=0; i<BrojRedova(matH); i++) {
        for(int j=0; j<BrojRedova(matH); j++) {
            if(i==0) {
                U.at(i).at(j)=matH.at(i).at(j);
            }
            if(i==j) {
                L.at(i).at(j)=1;
            }
            if(j>i) {
                L.at(i).at(j)=0;
            }
            if(j<i) {
                U.at(i).at(j)=0;
            }
        }
    }
    //popinula sa onim sto znam

    //algoritam
    for(int i=1; i<BrojRedova(matH); i++) {
        for(int j=0; j<BrojRedova(matH); j++) {
            if(j<i) {
                double clan;
                double suma=0;
                if(j!=0) for(int k=0; k<=j-1; k++) {
                        suma += L.at(i).at(k) * U.at(k).at(j);
                    }
                if(U.at(j).at(j) != 0) clan=1/U.at(j).at(j) * ( matH.at(i).at(j) - suma);
                else throw std::domain_error ("Nije dozvoljenjo dijeljenje sa 0!"); // umainu napraviti CATCH onda???
                L.at(i).at(j) = clan;
            }

            if(j>=i) {
                double clan;
                double suma=0;
                for(int k=0; k<=i-1; k++) {
                    suma += L.at(i).at(k) * U.at(k).at(j);
                }
                clan=matH.at(i).at(j) - suma;
                U.at(i).at(j)= clan;
            }
        }
    }
    Matrica3D povratna;
    if(matH.size()!=0) {
        Matrica &PrviSprat=L;
        Matrica &DrugiSprat=U;
        povratna.push_back(PrviSprat);
        povratna.push_back(DrugiSprat);
    }

    return povratna;

}

bool ProvjeriFaktorizaciju(Matrica &H, Matrica3D &LU)
{
    try {
        if(LU.size()==0 && H.size()==0) {
            return true;
            
        }
        else if(LU.size()==2 && JeLiKvadratna(H)){
            return MnozenjeMatrica(LU.at(0), LU.at(1)) == H;
        }

        return false;
    } catch (std::domain_error izuzetak) {
        std::cout << izuzetak.what() << std::endl;
    }

}

int main ()
{
    int dimenzijeMatrice;
    std::cout<<"Unesite dimenziju kvadratne matrice H: ";
    std::cin>>dimenzijeMatrice;
    try {
        Matrica H=KreirajMatricu(dimenzijeMatrice, dimenzijeMatrice);
        std::cout<<"Unesite elemente matrice H:"<<std::endl;
        H=UnesiMatricu(H);
        Matrica3D LU=DoolitleLU(H);
        std::cout<<"Matrica L:"<<std::endl;
        for(std::vector<double> &red: LU.at(0)) {
            for(double x: red) {
                std::cout <<std::setw(9)<<std::fixed<<std::setprecision(4)<<x;
            }
            std::cout<<std::endl;
        }
        std::cout<<"Matrica U:"<<std::endl;
        for(std::vector<double> &red: LU.at(1)) {
            for(double x: red) {
                std::cout <<std::setw(9)<<std::fixed<<std::setprecision(4)<<x;
            }
            std::cout<<std::endl;
        }
    } catch(std::domain_error izuzetak) {
        std::cout<< izuzetak.what() <<std::endl;
    }

    


    return 0;
}
