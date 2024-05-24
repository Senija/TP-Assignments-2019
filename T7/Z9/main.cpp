#include <iostream>
#include <string>
#include <iterator>
#include <algorithm>
#include <functional>


std::function<double (double)> plus2(double broj1){
    
    return [broj1](double broj2){return broj1 + broj2;};
}

std::function<std::function<double (double)> (double)> plus3(double broj1){

    //pok_na_funkciju [broj1] (double broj2){return broj1 + broj2};
    return [broj1](double broj2){return plus2(broj1+broj2);};
}


int main ()
{ 
    
	return 0;
}