#include <iostream>
#include <cmath>
#include <iomanip>

class Sat
{
    int sat, minuta, sekunda;

public:
    static bool DaLiJeIspravno(int sat, int minuta, int sekunda);
    Sat()
    {
        sat = 0;
        minuta = 0;
        sekunda = 0;
    }
    Sat(int h, int min, int s)
    {
        PostaviNormalizirano(h, min, s);
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
        sat = h;
        minuta = min;
        sekunda = s;
    }
    Sat &operator ++()
    {
        sekunda++;
        PostaviNormalizirano(sat, minuta, sekunda);
        return *this;
    }
    Sat operator ++(int)
    {
        auto pomocna = *this;
        sekunda++;
        PostaviNormalizirano(sat, minuta, sekunda);
        return pomocna;
    }

    Sat &operator --()
    {
        sekunda--;
        PostaviNormalizirano(sat, minuta, sekunda);
        return *this;
    }
    Sat operator --(int)
    {
        auto pomocna = *this;
        sekunda--;
        PostaviNormalizirano(sat, minuta, sekunda);
        return pomocna;
    }
    Sat &operator +=( int pomak)
    {
        if(pomak > 0)
            while(pomak) {
                ++*this;
                pomak --;
            }
        if(pomak < 0)	{
            pomak = std::abs(pomak);
            while(pomak != 0) {
                --*this;
                pomak--;
            }
        }
        return *this;
    }
    Sat &operator -=( int pomak)
    {
        //if(pomak < 0)	{
        pomak = std::abs(pomak);
        while(pomak != 0) {
            --*this;;
            pomak--;
        }
        //}
        return *this;
    }
    
    int DajSate() const
    {
        return sat;
    }
    int DajMinute() const
    {
        return minuta;
    }
    int DajSekunde() const
    {
        return sekunda;
    }
    friend int operator -(const Sat &sat1, const Sat &sat2);
    friend Sat operator -(const Sat &sat, int sekunde);
    friend Sat operator +(const Sat &sat, int sekunde);
    friend std::ostream &operator <<(std::ostream &tok, const Sat &s);
    //static int Razmak(const Sat &sat1, const Sat &sat2);




};
bool Sat::DaLiJeIspravno(int sat, int minuta, int sekunda)
{
    if(sat < 0 || sat > 23 || minuta < 0 || minuta > 59 || sekunda < 0 || sekunda > 59) return false;
    return true;
}
int operator -(const Sat &sat1, const Sat &sat2)
{
    int sek_izmedju;
    sek_izmedju = sat1.sekunda - sat2.sekunda;
    sek_izmedju += (sat1.minuta - sat2.minuta) * 60;
    sek_izmedju += (sat1.sat - sat2.sat)* 3600;
    return sek_izmedju;
}
Sat operator -(const Sat &sat, int sekunde)
{
    auto pomocna = sat;
    pomocna-=sekunde;
    return pomocna;
}
Sat operator +(const Sat &sat, int sekunde)
{
    auto pomocna = sat;
    pomocna+=sekunde;
    return pomocna;
}
std::ostream &operator <<(std::ostream &tok, const Sat &s)
{
    tok<<std::setw(2)<<std::setfill('0')<<s.DajSate()<<":"<<std::setw(2)<<std::setfill('0')<<s.DajMinute()<<":"<<std::setw(2)<<std::setfill('0')<<s.DajSekunde();
    return tok;
}
// int Sat::Razmak(const Sat &sat1, const Sat &sat2)
// {
//     int sek_izmedju;
//     sek_izmedju = sat1.sekunda - sat2.sekunda;
//     sek_izmedju += (sat1.minuta - sat2.minuta) * 60;
//     sek_izmedju += (sat1.sat - sat2.sat)* 3600;
//     return sek_izmedju;
// }
int main ()
{

    // S//AT1 testiranje konstruktora
    Sat s1(20, 4, 39);
    std::cout << s1 << std::endl;
    Sat s2(25, 150, 290);
    std::cout << s2 << std::endl;
    Sat s3;
    std::cout << s3 << std::endl;
    return 0;
}
