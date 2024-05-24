#include <iostream>
#include <set>
void f(int **p, int *q) { *p = q; }
template <typename T, typename F>
void g(T p, T q, F r) { while(p != q) r(*--q); }
int &h(int &p, int &q, int &r) {
std::cout << p << " " << q << " " << r << std::endl;
p = q++;
q = r++; 
r = p++;
std::cout << p << " " << q << " " << r << std::endl;
return p;
}
int main() {
std::set<int> s{2, 4, 1, 9, 7};
s.insert(1); s.insert(5);
for(auto x : s) std::cout << x << " ";
std::cout << std::endl;
int a[]{4, 1, 6, 7, 3, 2, 9}, *p(a + 4), q(8), r(4);
h(*(a + 2), a[4], p[-2]) *= 3;
for(auto i = std::begin(a); i < std::end(a); i++)
std::cout << *i << " ";
f(&p, &q); std::cout << p[0] << " ";
f(&p, new int(2)); std::cout << p[0] << std::endl;
g(a, a + 5, [&r](int x) { std::cout << x << "," << r << " "; r += x; });
std::cout << r << std::endl;
for(auto i = std::begin(a); i < std::end(a); i++)
std::cout << *i << " ";
std::cout << std::endl;
return 0;
}