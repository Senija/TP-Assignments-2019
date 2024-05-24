#include <iostream>
#include <functional>
#include <cmath>

typedef std::function<int (int)> PrimaVracaInt;
//template<typename FunkTip1, typename FunkTip2>
PrimaVracaInt Kompozicija(PrimaVracaInt f1, PrimaVracaInt f2){
    return [f1, f2] (int x) {  
        return f2(f1(x));
    };
}
PrimaVracaInt IteriranaFunkcija(PrimaVracaInt fun, int n){
    auto g = fun;
    if(n <= 0) return g;
    while(n != 1){
       g = Kompozicija(fun,g);
        n--;
    }
}
// int f(int x){
//     return x*x;
// }
int main ()
{
    //std::cout << IteriranaFunkcija([](int x) { return 3*x - 5; }, 6)(0) << std::endl;
	    std::cout<<IteriranaFunkcija([](int x) { return 3*x - 5;}, 6)(0)<<std::endl;

	return 0;
}