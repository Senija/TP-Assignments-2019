//TP 2018/2019: Zadaća 4, Zadatak 3
#include <iostream>
#include <cstring>
#include <stdexcept>
#include <utility>
#include <iomanip>
#include <initializer_list>
#include <algorithm>
class Let
{
    static const int length_odrdiste = 30;
    static const int length_oznaka = 10;
    char naziv_odredista[length_odrdiste];
    char oznaka_leta[length_oznaka];
    int kapija;
    std::pair<int, int> vrijeme_polijetanja; // vrijeme poijetanja
    int trajanje_leta; // u min
    int kasnjenje;
public:
    Let(const char odrediste[], const char oznaka_leta[], int kapija, int sat_polaska, int minute_polaska, int trajanje_leta);
    void PostaviKasnjenje(int kasnjenje);
    bool DaLiKasni() const
    {
        if(kasnjenje == 0) return false;
        return true;
    }
    int DajTrajanjeLeta() const
    {
        return trajanje_leta;
    }
    std::pair<int, int> DajOcekivanoVrijemePolijetanja() const
    {
        std::pair<int, int> pomocna;
        pomocna.second = vrijeme_polijetanja.second + kasnjenje;
        pomocna.first = (vrijeme_polijetanja.first + (pomocna.second)/60) % 24;
        pomocna.second = pomocna.second % 60;
        return pomocna;
    }
    std::pair<int, int> DajOcekivanoVrijemeSlijetanja() const
    {
        std::pair<int, int> vrijeme_slijetanja;
        vrijeme_slijetanja.second = vrijeme_polijetanja.second + trajanje_leta + kasnjenje;
        vrijeme_slijetanja.first = (vrijeme_polijetanja.first + (vrijeme_slijetanja.second) / 60) % 24;
        vrijeme_slijetanja.second = vrijeme_slijetanja.second % 60;

        return vrijeme_slijetanja;
    }
    void Ispisi() const
    {
        char sasjecen_naziv[21];
        if(strlen(naziv_odredista) > 20) {
            strncpy(sasjecen_naziv, naziv_odredista, 20);
            sasjecen_naziv[20] = '\0';
        } else strcpy(sasjecen_naziv, naziv_odredista);
        if(kasnjenje == 0) {
            std::cout<<std::left<<std::setw(10)<<std::setfill(' ')<<oznaka_leta<<std::setw(20)<<std::setfill(' ')<<sasjecen_naziv<<"   "<<std::right<<std::setw(3)<<std::setfill('0')<<std::setw(2)<<vrijeme_polijetanja.first<<":"<<std::setfill('0')<<std::setw(2)<<vrijeme_polijetanja.second;
            std::cout<<"   "<<std::setw(3)<<std::setfill(' ')<<std::setw(2)<<std::setfill('0')<<DajOcekivanoVrijemeSlijetanja().first<<":"<<std::setfill('0')<<std::setw(2)<<DajOcekivanoVrijemeSlijetanja().second<<std::setw(6)<<std::setfill(' ')<<kapija<<std::endl;
        } else {
            std::pair<int, int> pomocnoVrijeme = DajOcekivanoVrijemePolijetanja();
            pomocnoVrijeme.first -= kasnjenje/60;
            pomocnoVrijeme.second -=kasnjenje%60;

            std::cout<<std::left<<std::setw(10)<<std::setfill(' ')<<oznaka_leta<<std::setw(20)<<sasjecen_naziv<<"   "<<std::right<<std::setw(3)<<std::setfill('0')<<std::setw(2)<<DajOcekivanoVrijemePolijetanja().first<<":"<<std::setfill('0')<<std::setw(2)<<DajOcekivanoVrijemePolijetanja().second;
            std::cout<<" (Planirano "<<std::setfill('0')<<std::setw(2)<<pomocnoVrijeme.first<<":"<<std::setfill('0')<<std::setw(2)<<pomocnoVrijeme.second<<", Kasni "<<kasnjenje<<" min)"<<std::endl;
        }

    }
};

Let::Let(const char odrediste[], const char oznaka_leta[], int kapija, int sat_polaska, int minute_polaska, int trajanje_leta)
{
    if(sat_polaska < 0 || sat_polaska > 23) throw std::domain_error ("Nevalidan parametar za sate");
    if(minute_polaska < 0 || minute_polaska > 59) throw std::domain_error ("Nevalidan parametar za minute");
    if(trajanje_leta < 0) throw std::domain_error ("Nevalidan parametar za trajanje leta");
    if(strlen(odrediste) > 30) throw std::domain_error ("Predugacno ime za odrediste");
    if(strlen(oznaka_leta) > 10) throw std::domain_error ("Predugacno ime za oznaku leta");
    /// ostalo
    strcpy(naziv_odredista, odrediste);
    strcpy(Let::oznaka_leta, oznaka_leta);
    Let::kapija = kapija;
    vrijeme_polijetanja.first = sat_polaska;
    vrijeme_polijetanja.second = minute_polaska;
    Let::trajanje_leta = trajanje_leta;
    kasnjenje = 0;
}
void Let::PostaviKasnjenje(int kasnjenje)
{
    //da li ovdje treba bacat
    Let::kasnjenje = kasnjenje;
}

class Letovi
{
    int max_br_letova;
    int ostvareni_letovi;
    Let **PokNaLet;
    static bool DaLiKasni(Let *l)
    {
        if(l->DaLiKasni()) return true;
        return false;

    }
public:
    explicit Letovi(int max_broj_letova) : max_br_letova(max_broj_letova), ostvareni_letovi(0), PokNaLet(new Let *[max_broj_letova] {}) {}
    Letovi(std::initializer_list<Let> lista_letova): ostvareni_letovi(lista_letova.size()), max_br_letova(lista_letova.size()), PokNaLet(new Let*[lista_letova.size()] {})
    {
        for(int i = 0; i != lista_letova.size(); i++) PokNaLet[i] = new Let(*(lista_letova.begin() + i));
    }
    ~Letovi()
    {
        for(int i = 0; i != ostvareni_letovi; i++) {
            delete PokNaLet[i];
            PokNaLet[i] = nullptr;
        }
        delete[] PokNaLet;
    }
    Letovi(const Letovi &letovi);
    Letovi(Letovi &&letovi);
    Letovi &operator= (const Letovi &letovi);
    Letovi &operator= (Letovi &&letovi);
    void RegistrirajLet(const char odrediste[], const char oznaka_leta[],    int kapija, int sat_polaska, int minute_polaska, int trajanje_leta);
    void RegistrirajLet(Let *let);
    int DajBrojLetova() const
    {
        return ostvareni_letovi;
    }
    int DajBrojLetovaKojiKasne() const;
    int DajProsjecnoTrajanjeLetova() const;
    Let &DajPrviLet() const;
    Let &DajPosljednjiLet() const;
    void IsprazniKolekciju();
    void Ispisi(int sati, int minute) const;
};
Letovi::Letovi(const Letovi &letovi) :max_br_letova(letovi.max_br_letova), ostvareni_letovi(letovi.ostvareni_letovi), PokNaLet(new Let*[letovi.max_br_letova] {})
{
    try {
        for(int i = 0; i < letovi.ostvareni_letovi; i++) PokNaLet[i] = new Let(*(letovi.PokNaLet[i]));
    } catch(...) {
        for(int i = 0; i < letovi.ostvareni_letovi; i++) delete PokNaLet[i];
        delete[] PokNaLet;
        throw;
    }
}
Letovi::Letovi(Letovi &&letovi) : PokNaLet(letovi.PokNaLet), ostvareni_letovi(letovi.ostvareni_letovi), max_br_letova(letovi.max_br_letova)  //za bezimene objekte
{
    letovi.PokNaLet = nullptr;
    letovi.ostvareni_letovi = 0;
}
Letovi& Letovi::operator= (const Letovi &letovi)
{
    //if(letovi.max_br_letova > max_br_letova) {
    // if(&letovi != this) {
    //     Let **novi_prostor = nullptr;
    //     novi_prostor = new Let*[letovi.max_br_letova] {};
    //     try {
    //         for(int i = 0; i != letovi.ostvareni_letovi; i++) novi_prostor[i] = new Let(*(letovi.PokNaLet[i]));
    //     } catch(...) {
    //         for(int i = 0; i < letovi.ostvareni_letovi; i++) {
    //             delete novi_prostor[i];
    //             novi_prostor[i] = nullptr;
    //         }
    //         delete[] novi_prostor;
    //     }
    //     for(int i = 0; i < ostvareni_letovi; i++) {
    //         delete PokNaLet[i];
    //         PokNaLet[i] = nullptr;
    //     }
    //     delete[] PokNaLet;
    //     PokNaLet = novi_prostor;
    //     max_br_letova = letovi.max_br_letova;
    //     ostvareni_letovi = letovi.ostvareni_letovi;
    // }
    if(&letovi != this) {
        Let ** novi_prostor = nullptr;
        try {
            novi_prostor = new Let*[letovi.max_br_letova] {};
            for(int i = 0; i != letovi.ostvareni_letovi; i++) novi_prostor[i] = new Let(*(letovi.PokNaLet[i]));
            for(int i = 0; i != ostvareni_letovi; i++) {
                delete  PokNaLet[i];
                PokNaLet[i] = nullptr;
            }
            delete[] PokNaLet;
            PokNaLet = novi_prostor;
            max_br_letova = letovi.max_br_letova;
            ostvareni_letovi = letovi.ostvareni_letovi;
        } catch(...) {
            for(int i = 0; i != letovi.ostvareni_letovi; i++) {
                delete novi_prostor[i];
                novi_prostor[i] = nullptr;
            }
            delete[] novi_prostor;
        }
        return *this;
    }
}
Letovi& Letovi::operator= (Letovi &&letovi)
{
    std::swap(letovi.max_br_letova, max_br_letova);
    std::swap(letovi.ostvareni_letovi, ostvareni_letovi);
    std::swap(letovi.PokNaLet, PokNaLet);
    return *this;
}
void Letovi::RegistrirajLet(const char odrediste[], const char oznaka_leta[],    int kapija, int sat_polaska, int minute_polaska, int trajanje_leta)
{
    if(ostvareni_letovi == max_br_letova) throw std::range_error ("Dostignut maksimalni broj letova");
    PokNaLet[ostvareni_letovi] = new Let(odrediste, oznaka_leta, kapija, sat_polaska, minute_polaska, trajanje_leta);
    ostvareni_letovi++;
}
void Letovi::RegistrirajLet(Let *let)
{
    if(ostvareni_letovi == max_br_letova) throw std::range_error ("Dostignut maksimalni broj letova");
    PokNaLet[ostvareni_letovi] = let;
    ostvareni_letovi++;
    let = nullptr;
}
int Letovi::DajBrojLetovaKojiKasne() const
{
    return std::count_if(PokNaLet, PokNaLet + ostvareni_letovi, [](Let *l) {
        if(l->DaLiKasni()) return true;
        return false;
    });
}
int Letovi::DajProsjecnoTrajanjeLetova() const
{
    int suma_trajanja = 0;
    for(int i = 0; i < ostvareni_letovi; i++) {
        suma_trajanja += PokNaLet[i]->DajTrajanjeLeta();
    }
    return suma_trajanja/ostvareni_letovi;
}
Let& Letovi::DajPrviLet() const
{
    if(ostvareni_letovi == 0) throw std::domain_error ("Nema registriranih letova");
    return **std::min_element(PokNaLet, PokNaLet + ostvareni_letovi, [](Let *let1, Let *let2) {
        if(let1->DajOcekivanoVrijemePolijetanja().first == let2->DajOcekivanoVrijemePolijetanja().first) {
            return let1->DajOcekivanoVrijemePolijetanja().second <= let2->DajOcekivanoVrijemePolijetanja().second;
        } else return let1->DajOcekivanoVrijemePolijetanja().first < let2->DajOcekivanoVrijemePolijetanja().first;
    });
}
Let& Letovi::DajPosljednjiLet() const
{
    if(ostvareni_letovi == 0) throw std::domain_error ("Nema registriranih letova");
    return **std::max_element(PokNaLet, PokNaLet + ostvareni_letovi, [](Let *let1, Let *let2) {
        if(let1->DajOcekivanoVrijemePolijetanja().first == let2->DajOcekivanoVrijemePolijetanja().first) {
            return let1->DajOcekivanoVrijemePolijetanja().second <= let2->DajOcekivanoVrijemePolijetanja().second;
        } else return let1->DajOcekivanoVrijemePolijetanja().first < let2->DajOcekivanoVrijemePolijetanja().first;
    });
}
void Letovi::IsprazniKolekciju()
{
    for(int i = 0; i < ostvareni_letovi; i++) {
        delete PokNaLet[i];   //??????????????????????????????
        PokNaLet[i] = nullptr;
    }
    ostvareni_letovi = 0;
}
void Letovi::Ispisi(int sati, int minute) const
{
    std::sort(PokNaLet, PokNaLet + ostvareni_letovi, [](Let *let1, Let *let2) {
        if(let1->DajOcekivanoVrijemePolijetanja().first == let2->DajOcekivanoVrijemePolijetanja().first) {
            return let1->DajOcekivanoVrijemePolijetanja().second <= let2->DajOcekivanoVrijemePolijetanja().second;
        } else return let1->DajOcekivanoVrijemePolijetanja().first < let2->DajOcekivanoVrijemePolijetanja().first;
    });
    std::for_each(PokNaLet, PokNaLet + ostvareni_letovi, [sati, minute](Let *l) {
        if(l->DajOcekivanoVrijemePolijetanja().first >= sati && l->DajOcekivanoVrijemePolijetanja().second >= minute) {
            l->Ispisi();
        }
    });
}



int main ()
{

    Letovi aerodrom_sa(3);
    Letovi aerodrom_bg(3);
    aerodrom_bg.RegistrirajLet("New York", "aaa",2, 12, 44, 65);
    aerodrom_bg.RegistrirajLet("LA", "bbb",1, 12, 17, 63);
    aerodrom_bg.RegistrirajLet("Amsterdam", "JK4",6, 17, 44, 123);
    aerodrom_sa.RegistrirajLet("Sarajevo", "aaa",2, 12, 44, 65);
    aerodrom_sa.RegistrirajLet("Zageb", "bbb",1, 12, 17, 63);
    aerodrom_sa.RegistrirajLet("Istanbul", "JK4",6, 17, 44, 123);
    aerodrom_sa = aerodrom_bg;
    std::cout<<"Posljedni let sa earodnoma: ";
    aerodrom_sa.DajPosljednjiLet().Ispisi();
    std::cout<<"Prvi let sa earodnoma: ";
    aerodrom_sa.DajPrviLet().Ispisi();
    std::cout<<"Prosjecno virjeme trajanje_leta na aerodnomu_sa: "<<aerodrom_sa.DajProsjecnoTrajanjeLetova()<<"min."<<std::endl;
    std::cout<<"Ukupan bro letova: "<<aerodrom_sa.DajBrojLetova()<<std::endl;
    std::cout<<"Broj letova koji kasne: "<<aerodrom_sa.DajBrojLetovaKojiKasne()<<std::endl;
    aerodrom_sa.Ispisi(0, 0);
    aerodrom_sa.IsprazniKolekciju();


    return 0;
}
