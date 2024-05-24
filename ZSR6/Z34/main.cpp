#include <iostream>
#include <vector>
#include <cmath>

double Sxx (std::vector<double> x, double x_srednje) {
    
    std::cout << "(Xi - Xsrednje)^2 = ";
    double s = 0;
    for(int i = 0; i < x.size(); i++) {
        std::cout << "(" << x[i] << "-" << x_srednje << ")^2 " ;
        if(i != x.size() - 1) std::cout << "+ ";
        s += (x[i] - x_srednje)*(x[i] - x_srednje);
    }
    std::cout << std::endl;
    std::cout << "(Xi - Xsrednje)^2 = " << s << std::endl;
    return s;
}

double Syy (std::vector<double> y, double y_srednje) {
    std::cout << "(Yi - Ysrednje)^2 = ";
    double s = 0;
    for(int i = 0; i < y.size(); i++) {
        std::cout << "(" << y[i] << "-" << y_srednje << ")^2 " ;
        if(i != y.size() - 1) std::cout << "+ ";
        s += (y[i] - y_srednje)*(y[i] - y_srednje);
    }
    std::cout << std::endl;
    std::cout << "(Yi - Ysrednje)^2 = " << s << std::endl;
    return s;
}

double Sxy (std::vector<double> x, std::vector<double> y, double x_srednje, double y_srednje) {
    std::cout << "(Xi - Xsrednje)(Yi - Ysrednje) = ";
    double s = 0;
    if(x.size() != y.size()) throw std::logic_error ("NISU JEDNAKI X I Y VEKTORI!!!!");
    for(int i = 0; i < x.size(); i++) {
        std::cout << "(" << x[i] << "-" << x_srednje << ")(" << y[i] << "-" << y_srednje << ")" ;
        if(i != x.size() - 1) std::cout << "+ ";
        s += (x[i] - x_srednje)*(y[i] - y_srednje);
    }
    std::cout << std::endl;
    std::cout << "(Xi - Xsrednje)(Yi - Ysrednje) = " << s << std::endl;
    return s;
}


int main ()
{
    std::cout << "Linearna regrsija (metoda najmanjih kvadrata): " << std::endl;
    std::vector<double> x {1, 2, 3, 6, 9, 12};
    std::vector<double> y {3,6,13,16,29,35};
    
    double x0 = 30; // Koliko ce rijeci znati za 20 dana? (primjer sa ispita);
    int n = x.size();
    
    double t = 0.941;
    
    double suma = 0;
    for(auto a : x) suma += a;
    double x_srednje = double(suma) / x.size();
    std::cout << "X srednje = " << x_srednje << std::endl;
    suma = 0;
    for(auto a : y) suma += a;
    double y_srednje = double(suma) / y.size();
    std::cout << "Y srednje = " << y_srednje << std::endl;
    
    std::cout << std::endl << "Sxx : " << std::endl;
    double sxx = Sxx(x, x_srednje);
    
    std::cout << std::endl << "Syy : " << std::endl;
    double syy = Syy(y, y_srednje);
    
    std::cout << std::endl << "Sxy : " << std::endl;
    double sxy = Sxy(x, y, x_srednje, y_srednje);

    double b1 = sxy / sxx;
    std::cout << std::endl << "b1: " << b1 <<  std::endl;
    
    double b0 = y_srednje - b1 * x_srednje;
    std::cout << std::endl << "b0: " << b0 <<  std::endl;
    
    double y0 = b0 + b1*x0;
    std::cout << std::endl << "y0: " << y0 <<  std::endl;
    
    
    double s = std::sqrt((syy - b1 * sxy) / (n - 2));
    std::cout << "s: " << s << std::endl;
    
    double pom = t*s*std::sqrt(1/n + (x0 - x_srednje)*(x0 - x_srednje)/sxx);
    std::cout << "Interval pouzdanosti za ocekivanje: " << y0 - pom << ", " << y0 + pom << std::endl;
    pom = t*s*std::sqrt(1 + 1/n + (x0 - x_srednje)*(x0 - x_srednje)/sxx);
    std::cout << "Vrijednost varijable y: " << y0 - pom << ", " << y0 + pom << std::endl;
    
    
    return 0;
}