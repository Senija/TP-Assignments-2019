//TP VJEZBA ZA ISPIT
#include <iostream>
#include <functional>
typedef std::function<int (int)> PrimaVracaInt;

PrimaVracaInt Kompozicija(PrimaVracaInt f1, PrimaVracaInt f2){
    return [f1, f2] (int x){ return f2(f1(x)); };
}

PrimaVracaInt IteriranaFunkcija(PrimaVracaInt f, int n){
    auto g = f;
    if(n <= 1) return g;
    while(n != 1){
        g = Kompozicija(f, g);
        n--;
    }
}
int main ()
{
    std::cout<<IteriranaFunkcija([](int x) { return 3*x - 5;}, 6)(0)<<std::endl;
    //std::cout<<g(0);
	return 0;
}