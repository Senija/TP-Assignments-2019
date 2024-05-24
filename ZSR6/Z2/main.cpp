//TP 2018/2019: ZSR 6, Zadatak 2
#include <iostream>
#include <string>
#include <set>
#include <iterator>
#include <complex>
#include <functional> 

void P(int &x, int y, int &z) { x -= y; y -= z; z -= x; }
void P(int &x, int y, int &&z) { x += y; y += z; z += x; }
template <typename T>
std::complex<double> Q(T &x, T &y) { return {*--y, *x++}; }
int R(std::function<int(int)> x, int y) { return x(x(y)); }
int main() {
int x(4), y(6), z(1);
P(z, x + 1, y); std::cout << x << " " << y << " " << z << std::endl;
x = 4; y = 6; z = 1;
P(z, x, y + 1); std::cout << x << " " << y << " " << z << std::endl;
std::set<int> s{2, 7, 3, 6, 9, 0, 0, 4, 6, 2, 5};
std::set<int>::iterator p(s.begin()), q(s.end());
while(p != q) std::cout << Q(p, q) << std::endl;
x = 4; y = 1; z = R([&y](int z){ return y++ * z; }, x);
std::cout << x << " " << y << " " << z << std::endl;
std::string k("yxcvbn"), l("poiuztrew"), m(l);
std::copy(k.begin(), k.end(), l.begin());
std::copy(k.begin(), k.end(), std::inserter(m, m.begin()));
std::cout << k << " " << l << " " << m << std::endl;
return 0;
}