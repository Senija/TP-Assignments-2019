#include <iostream>
#include <cmath>
#include <iomanip>

class Sat
{
    int ukupno_sek;

public:
    static bool DaLiJeIspravno(int sat, int minuta, int sekunda);
    void Postavi(int h, int min, int s)
    {
        if(!DaLiJeIspravno(h, min, s)) throw std::domain_error ("Neispravno vrijeme");
        ukupno_sek = h*3600 + min*60 + s;
    }
    void PostaviNormalizirano(int h, int min, int s)
    {
        while(s < 0) {
            s = 60 +s;
            min--;
        }
        while(min < 0) {
            min = 60 + min;
            h--;
        }
        while(h < 0) {
            h = 24 + h;
        }
        if(s > 59) {
            min += s / 60;
            s = s % 60;
        }
        if(min > 59) {
            h += min / 60;
            min = min % 60;
        }
        if(h > 23) h = h % 24;
        if(s < 0 ) {
            s = 60 + s;
        }
        ukupno_sek = 3600 * h + 60 * min + s;
    }
    Sat &Sljedeci()
    {
        ukupno_sek++;
        int min = ukupno_sek / 60;
        int s =  ukupno_sek % 60;
        int h = min / 60;
        if(min > 59) min = min % 60;
        PostaviNormalizirano(h, min, s);
        return *this;
    }
    Sat &Prethodni()
    {
        ukupno_sek--;
        int min = ukupno_sek / 60;
        int s =  ukupno_sek % 60;
        int h = min / 60;
        if(min > 59) min = min % 60;
        PostaviNormalizirano(h, min, s);
        return *this;
    }
    Sat &PomjeriZa( int pomak)
    {
        if(pomak > 0)
            while(pomak) {
                Sljedeci();
                pomak --;
            }
        if(pomak < 0)	{
            pomak = std::abs(pomak);
            while(pomak != 0) {
                Prethodni();
                pomak--;
            }
        }
        return *this;
    }
    void Ispisi() const
    {
        int minuta = ukupno_sek / 60;
        int sekunda = ukupno_sek % 60;
        int sat = minuta / 60;
        if(minuta > 59) minuta = minuta % 60;
        std::cout<<std::setw(2)<<std::setfill('0')<<sat<<":"<<std::setw(2)<<std::setfill('0')<<minuta<<":"<<std::setw(2)<<std::setfill('0')<<sekunda;
    }
    int DajSate() const
    {
        return ukupno_sek/3600;
    }
    int DajMinute() const
    {
        int minuta = ukupno_sek/60;
        if(minuta > 59) minuta = minuta % 60;
        return minuta;
    }
    int DajSekunde() const
    {
        return ukupno_sek % 60;
    }
    friend int BrojSekundiIzmedju(const Sat &sat1, const Sat &sat2);
    static int Razmak(const Sat &sat1, const Sat &sat2);




};
bool Sat::DaLiJeIspravno(int sat, int minuta, int sekunda)
{
    if(sat < 0 || sat > 23 || minuta < 0 || minuta > 59 || sekunda < 0 || sekunda > 59) return false;
    return true;
}
int BrojSekundiIzmedju(const Sat &sat1, const Sat &sat2)
{
    return sat1.ukupno_sek - sat2.ukupno_sek;
}
int Sat::Razmak(const Sat &sat1, const Sat &sat2)
{
    return sat1.ukupno_sek - sat2.ukupno_sek;
}
int main ()
{
    Sat s;
    s.Postavi(10,10,10);
    std::cout << s.DajSate() << " "
              << s.DajMinute() << " "
              << s.DajSekunde();

    return 0;
}
