//TP 2018/2019: Zadaća 4, Zadatak 1
#include <iostream>
#include <utility>
#include <cmath>
#include <algorithm>
#include <stdexcept>
#include <vector>
#include <memory>
#include <sstream>

typedef std::pair<double, double> Tacka;
enum Pozicija {GoreLijevo, GoreDesno, DoljeLijevo, DoljeDesno};
enum Smjer {Nalijevo, Nadesno};

class NepreklapajuciPravougaonik
{
    Tacka DonjiLeftVrh, GornjLeftVrh, DonjiRightVrh, GornjiRightVrh, Centar;
    NepreklapajuciPravougaonik *PokIspred;
    static NepreklapajuciPravougaonik *PokZadnji;
    // void Nacrtaj(const Tacka &DL, const Tacka &DD, const Tacka &GL, const Tacka &GD){
    //     for(int i = -10; i<= 10; i++){
    //         for(int j = -10; j<= 10; j++){
    //             if((i == DL.first && j == DL.second) || (i == DD.first && j == DD.second) || (i == GL.first && j == GL.second) || (i == GD.first && j == GD.second)) std::cout<<"+";
    //             else std::cout<<" ";
    //         }
    //         std::cout<<std::endl;
    //     }
    // }
    void RotirajTacku(const Tacka &PivotPoint, Tacka &tacka, Smjer s)
    {
        //const double PIpola = (4 * atan(1))/2;
        tacka.first -= PivotPoint.first;
        tacka.second -= PivotPoint.second;
        double x = 0, y = 0;
        if(s == Nadesno) {
            // x = /*tacka.first * cos(-1*PIpola)*/ 0 + 1 * tacka.second ; //* sin(-1 * PIpola);
            // y = -1*tacka.first ; //* sin(-1 * PIpola) + tacka.second * cos(-1 *PIpola);
            x = tacka.second;
            y = -1 * tacka.first;
        } else if(s == Nalijevo) {
            //x = /*tacka.first * cos(PIpola) */- 1 * tacka.second ; //* sin(PIpola);
            //y = tacka.first ;//* sin(PIpola) + tacka.second * cos(PIpola);
            x = -1 * tacka.second;
            y = tacka.first;
        }
        tacka.first = x + PivotPoint.first;
        tacka.second = y + PivotPoint.second;
    }
    bool JeLiTacka() const
    {
        return (DonjiRightVrh == GornjiRightVrh) && (DonjiLeftVrh == GornjLeftVrh) && (DonjiRightVrh == DonjiLeftVrh);
    }
    bool JeLiDuz() const
    {
        if((JesuLiJednaki(0, DajHorizontalnu()) && !JesuLiJednaki(0, DajVertikalnu())) || (!JesuLiJednaki(0, DajHorizontalnu()) && JesuLiJednaki(0, DajVertikalnu()))) return true;
        return false;
    }
    static bool JesuLiJednaki(double x, double y, double Eps = 1e-10)
    {
        return std::fabs(x-y) <= Eps*(std::fabs(x) + std::fabs(y));
    }
    bool JeLiNepreklapajuciPravougaonik() const
    {
        if(!JesuLiJednaki(DajHorizontalnu(), 0) && !JesuLiJednaki(DajVertikalnu(), 0)) return true;
        return false;
    }
    void SwitchPlaces()
    {
        if(DonjiLeftVrh.first > DonjiRightVrh.first) {
            std::swap(DonjiRightVrh, DonjiLeftVrh);
            std::swap(GornjiRightVrh, GornjLeftVrh);
        }
        if(GornjiRightVrh.second < DonjiRightVrh.second) {
            std::swap(GornjiRightVrh, DonjiRightVrh);
            std::swap(GornjLeftVrh, DonjiLeftVrh);
        }
    }
    //provjera preklapanje provjeriti ovu funkciju
    bool ImaLiPreklapanja(const Tacka &t1, const Tacka &t2, const NepreklapajuciPravougaonik &p) const
    {
        double  desno = std::max(t1.first, t2.first);
        double lijevo = std::min(t1.first, t2.first);

        double  gore = std::max(t1.second, t2.second);
        double dole = std::min(t1.second, t2.second);
        auto horizontalno = std::min(p.DonjiRightVrh.first, desno) - std::max(p.DonjiLeftVrh.first, lijevo);
        auto vertikalno = std::min(p.GornjiRightVrh.second, gore) - std::max(p.DonjiLeftVrh.second, dole);
        if( horizontalno > 0 && vertikalno >0 ) return true;
        else return false;
    }
    bool PostojiLiVec(const Tacka &t1, const Tacka &t2)
    {
        for(auto i = PokZadnji; i != nullptr; i = i->PokIspred) {
            //auto m = ImaLiPreklapanja(t1, t2, *i);
            if(i != this && ImaLiPreklapanja(t1, t2, *i)) return true;
        }
        return false;
    }
    Tacka DajSuprotnoTjeme(Pozicija p) const
    {
        if(p == GoreDesno) return DonjiLeftVrh;
        if(p == DoljeLijevo) return GornjiRightVrh;
        if(p == GoreLijevo) return DonjiRightVrh;
        if(p == DoljeDesno) return GornjLeftVrh;
    }

public:
    NepreklapajuciPravougaonik(const Tacka &t1, const Tacka &t2);
    NepreklapajuciPravougaonik(const NepreklapajuciPravougaonik &p) = delete;
    NepreklapajuciPravougaonik &operator =(const NepreklapajuciPravougaonik &p) = delete;
    ~NepreklapajuciPravougaonik()
    {
        //posebni slucaji!!!!!!!!!!!!
        auto pomocna = this->PokIspred;
        NepreklapajuciPravougaonik *sljedeci;
        if(PokZadnji == this) {
            PokIspred = nullptr;
            PokZadnji = pomocna;

        } else {
            for(auto i = PokZadnji; i != nullptr; i = i->PokIspred) {
                if(this == i->PokIspred) {
                    sljedeci = i;
                    break;
                }
            }
            PokIspred = nullptr;
            sljedeci->PokIspred = pomocna;

        }
        //PokIspred =

    }
    void Postavi(const Tacka &t1, const Tacka &t2);
    void Postavi(Pozicija p, const Tacka &t);
    void Centriraj(const Tacka &t);
    Tacka DajTjeme(Pozicija p) const
    {
        if(p == DoljeDesno) return DonjiRightVrh;
        if(p == GoreDesno) return GornjiRightVrh;
        if(p == DoljeLijevo) return DonjiLeftVrh;
        if(p == GoreLijevo) return GornjLeftVrh;
    }
    Tacka DajCentar() const
    {
        return Centar;
    }
    double DajHorizontalnu() const
    {
        return DonjiRightVrh.first - DonjiLeftVrh.first;
    }
    double DajVertikalnu() const
    {
        return GornjiRightVrh.second - DonjiRightVrh.second;
    }
    double DajObim() const
    {
        //PROVJERITI
        if(JeLiTacka()) return 0;
        return 2*DajHorizontalnu() + 2*DajVertikalnu();
    }
    double DajPovrsinu() const
    {
        if(JeLiDuz() || JeLiTacka()) return 0;
        return DajHorizontalnu() * DajVertikalnu();
    }
    //static NepreklapajuciPravougaonik Presjek(const NepreklapajuciPravougaonik &p1, const NepreklapajuciPravougaonik &p2);
    void Transliraj(double delta_x, double delta_y);
    void Rotiraj(const Tacka &t, Smjer s);
    void Ispisi() const
    {
        std::cout<<"{{"<<GornjLeftVrh.first<<","<<GornjLeftVrh.second<<"},{"<<DonjiRightVrh.first<<","<<DonjiRightVrh.second<<"}}";
    }
    friend bool DaLiSePoklapaju(const NepreklapajuciPravougaonik &p1, const NepreklapajuciPravougaonik &p2);
    friend bool DaLiSuPodudarni(const NepreklapajuciPravougaonik &p1, const NepreklapajuciPravougaonik &p2);
    friend bool DaLiSuSlicni(const NepreklapajuciPravougaonik &p1, const NepreklapajuciPravougaonik &p2);
};
NepreklapajuciPravougaonik* NepreklapajuciPravougaonik::PokZadnji = nullptr;
NepreklapajuciPravougaonik::NepreklapajuciPravougaonik(const Tacka &t1, const Tacka &t2)
{
    try {
        Postavi(t1, t2);
        if(PokZadnji == nullptr) {
            PokIspred = nullptr;
            PokZadnji = this;

        } else {
            PokIspred = PokZadnji;
            PokZadnji = this;
        }
    } catch(...) {
        throw;
    }
}
void NepreklapajuciPravougaonik::Postavi(const Tacka &t1, const Tacka &t2)
{
    if(PostojiLiVec(t1, t2))
        throw std::logic_error("Nedozvoljeno preklapanje");
    if((t1.first < t2.first) && !JesuLiJednaki(t1.first, t2.first) && (t1.second < t2.second) && !JesuLiJednaki(t1.second, t2.second)) {
        DonjiLeftVrh = t1;
        GornjiRightVrh = t2;
        DonjiRightVrh.first = GornjiRightVrh.first;
        DonjiRightVrh.second = DonjiLeftVrh.second;
        GornjLeftVrh.first = DonjiLeftVrh.first;
        GornjLeftVrh.second = GornjiRightVrh.second;
    } else if((t2.first < t1.first) && !JesuLiJednaki(t1.first, t2.first) && (t2.second < t1.second) && !JesuLiJednaki(t1.first, t2.first)) {
        DonjiLeftVrh = t2;
        GornjiRightVrh = t1;
        DonjiRightVrh.first = GornjiRightVrh.first;
        DonjiRightVrh.second = DonjiLeftVrh.second;
        GornjLeftVrh.first = DonjiLeftVrh.first;
        GornjLeftVrh.second = GornjiRightVrh.second;
    } else if(t1.first > t2.first && t1.second < t2.second) {
        DonjiRightVrh = t1;
        GornjLeftVrh = t2;
        DonjiLeftVrh.first = GornjLeftVrh.first;
        DonjiLeftVrh.second = DonjiRightVrh.second;
        GornjiRightVrh.first = DonjiRightVrh.first;
        GornjiRightVrh.second = GornjLeftVrh.second;

    } else if(t1.first < t2.first && t1.second > t2.second) {
        DonjiRightVrh = t2;
        GornjLeftVrh = t1;
        DonjiLeftVrh.first = GornjLeftVrh.first;
        DonjiLeftVrh.second = DonjiRightVrh.second;
        GornjiRightVrh.first = DonjiRightVrh.first;
        GornjiRightVrh.second = GornjLeftVrh.second;
    } else if(JesuLiJednaki(t1.first, t2.first) && JesuLiJednaki(t1.second, t2.second) ) {
        GornjLeftVrh = t1;
        GornjiRightVrh = t1;
        DonjiLeftVrh = t1;
        DonjiRightVrh = t1;
    } else if(JesuLiJednaki(t1.first, t2.first)) {
        if(t1.second < t2.second) {
            DonjiRightVrh = t1;
            DonjiLeftVrh = DonjiRightVrh;
            GornjiRightVrh = t2;
            GornjLeftVrh = GornjiRightVrh;
        } else {
            DonjiRightVrh = t2;
            DonjiLeftVrh = DonjiRightVrh;
            GornjiRightVrh = t1;
            GornjLeftVrh = GornjiRightVrh;
        }
    } else if(JesuLiJednaki(t1.second, t2.second)) {
        if(t1.first < t2.first) {
            DonjiLeftVrh = t1;
            GornjLeftVrh = DonjiLeftVrh;
            DonjiRightVrh = t2;
            GornjiRightVrh = DonjiRightVrh;
        } else {
            DonjiLeftVrh = t2;
            GornjLeftVrh = DonjiLeftVrh;
            DonjiRightVrh = t1;
            GornjiRightVrh = DonjiRightVrh;
        }
    }
    Centar.first = (DonjiRightVrh.first - DonjiLeftVrh.first) / 2 + DonjiLeftVrh.first;
    Centar.second = (GornjiRightVrh.second - DonjiRightVrh.second) / 2 + DonjiRightVrh.second;
    // Nacrtaj(DonjiLeftVrh, DonjiRightVrh, GornjLeftVrh, GornjiRightVrh);
}
void NepreklapajuciPravougaonik::Postavi(Pozicija p, const Tacka &t)
{
    if(PostojiLiVec(t, DajSuprotnoTjeme(p))) throw std::logic_error("Nedozvoljeno preklapanje");
    if(p == GoreDesno) {
        GornjiRightVrh = t;
        DonjiRightVrh.first = GornjiRightVrh.first;
        GornjLeftVrh.second = GornjiRightVrh.second;
    } else if(p == GoreLijevo) {
        GornjLeftVrh = t;
        DonjiLeftVrh.first = GornjLeftVrh.first;
        GornjiRightVrh.second = GornjLeftVrh.second;

    } else if(p == DoljeDesno) {
        DonjiRightVrh = t;
        GornjiRightVrh.first = DonjiRightVrh.first;
        DonjiLeftVrh.second = DonjiRightVrh.second;

    } else if(p == DoljeLijevo) {
        DonjiLeftVrh = t;
        GornjLeftVrh.first = DonjiLeftVrh.first;
        DonjiRightVrh.second = DonjiLeftVrh.second;

    }
    SwitchPlaces();
    //Nacrtaj(DonjiLeftVrh, DonjiRightVrh, GornjLeftVrh, GornjiRightVrh);
    Centar.first = (DonjiRightVrh.first - DonjiLeftVrh.first) / 2 + DonjiLeftVrh.first;
    Centar.second = (GornjiRightVrh.second - DonjiRightVrh.second) / 2 + DonjiRightVrh.second;
}
void NepreklapajuciPravougaonik::Centriraj(const Tacka &t)
{

    auto delta_x = t.first - Centar.first;
    auto delta_y = t.second - Centar.second;
    Transliraj(delta_x, delta_y);

}
void NepreklapajuciPravougaonik::Transliraj(double delta_x, double delta_y)
{
    Tacka provjera1 = {DonjiLeftVrh.first + delta_x, DonjiLeftVrh.second + delta_y};
    Tacka provjera2 = {GornjiRightVrh.first + delta_x, GornjiRightVrh.second + delta_y};
    if(PostojiLiVec(provjera1, provjera2)) throw std::logic_error ("Nedozvoljeno preklapanje");
    DonjiLeftVrh.first += delta_x;
    DonjiLeftVrh.second += delta_y;
    GornjiRightVrh.first += delta_x;
    GornjiRightVrh.second += delta_y;
    Postavi(DonjiLeftVrh, GornjiRightVrh);

}
void NepreklapajuciPravougaonik::Rotiraj(const Tacka &t, Smjer s)
{
    auto provjera1 = DonjiLeftVrh;
    auto provjera2 = GornjiRightVrh;
    RotirajTacku(t, provjera1, s);
    RotirajTacku(t, provjera2, s);
    if(PostojiLiVec(provjera1, provjera2)) throw std::logic_error ("Nedozvoljeno preklapanje");
    // RotirajTacku(t, DonjiLeftVrh, s);
    // RotirajTacku(t, GornjiRightVrh, s);
    DonjiLeftVrh = provjera1;
    GornjiRightVrh = provjera2;
    Postavi(DonjiLeftVrh, GornjiRightVrh);
    //Nacrtaj(DonjiLeftVrh, DonjiRightVrh, GornjLeftVrh, GornjiRightVrh);

}

bool DaLiSePoklapaju(const NepreklapajuciPravougaonik &p1, const NepreklapajuciPravougaonik &p2)
{
    if(p1.DonjiRightVrh == p2.DonjiRightVrh && p1.GornjLeftVrh == p2.GornjLeftVrh) return true;
    return false;
}
bool DaLiSuPodudarni(const NepreklapajuciPravougaonik &p1, const NepreklapajuciPravougaonik &p2)
{
    if((NepreklapajuciPravougaonik::JesuLiJednaki(p1.DajHorizontalnu(), p2.DajHorizontalnu()) && NepreklapajuciPravougaonik::JesuLiJednaki(p1.DajVertikalnu(), p2.DajVertikalnu())) || (NepreklapajuciPravougaonik::JesuLiJednaki(p1.DajHorizontalnu(), p2.DajVertikalnu()) && NepreklapajuciPravougaonik::JesuLiJednaki(p1.DajVertikalnu(), p2.DajHorizontalnu()))) return true;
    return false;
}
//Popravila
bool DaLiSuSlicni(const NepreklapajuciPravougaonik &p1, const NepreklapajuciPravougaonik &p2)
{
    // p1.JeLiNepreklapajuciPravougaonik();
    // p2.JeLiNepreklapajuciPravougaonik();
    if((p1.JeLiTacka() && p2.JeLiTacka()) || (p1.JeLiDuz() && p2.JeLiDuz())) return true;
    if((p1.JeLiTacka() && p2.JeLiDuz()) || (p1.JeLiDuz() && p2.JeLiTacka())) return false;//pitati capu za ovo
    if((p1.JeLiNepreklapajuciPravougaonik() && !p2.JeLiNepreklapajuciPravougaonik()) || (!p1.JeLiNepreklapajuciPravougaonik() && p2.JeLiNepreklapajuciPravougaonik())) return false;
    if(p1.DajHorizontalnu()/p1.DajVertikalnu() == p2.DajHorizontalnu()/p2.DajVertikalnu()) return true; // U CIJELOM PROGRAMU FALI ROVJERA ZA TACKU I DUZ!!!
    return false;

}



int main ()
{

    typedef std::shared_ptr<NepreklapajuciPravougaonik> PokNaPravougaonik;
    int n;
    std::cout<<"Unesite n: ";
    std::cin>>n;
    std::vector<PokNaPravougaonik> VektorPok;
    bool nepravilan_unos = true;
    while(nepravilan_unos) {
        for(int i = 0; i < n; i++) {
            double x1, y1, x2, y2;

            for(int j = 0; j < 2; j++) {
                if(j == 0) {
                    std::cout<<"Unesite 1. tjeme pravougaonika "<<i+1<<": ";
                    std::cin>>x1>>y1;
                } else {
                    std::cout<<"Unesite 2. tjeme pravougaonika "<<i+1<<": ";
                    std::cin>>x2>>y2;
                }
            }
            try {
                VektorPok.push_back(std::make_shared<NepreklapajuciPravougaonik>(std::make_pair(x1,y1), std::make_pair(x2,y2)));
                nepravilan_unos = false;
            } catch(std::logic_error e) {
                std::cout<<"GRESKA: "<<e.what()<<"! Ponovite unos: "<<std::endl;
                i--;
            }
        }
    }
    std:sort(VektorPok.begin(), VektorPok.end(), [](PokNaPravougaonik p1, PokNaPravougaonik p2){
        return p1->DajPovrsinu() < p2->DajPovrsinu();
    });
    std::cout<<"Ispis pravougaonika nakon sortiranja: "<<std::endl;
    std::for_each(VektorPok.begin(), VektorPok.end(), [](PokNaPravougaonik p){
        p->Ispisi();
        std::cout<<std::endl;
    });
    std::cout<<"Podudarni pravougaonici: "<<std::endl;
    bool podudarni = false;
    for(auto i = VektorPok.begin(); i != VektorPok.end() - 1; i++){
        if(DaLiSuPodudarni(**i, **(i+1))){
            (*i)->Ispisi();
            std::cout<<" i ";
            (*(i+1))->Ispisi();
            std::cout<<std::endl;
            podudarni = true;
        }
    }
    if(!podudarni) std::cout<<"Nema podudarnih pravougaonika.";

    return 0;
}
