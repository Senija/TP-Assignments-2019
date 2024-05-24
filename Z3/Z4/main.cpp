//TP 2018/2019: Zadaća 3, Zadatak 4
#include <iostream>
#include <list>
#include <iterator>
#include <set>
int Poglavica(int br_punoljetnih, int korak, bool ispis = false)
{

    std::list<int> krug(br_punoljetnih);
    int element = 1;
    for(auto i = krug.begin(); i != krug.end(); i++) {
        *i = element;
        element++;
    }
    int brojac = 1;
    auto it = krug.begin();
    for(;;) {

        while(brojac == korak ) {
            if(krug.size() == 1) break;
            if(ispis == true) std::cout<<*it<<std::endl;
            it = krug.erase(it);
            if(it == krug.end()) it = krug.begin();
            brojac = 1;
            //if(krug.size() == 1) break;
        }

        if(krug.size() == 1) return *it;
        it++;
        brojac++;
        if(it == krug.end()) it = krug.begin();
    }
}

int SigurnoMjesto(int korak, int n1, int n2)
{
    //std::vector<int> MjestaUKrugu(n2);
    std::set<int> MjestaUKrugu;
    
    for(auto i = 1; i < n2; i++) {
        MjestaUKrugu.insert(i);
    }
    for(int i = n1; i < n2; i++) {
        auto poglavica = Poglavica(i, korak);
        MjestaUKrugu.erase(poglavica);
    }
    if(MjestaUKrugu.size() != 0) {
        auto it = MjestaUKrugu.begin();
        if(*it > n1) return 0;
        return *it;
    } else return 0;

}
int main ()
{
    int br_punoljetnih = 0;
    std::cout<<"Unesi broj punoljetnih clanova (N): "; 
    std::cin>>br_punoljetnih;
    int korak = 0;
    std::cout<<"Unesi korak razbrajanja (M): ";
    std::cin>>korak;
    int pocetak, kraj;
    std::cout<<"Unesi raspon (N1-N2): ";
    std::cin>>pocetak>>kraj;
    std::cout<<"Redni broj osobe koja postaje poglavica: "<<Poglavica(br_punoljetnih, korak)<<" Sigurno mjesto: "<<SigurnoMjesto(korak, pocetak, kraj);
    //std::cout<<"Sigurno mjesto: "<<SigurnoMjesto(korak, pocetak, kraj);
    return 0;
}
