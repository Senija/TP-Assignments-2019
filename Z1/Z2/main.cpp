//TP 2016/2017: Zadaća 1, Zadatak 2
#include <iostream>
#include <cmath>
#include <vector>
#include <deque>
#include <exception>

const double Eps=1e-10;
enum class Smjer {Rastuci, Opadajuci};

double SumaPodniza(std::vector<double> &v, int pocetak, int kraj)
{
    double suma=0;
    for(int i=pocetak; i<kraj; i++) {
        suma+=v.at(i);
    }
    return suma;
}

std::vector<double> KopirajDioVektora(std::vector<double> &v, int pocetak, int kraj)
{
    std::vector<double> pomocni;
    for(int i=pocetak; i<kraj; i++) {
        pomocni.push_back(v.at(i));
    }
    return pomocni;
}

bool PostojiLiPodnizUDeku(std::deque<std::vector<double>> &dek, std::vector<double> &podniz) // sta ako ovdje se posalje sve prazno
{

    if(dek.size()==0) return false;
    if(podniz.size()==0) return true;
    bool postoji=false;
    int index_podniza=0;
    for(int i=0; i<dek.size(); i++) {
        if(podniz.size()>dek.at(i).size()) return false;
        int j=0;
        while(j<dek.at(i).size()) {
            index_podniza=0;
            while( std::fabs(dek.at(i).at(j) - podniz.at(index_podniza)) <= Eps*(std::fabs(dek.at(i).at(j)) + fabs(podniz.at(index_podniza)))) {
                j++;
                index_podniza++;
                if(index_podniza == podniz.size() || j == dek.at(i).size()) break;
            }
            if(index_podniza == podniz.size()) {
                return true;
                break;
            }
            j++;
        }
    }
    return postoji;
}

std::deque<std::vector<double>> MaksimalniBalansiraniPodniz( std::vector<double> v)
{

    std::deque<std::vector<double>> dekMaxBalansiranogPodniza;
    for(int i=v.size(); i>1; i--) {
        for(int j=0; j<=i; j++) {
            //if((i-j)%2 == 0 ){

            if(std::fabs(SumaPodniza(v, j, (i-j)/2 +j ) - SumaPodniza(v, (i-j+1)/2+j, i)) <= Eps*( std::fabs( SumaPodniza(v, j, (i-j)/2 +j ) ) + std::fabs( SumaPodniza(v, (i-j+1)/2+j, i) ))) {
                std::vector<double> pomocni = KopirajDioVektora(v, j, i);
                if(pomocni.size()>=2 && !PostojiLiPodnizUDeku(dekMaxBalansiranogPodniza, pomocni))
                    dekMaxBalansiranogPodniza.push_back(pomocni);

            }
        }
    }

    return dekMaxBalansiranogPodniza;
}



bool DaLiJeBalansiraniPodniz(std::deque<std::vector<double>> dek)
{

    bool balansiran=true;
    for(int i=0; i<dek.size(); i++) {
        if( std:: fabs(SumaPodniza(dek.at(i), 0, dek.at(i).size()/2) - SumaPodniza(dek.at(i), (dek.at(i).size() + 1)/2, dek.at(i).size())) > Eps*(std::fabs(SumaPodniza(dek.at(i), 0, dek.at(i).size()/2)) + std::fabs(SumaPodniza(dek.at(i), (dek.at(i).size() + 1)/2, dek.at(i).size()))))
            return false;
    }
    return balansiran;
}
std::deque<std::vector<double>> Transformacija(std::deque<std::vector<double>> dek, Smjer sortiranje)
{

    if(!DaLiJeBalansiraniPodniz(dek)) throw std::domain_error ("Dek vektora je neispravan.");
    if(sortiranje == Smjer::Rastuci) {

        for(int i=0; i<dek.size(); i++) { ///raste pa opada
            for(int j=0; j<dek.at(i).size()/2 ; j++) {
                int min=j;
                for(int k=j+1; k<dek.at(i).size()/2; k++) {
                    if(dek.at(i).at(k) < dek.at(i).at(min))
                        min=k;
                }

                double temp=dek.at(i).at(j);
                dek.at(i).at(j)= dek.at(i).at(min);
                dek.at(i).at(min) = temp;
            }
        }

        for(int i=0; i<dek.size(); i++) { ///raste pa opada
            for(int j=(dek.at(i).size()+1)/2 ; j<dek.at(i).size(); j++) {
                int max=j;
                for(int k=j+1; k<dek.at(i).size(); k++) {
                    if(dek.at(i).at(k) > dek.at(i).at(max))
                        max=k;
                }

                double temp=dek.at(i).at(j);
                dek.at(i).at(j)= dek.at(i).at(max);
                dek.at(i).at(max) = temp;
            }
        }
    }
    if(sortiranje == Smjer::Opadajuci) {

        for(int i=0; i<dek.size(); i++) { //od veceg ka manjem
            for(int j=0; j<dek.at(i).size()/2 ; j++) {
                int max=j;
                for(int k=j+1; k<dek.at(i).size()/2; k++) {
                    if(dek.at(i).at(k) > dek.at(i).at(max))
                        max=k;
                }

                double temp=dek.at(i).at(j);
                dek.at(i).at(j)= dek.at(i).at(max);
                dek.at(i).at(max) = temp;
            }
        }

        for(int i=0; i<dek.size(); i++) { ///raste pa opada
            for(int j=(dek.at(i).size()+1)/2 ; j<dek.at(i).size(); j++) {
                int min=j;
                for(int k=j+1; k<dek.at(i).size(); k++) {
                    if(dek.at(i).at(k) < dek.at(i).at(min))
                        min=k;
                }

                double temp=dek.at(i).at(j);
                dek.at(i).at(j)= dek.at(i).at(min);
                dek.at(i).at(min) = temp;
            }
        }
    }

    return dek;


}

int main ()
{
    int br_elemenata;
    std::cout<<"Unesite broj elemenata niza: ";
    std::cin>>br_elemenata;
    std::cout<<"Unesite elemente niza: ";
    std::vector<double> Vektor(br_elemenata);
    for(int i=0; i<br_elemenata; i++) {

        std::cin>>Vektor.at(i);
    }
    int tip;
    std::cout<<"Unesite tip: (1 - rastuci, 0 - opadajuci): "<<std::endl;
    std::cin>>tip;
    std::cout<<"Maksimalni balansirani podnizovi: "<<std::endl;
    std::deque<std::vector<double>> balansiraniDek = MaksimalniBalansiraniPodniz(Vektor);
    for(int i=balansiraniDek.size()-1; i>=0; i--) {
        for(int j=0; j<balansiraniDek.at(i).size(); j++) {
            if(j == balansiraniDek.at(i).size()-1) std::cout<<balansiraniDek.at(i).at(j);
            else std::cout<<balansiraniDek.at(i).at(j)<<" ";
        }
        std::cout << std::endl;
    }
    std::cout<<"Savrseni balansirani podnizovi nakon transformacije:"<<std::endl;
    std::deque<std::vector<double>> SortiraniDek;
     if(tip==1) SortiraniDek = Transformacija(balansiraniDek, Smjer::Rastuci);                            

    else SortiraniDek = Transformacija(balansiraniDek, Smjer::Opadajuci);

    for(int i=SortiraniDek.size()-1; i>=0; i--) {
        for(int j=0; j<SortiraniDek.at(i).size(); j++) {
            if(j == SortiraniDek.at(i).size()-1) std::cout<<SortiraniDek.at(i).at(j);
            else std::cout<<SortiraniDek.at(i).at(j)<<" ";
        }
        std::cout << std::endl;
    }

    return 0;
}
