//TP 2018/2019: ZSR 3, Zadatak 1
#include <iostream>
#include <stack>
int main ()
{
    std::stack<int> s;
    s.push(5);
    s.push(4);
    s.push(3);
    while(!s.empty()){
        std::cout<<s.top();
        s.pop();
    }
    	return 0;
}