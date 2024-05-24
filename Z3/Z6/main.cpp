//TP 2018/2019: Zadaća 3, Zadatak 4
//NEMAM PROVJERU ZA MEMORIJU OVJDE
#include <iostream>
#include <list>
#include <iterator>
#include <memory>
#include <set>
struct Cvor {
    int redni_broj;
    std::shared_ptr<Cvor> sljedeci;
};
int Poglavica(int br_punoljetnih, int korak, bool ispis = false)
{
    std::shared_ptr<Cvor> pocetak = nullptr, prethodni;
    for(int brojac = 0; brojac < br_punoljetnih; brojac++) {
        //if(brojac == br_punoljetnih) break;
        auto novi = std::make_shared<Cvor>();
        novi->redni_broj = brojac+1;
        novi->sljedeci = nullptr;
        if(!pocetak) pocetak = novi;
        else prethodni->sljedeci = novi;
        if(brojac == br_punoljetnih-1) novi->sljedeci = pocetak;
        prethodni = novi;

    }
    //prethodni = nullptr;
    int br_mjesta = 1;
    auto pok = pocetak;
    //prethodni = pocetak;
    //bool prvi_prolazak = true;
    for(;;) {
        while(br_mjesta == korak) {
            if(pok == prethodni) break;
            auto pomocna = pok->sljedeci;
            //delete pok;
            if(ispis == true) std::cout<<pok->redni_broj<<std::endl;
            prethodni->sljedeci = pomocna;
            pok = pomocna;
            br_mjesta = 1;
        }

        // if(prvi_prolazak) {
        //     prvi_prolazak = false;
        //     pok = pok->sljedeci;
        //     br_mjesta++;
        // } 
         if(pok == prethodni) {
            int poglavica = pok->redni_broj;
            //delete pok;
            prethodni->sljedeci = nullptr;
            pok = nullptr;
            return poglavica;
        } else {
            pok = pok->sljedeci;
            prethodni = prethodni->sljedeci;
            br_mjesta++;
        }


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
    return 0;
}
