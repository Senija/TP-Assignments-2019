#include <iostream>
#include <initializer_list>
#include <functional>
#include <cmath>
#include <utility>
class FourierovRed{
    double *a = nullptr;
    double *b = nullptr;
    double period;
    int stepen;
    public:
    FourierovRed(double T, std::initializer_list<double> A, std::initializer_list<double> B){
        double *pom_a = nullptr;
        double *pom_b = nullptr;
        try{
            int vel;
            if(A.size() >= B.size()) vel = A.size();
            else vel = B.size();
            pom_a = new double[vel]{};
            pom_b = new double[vel]{};
            for(auto i = 0; i < vel; i++){
                pom_a[i] = *(A.begin() + i);
            }
            for(auto i = 0; i < vel; i++){
                pom_b[i] = *(B.begin() + i);
            }
            a= pom_a;
            b = pom_b;
            period = T;
            stepen = vel;
        }
        catch(...){
            delete[] pom_a;
            delete[] pom_b;
            throw;
        }
    }

    FourierovRed(int n, double T, std::function<double(int)> funkA, std::function<double(int)> funkB){
        if(n <= 0) throw std::domain_error ("Stepen mora biti pozitivan");
        double *pom_a = nullptr;
        double *pom_b = nullptr;
        try{
            pom_a = new double[n]{};
            pom_b = new double[n]{};
            for(int i = 0; i < n; i++){
                pom_a[i] = funkA(i);
                pom_b[i] = funkB(i);
            }
            a = pom_a;
            b = pom_b;
            period = T;
            stepen = n;
        }
        catch(...){
            delete[] pom_a;
            delete[] pom_b;
            throw;
        }
    }

    FourierovRed(int n, double poc, double kraj, std::function<double(double)> funk, int M){
        double Pi = 4 * atan(1);
        if(n <=0) throw std::domain_error ("Stepen mora biti pozitivan");
        if(M <= 0) throw std::domain_error ("Broj podintervala mora biti pozitivan");
        if(poc > kraj) throw std::range_error ("Neispravan interval");
        double *pom_a = nullptr;
        double *pom_b = nullptr;
        try{
            pom_a = new double[n]{};
            pom_b = new double[n]{};
            for(int i = 0; i < n; i++){
                double A = (funk(poc) + funk(kraj))/M * cos (2 * i *Pi * poc /(kraj - poc));
                double B = (funk(poc) + funk(kraj))/M * sin (2 * i *Pi * poc /(kraj - poc));
                double suma = 0;
                double sumb = 0;
                for(int j = 1; j <= M-1; j++){
                    suma += funk(poc + j*(kraj - poc)/M) * cos(2*i*Pi*(poc/(kraj - poc) + j/M));
                    sumb += funk(poc + j*(kraj - poc)/M) * sin(2*i*Pi*(poc/(kraj - poc) + j/M));
                }

                pom_a[i] = A + 2/M * suma;
                pom_b[i] = B + 2/M * sumb;
            }
            a = pom_a;
            b = pom_b;
            period = kraj - poc;
            stepen = n;
        }
        catch(...){
            delete[] pom_a;
            delete[] pom_b;
            throw;
        }
    }
    ~FourierovRed(){
        delete[] a;
        delete[] b; 
        a = nullptr;
        b = nullptr;
    }

    FourierovRed(const FourierovRed &FR){
        double *pom_a = nullptr;
        double *pom_b = nullptr;
        try{
            pom_a = new double[FR.stepen]{};
            pom_b = new double[FR.stepen]{};
            for(int i = 0; i < FR.stepen; i++){
                pom_a[i] = FR.a[i];
                pom_b[i] = FR.b[i];
            }

            a = pom_a;
            b = pom_b;
            period = FR.period;
            stepen = FR.stepen;
        }
        catch(...){
            delete[] pom_a;
            delete[] pom_b;
            throw;
        }
    }

    FourierovRed(FourierovRed &&FR) : stepen(FR.stepen), period(FR.period){
        a = FR.a;
        b = FR.b;
        FR.a = nullptr;
        FR.b = nullptr;
        FR.stepen = 0;
    }
    FourierovRed &operator = (const FourierovRed &FR){
        double *pom_a = nullptr;
        double *pom_b = nullptr;
        try{
            pom_a = new double[FR.stepen]{};
            pom_b = new double[FR.stepen]{};
            for(int i = 0; i < FR.stepen; i++){
                pom_a[i] = FR.a[i];
                pom_b[i] = FR.b[i];
            }
            delete[] a;
            delete[] b;
            a = nullptr;
            b = nullptr;
            a = pom_a;
            b = pom_b;
            stepen = FR.stepen;
            period = FR.period; 

        }
        catch(...){
            delete[] pom_a;
            delete[] pom_b;
        }
        return *this;
    }

    FourierovRed &operator = (FourierovRed &&FR){
        std::swap(a, FR.a);
        std::swap(b, FR.b);
        std::swap(stepen, FR.stepen);
        std::swap(period, FR.period);
        return *this;
    }

    double operator ()(double argument) const{
        double Pi = 4 * atan(1);
        double rez = a[0]/2;
        for(int i = 1; i < stepen; i++){
            rez += a[i] * cos(2*i*argument * Pi/period) + b[i] * sin(2*i*argument * Pi/period); 
        }

        return rez;
    }

    std::pair<double, double> operator[](int index) const {
        if(index < 0 || index > stepen-1) throw std::range_error ("Neispravan indeks");
        if(index == 0) return std::make_pair(a[index], 0);
        return std::make_pair(a[index], b[index]);
    }

    // std::pair<double&, double&> operator[](int index){
    //     if(index < 0 || index > stepen-1) throw std::range_error ("Neispravan indeks");
    //     // double &pom_a = a[index];
    //     // double &pom_b = b[index];
    //     return std::make_pair(a[index], b[index]);
    // }    
};
int main(){
    FourierovRed f1(8 * atan(1), {5,2,3,4}, {5,2,3,4});
    // std::cout<<f[0].first<<" "<<f[0].second;
    // std::cout<<f(2);
    
    FourierovRed f(10, 8 * atan(1), [](int x){if(x == 0) return 1; return 1/x;}, [](int y){return 2*y/10;});
    std::cout<<f[0].first<<" "<<f[0].second<<std::endl;
    FourierovRed f2(f);
    std::cout<<f2[0].first<<" "<<f2[0].second<<std::endl;
    f2 = f1;
    std::cout<<f2[0].first<<" "<<f2[0].second<<std::endl;
    FourierovRed f3(10, 1, 10, [](int x){if(x == 0) return 1; return 1/x;}, 100);
    std::cout<<f3[0].first<<" "<<f3[0].second<<std::endl;
    return 0;
}