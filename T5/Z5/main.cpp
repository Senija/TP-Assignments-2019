#include <iostream>
#include <cmath>
#include <iomanip>
 


double TrapeznoPravilo(double (*fun) (double), double a, double b, int n){
	
	double suma=0;
	for(int k=1; k<=n-1; k++){
		suma += fun(a+ ((b-a)/n *k));
	}
	return (b-a)/n *(0.5 * fun(a) + 0.5 * fun(b) + suma);
}

int main ()
{
	int n;
	std::cout<<"Unesite broj podintervala: ";
	std::cin>>n;
	std::cout<<"Za taj broj podintervala priblizne vrijednosti integrala iznose:"<<std::endl;
	const double PI=4*atan(1);
	std::cout<<"- Za funkciju sin x na intervalu (0,pi): "<<std::fixed<<std::setprecision(5)<<TrapeznoPravilo(std::sin, 0, PI, n)<<std::endl;
	std::cout<<"- Za funkciju x^3 na intervalu (0,10): "<<std::setprecision(2)<<TrapeznoPravilo([] (double x) {return std::pow(x, 3);}, 0, 10, n)<<std::endl;
	std::cout<<"- Za funkciju 1/x na intervalu (1,2): "<<std::setprecision(5)<<TrapeznoPravilo([] (double x) {return 1./x;}, 1, 2, n);
	return 0;
}