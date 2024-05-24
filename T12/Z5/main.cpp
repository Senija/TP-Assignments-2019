#include <iostream>
#include <vector>
#include <functional>
#include <algorithm>
int main ()
{
	std::vector<double> v;
	int br_elemenata;
	std::cout<<"Koliko zelite elemenata: ";
	std::cin>>br_elemenata;
	v.resize(br_elemenata);
	std::cout<<"Unesite elemente: ";
	for(int i = 0; i < br_elemenata; i++) 
		std::cin>>v[i];
	std::transform(v.begin(), v.end(), v.begin(), std::bind(std::divides<double>(), 1, std::placeholders::_1));
	std::cout<<"Transformirani elementi: ";
	for(auto x : v){
		std::cout<<x<<" ";
	}
	return 0;
}