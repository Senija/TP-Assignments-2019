//TP 2018/2019: Zadaća 4, Zadatak 1
#include <iostream>
#include <utility>
#include <cmath>
#include <algorithm>
#include <stdexcept>
typedef std::pair<double, double> Tacka;
enum Pozicija {GoreLijevo, GoreDesno, DoljeLijevo, DoljeDesno};
enum Smjer {Nalijevo, Nadesno};

class Pravougaonik
{
    Tacka DonjiLeftVrh, GornjLeftVrh, DonjiRightVrh, GornjiRightVrh, Centar;
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
        const double PIpola = (4 * atan(1))/2;
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
    static bool JesuLiJednaki(double x, double y, double Eps = 1e-10){
        return std::fabs(x-y) <= Eps*(std::fabs(x) + std::fabs(y));
    }
    bool JeLiPravougaonik() const{
        if(!JesuLiJednaki(DajHorizontalnu(), 0) && !JesuLiJednaki(DajVertikalnu(), 0)) return true;
        return false;
    }
    void SwitchPlaces(){
        if(DonjiLeftVrh.first > DonjiRightVrh.first){
            std::swap(DonjiRightVrh, DonjiLeftVrh);
            std::swap(GornjiRightVrh, GornjLeftVrh);
        }
        if(GornjiRightVrh.second < DonjiRightVrh.second){
            std::swap(GornjiRightVrh, DonjiRightVrh);
            std::swap(GornjLeftVrh, DonjiLeftVrh);
        }
    }
//     bool JesuLiJednaki(double x, double y, double Eps = 1e–10) {
//  return std::fabs(x – y) <= Eps * (std::fabs(x) + std::fabs(y));
// }


public:
    Pravougaonik(const Tacka &t1, const Tacka &t2);
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
    static Pravougaonik Presjek(const Pravougaonik &p1, const Pravougaonik &p2);
    void Transliraj(double delta_x, double delta_y);
    void Rotiraj(const Tacka &t, Smjer s);
    void Ispisi() const
    {
        std::cout<<"{{"<<GornjLeftVrh.first<<","<<GornjLeftVrh.second<<"},{"<<DonjiRightVrh.first<<","<<DonjiRightVrh.second<<"}}";
    }
    friend bool DaLiSePoklapaju(const Pravougaonik &p1, const Pravougaonik &p2);
    friend bool DaLiSuPodudarni(const Pravougaonik &p1, const Pravougaonik &p2);
    friend bool DaLiSuSlicni(const Pravougaonik &p1, const Pravougaonik &p2);
};
Pravougaonik::Pravougaonik(const Tacka &t1, const Tacka &t2)
{
    Postavi(t1, t2);
}
void Pravougaonik::Postavi(const Tacka &t1, const Tacka &t2)
{
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
void Pravougaonik::Postavi(Pozicija p, const Tacka &t)
{
    if(p == GoreDesno) {
        GornjiRightVrh = t;
        DonjiRightVrh.first = GornjiRightVrh.first;
        GornjLeftVrh.second = GornjiRightVrh.second;
    }
    if(p == GoreLijevo) {
        GornjLeftVrh = t;
        DonjiLeftVrh.first = GornjLeftVrh.first;
        GornjiRightVrh.second = GornjLeftVrh.second;

    }
    if(p == DoljeDesno) {
        DonjiRightVrh = t;
        GornjiRightVrh.first = DonjiRightVrh.first;
        DonjiLeftVrh.second = DonjiRightVrh.second;

    }
    if(p == DoljeLijevo) {
        DonjiLeftVrh = t;
        GornjLeftVrh.first = DonjiLeftVrh.first;
        DonjiRightVrh.second = DonjiLeftVrh.second;

    }
    SwitchPlaces();
    //Nacrtaj(DonjiLeftVrh, DonjiRightVrh, GornjLeftVrh, GornjiRightVrh);
    Centar.first = (DonjiRightVrh.first - DonjiLeftVrh.first) / 2 + DonjiLeftVrh.first;
    Centar.second = (GornjiRightVrh.second - DonjiRightVrh.second) / 2 + DonjiRightVrh.second;
}
void Pravougaonik::Centriraj(const Tacka &t)
{

    auto delta_x = t.first - Centar.first;
    auto delta_y = t.second - Centar.second;
    Transliraj(delta_x, delta_y);

}
void Pravougaonik::Transliraj(double delta_x, double delta_y)
{
    DonjiLeftVrh.first += delta_x;
    DonjiLeftVrh.second += delta_y;
    //DonjiRightVrh.first += delta_x;
    GornjiRightVrh.first += delta_x;
    GornjiRightVrh.second += delta_y;
    //GornjLeftVrh.first += delta_x;
    //DonjiLeftVrh.second += delta_y;
    // DonjiRightVrh.second += delta_y;
    // GornjiRightVrh.second += delta_y;
    // GornjLeftVrh.second += delta_y;
    // Centar.first += delta_x;
    // Centar.second += delta_y;
    Postavi(DonjiLeftVrh, GornjiRightVrh);

}
void Pravougaonik::Rotiraj(const Tacka &t, Smjer s)
{
    RotirajTacku(t, DonjiLeftVrh, s);
    RotirajTacku(t, GornjiRightVrh, s);
    Postavi(DonjiLeftVrh, GornjiRightVrh);
    //Nacrtaj(DonjiLeftVrh, DonjiRightVrh, GornjLeftVrh, GornjiRightVrh);

}
Pravougaonik Pravougaonik::Presjek(const Pravougaonik &p1, const Pravougaonik &p2)
{
    if((p1.DonjiRightVrh.first >= p2.DonjiLeftVrh.first) && (p1.DonjiLeftVrh.first <= p2.DonjiRightVrh.first) && (p1.GornjiRightVrh.second >= p2.DonjiRightVrh.second) && (p1.DonjiRightVrh.second <= p2.GornjiRightVrh.second)) {
        Tacka DonjiLijevi, GornjiDesni;
        DonjiLijevi.first = std::max((p1.DajTjeme(DoljeLijevo)).first, (p2.DajTjeme(DoljeLijevo)).first);
        DonjiLijevi.second = std::max((p1.DajTjeme(DoljeLijevo)).second, (p2.DajTjeme(DoljeLijevo)).second);
        GornjiDesni.first = std::min((p1.DajTjeme(GoreDesno)).first, (p2.DajTjeme(GoreDesno)).first);
        GornjiDesni.second = std::min((p1.DajTjeme(GoreDesno)).second, (p2.DajTjeme(GoreDesno)).second);
        return Pravougaonik(DonjiLijevi, GornjiDesni);
    } else throw std::domain_error ("Pravougaonici se ne presjecaju");
}
//OVO NISTA NE VALJA MOZE PUNO BOLJE
bool DaLiSePoklapaju(const Pravougaonik &p1, const Pravougaonik &p2)
{
    if(p1.DonjiRightVrh == p2.DonjiRightVrh && p1.GornjLeftVrh == p2.GornjLeftVrh) return true;
    return false;
}
bool DaLiSuPodudarni(const Pravougaonik &p1, const Pravougaonik &p2)
{
    if((Pravougaonik::JesuLiJednaki(p1.DajHorizontalnu(), p2.DajHorizontalnu()) && Pravougaonik::JesuLiJednaki(p1.DajVertikalnu(), p2.DajVertikalnu())) || (Pravougaonik::JesuLiJednaki(p1.DajHorizontalnu(), p2.DajVertikalnu()) && Pravougaonik::JesuLiJednaki(p1.DajVertikalnu(), p2.DajHorizontalnu()))) return true;
    return false;
}
//Popravila
bool DaLiSuSlicni(const Pravougaonik &p1, const Pravougaonik &p2)
{
    // p1.JeLiPravougaonik();
    // p2.JeLiPravougaonik();
    if(p1.JeLiTacka() || p2.JeLiTacka()) return true;
    if(p1.JeLiDuz() && p2.JeLiDuz()) return true;
    //if((p1.JeLiTacka() && p2.JeLiDuz()) || (p1.JeLiDuz() && p2.JeLiTacka())) return false;/
    if((p1.JeLiPravougaonik() && !p2.JeLiPravougaonik()) || (!p1.JeLiPravougaonik() && p2.JeLiPravougaonik())) return false;
    if((p1.DajHorizontalnu()/p1.DajVertikalnu() != p2.DajHorizontalnu()/p2.DajVertikalnu()) && (p1.DajHorizontalnu()/p1.DajVertikalnu() != p2.DajVertikalnu()/p2.DajHorizontalnu())) return false; // U CIJELOM PROGRAMU FALI ROVJERA ZA TACKU I DUZ!!!
    return true;

}



int main ()
{
    //ovdje program
    int n;
    std::cout<<"Unesite n: ";
    std::cin>>n;
    Pravougaonik **DupliNaPravougaonike = nullptr;
    try {
        DupliNaPravougaonike = new Pravougaonik*[n];
        try {
            for(int i = 0; i < n; i++) {
                Tacka t1, t2;
                for(int j = 0; j < 2; j++) {
                    double x1, y1;
                    std::cout<<"Unesite "<<j+1<<". tjeme pravougaonika "<<i+1<<": ";
                    std::cin>>x1>>y1;
                    if(j == 0) t1 = {x1, y1};
                    else t2 = {x1, y1};
                    
                }
                DupliNaPravougaonike[i] = new Pravougaonik(t1, t2);

            }
            std::cout<<"Unesite podatke za transliranje (dx dy): ";
            double delta_x, delta_y;
            std::cin>>delta_x>>delta_y;
            std::transform(DupliNaPravougaonike, DupliNaPravougaonike + n, DupliNaPravougaonike, [delta_x, delta_y] (Pravougaonik *p) {
                p->Transliraj(delta_x, delta_y);
                p->Rotiraj(p->DajCentar(), Nadesno);
                return p;
            });
            std::cout<<"Pravougaonici, nakon transformacija:"<<std::endl;
            std::for_each(DupliNaPravougaonike, DupliNaPravougaonike + n, [](Pravougaonik *p) {
                p->Ispisi();
                std::cout<<std::endl;
            });
            auto PokMaxPovrsina = *std::max_element(DupliNaPravougaonike, DupliNaPravougaonike + n, [](Pravougaonik *p1, Pravougaonik *p2) {
                return p1->DajPovrsinu() < p2->DajPovrsinu();
            });
            std::cout<<"Pravougaonik s najvecom povrsinom: ";
            if(PokMaxPovrsina != *DupliNaPravougaonike + n) PokMaxPovrsina->Ispisi();
            for(int i = 0; i<n; i++) delete DupliNaPravougaonike[i];
            delete[] DupliNaPravougaonike;
        } catch(...) {
            for(int i = 0; i < n; i++) delete DupliNaPravougaonike[i];
            throw;
        }
    } catch(...) {
        delete[] DupliNaPravougaonike;
    }
    return 0;
}
