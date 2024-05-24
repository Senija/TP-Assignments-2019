//TP 2018/2019: ZSR 2, Zadatak 3
#include <iostream>
#include <memory>
int main ()
{
    
    //int *p = new int[5]{1,2,3,4,5};
    std::unique_ptr<int[]> p(new int[5] {1,2,3,4,5});
    
	return 0;
}