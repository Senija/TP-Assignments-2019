//TP 2018/2019: Zadaća 3, Zadatak 4
#include <iostream>
#include <list>
#include <iterator>
#include <set>
struct Cvor {
    int redni_broj;
    Cvor *sljedeci;
};
int Poglavica(int br_punoljetnih, int korak, bool ispis = false)
{
    Cvor *pocetak = nullptr, *prethodni;
    int brojac = 0;
    try {
        for(;;) {
            if(brojac == br_punoljetnih) {
                break;
            }
            Cvor *novi = new Cvor {brojac+1, nullptr};
            if(!pocetak) pocetak = novi;
            else prethodni->sljedeci = novi;
            if(brojac == br_punoljetnih-1) {
                novi->sljedeci = pocetak;
                //prethodni = novi->sljedeci;
            }
            prethodni = novi;

            brojac++;
        }
        int br_mjesta = 1;
        auto pok = pocetak;
        //prethodni = pocetak;
        //bool prvi_prolazak = true;
        for(;;) {
            while(br_mjesta == korak) {
                if(pok == prethodni) break;
                auto pomocna = pok->sljedeci;
                if(ispis == true) std::cout<<pok->redni_broj<<std::endl;
                delete pok;
                prethodni->sljedeci = pomocna;
                pok = pomocna;
                br_mjesta = 1;
                //if(pok == prethodni) break;
            }

            // if(prvi_prolazak) {
            //     prvi_prolazak = false;
            //     pok = pok->sljedeci;
            //     br_mjesta++;
            // }
            if(pok == prethodni) {
                int poglavica = pok->redni_broj;
                delete pok;
                return poglavica;
            } else {
                pok = pok->sljedeci;
                prethodni = prethodni->sljedeci;
                br_mjesta++;
            }


        }
    } catch(std::bad_alloc) {
        for(auto p = pocetak; p != nullptr; ) {
            auto temp = p->sljedeci;
            delete p;
            p = temp;
        }
        return 0;
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
