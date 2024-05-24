#include <iostream>
#include <string>
#include <iterator>
#include <algorithm>
std::string IzvrniBezRazmaka(std::string recenica){
	std::string IzvrnutiString;
	std::remove_copy(recenica.rbegin(), recenica.rend(), std::back_inserter(IzvrnutiString), ' ');
	return IzvrnutiString;
}
int main ()
{
	std::string Recenica =" Ja idem na ETF.";
	std::cout<<IzvrniBezRazmaka(Recenica);
	return 0;
}