//TP 2018/2019: Ispit 5, Zadatak 6
#include <iostream>
#include <functional>
#include <vector>
#include <cmath>
std::function<double (double)> FourierovRed(const std::vector<double> &A, const std::vector<double> &B, double w)
{
    if(A.size() == 0 && B.size() == 0) return [](double x) {
        return 0;
    };

    return [w, A, B](double x) {
        double suma = A[0]/2;
        for(int i = 1; i < A.size(); i++) {
            if(i >= B.size()){
                suma += A[i] * cos(i*x*w);
            }
            else suma += A[i] * cos(i*x*w) + B[i] * sin(i*x*w);
            //else suma += A[i] * cos(i*x*w);
        }
        if(B.size() > A.size()){
            for(int i = A.size(); i < B.size(); i++) suma +=  B[i] * sin(i*x*w);
        }
        return suma;
    };
}

int main ()
{
    
    std::vector<double> A{3, 1 ,-0.5, 0.2}, B{0, 2, -1, 0};
    double w = (4*atan(1))/3;
    double x;
    std::cout<<"Unesi x: ";
    std::cin>>x;
    std::cout<<"T(x) = ";
    std::cout<<FourierovRed(A, B, w)(x)<<std::endl;

    return 0;
}
