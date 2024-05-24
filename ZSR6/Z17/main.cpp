//TP 2018/2019: ZSR 6, Zadatak 17
#include <iostream>
#include <forward_list>

int main ()
{
    std::forward_list<int> nova;
    std::cout<<nova.end() - nova.begin();
	return 0;
}