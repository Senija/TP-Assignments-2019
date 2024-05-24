#include <iostream>
#include <vector>
#include <stdexcept>
#include <algorithm>
#include <functional>

class Padavine
{
    std::vector<int> padavine;
    int max_kolicina;

public:

    explicit Padavine(int MaxKolicina)
    {
        if(MaxKolicina < 0) throw std::range_error ("Ilegalna maksimalna kolicina");
        max_kolicina = MaxKolicina;
    }

    void RegistrirajPadavine(int nova_padavina)
    {
        if(nova_padavina < 0 || nova_padavina > max_kolicina) throw std::range_error("Ilegalna kolicina padavina");
        padavine.push_back(nova_padavina);
    }

    int DajBrojRegistriranihPadavina() const
    {
        return padavine.size();
    }

    void BrisiSve()
    {
        padavine.resize(0);
    }

    int DajMinimalnuKolicinuPadavina() const;

    int DajMaksimalnuKolicinuPadavina() const;

    int DajBrojDanaSaPadavinamaVecimOd(int granica) const;

    void Ispisi() const;

    int operator [](int index) const
    {
        if(index > padavine.size()) throw std::range_error ("Neispravan indeks");
        return padavine[index - 1];
    }

    Padavine &operator ++();
    Padavine operator ++(int);
    Padavine& operator +=(int x);
    Padavine& operator -=(int x); // ovdje vise verzija
    Padavine& operator -=(const Padavine &p);
    Padavine operator -() const;
    friend bool operator ==(const Padavine &p1, const Padavine &p2);
    friend bool operator !=(const Padavine &p1, const Padavine &p2);
    friend Padavine operator+ (const Padavine &p, int x);
    friend Padavine operator+ (int x, const Padavine &p);
    friend Padavine operator- (const Padavine &p, int x);
    friend Padavine operator- (int x, const Padavine &p);
    friend Padavine operator- (const Padavine &p1, const Padavine &p2);
};

int Padavine::DajMinimalnuKolicinuPadavina() const
{
    if(padavine.size() == 0) throw std::range_error ("Nema registriranih padavina");
    auto min_kolicina = *min_element(padavine.begin(), padavine.end());
    return min_kolicina;
}


int Padavine::DajMaksimalnuKolicinuPadavina() const
{
    if(padavine.size() == 0) throw std::range_error ("Nema registriranih padavina");
    auto max = *max_element(padavine.begin(), padavine.end());
    return max;
}


int Padavine::DajBrojDanaSaPadavinamaVecimOd(int granica) const
{
    if(padavine.size() == 0) throw std::range_error ("Nema registriranih padavina");
    auto broj = std::count_if(padavine.begin(), padavine.end(), std::bind(std::greater<int>(), std::placeholders::_1, granica));
    return broj;
}

void Padavine::Ispisi() const
{
    auto padavineNo2 = padavine;
    std::sort(padavineNo2.begin(), padavineNo2.end(), std::greater<int>());
    for_each(padavineNo2.begin(), padavineNo2.end(), [](int padavina) {
        std::cout<<padavina<<std::endl;
    });
}

Padavine& Padavine::operator ++()
{
    ++max_kolicina;
    std::vector<int> Jedinice(padavine.size(), 1);
    std::transform(padavine.begin(), padavine.end(), Jedinice.begin(), padavine.begin(), std::plus<int>());
    return *this;
}

Padavine Padavine::operator ++(int)
{
    // TREBA LI POVECATI MAX VRIJEDNOST???
    max_kolicina++;
    auto temp = *this;
    std::vector<int> Jedinice(padavine.size(), 1);
    std::transform(padavine.begin(), padavine.end(), Jedinice.begin(), padavine.begin(), std::plus<int>());
    return temp;

}

Padavine operator+(const  Padavine &p, int x)
{
    if((p.DajMinimalnuKolicinuPadavina() + x) < 0) throw std::domain_error ("Nekorektan rezultat operacije");
    std::vector<int> SaberiSa(p.padavine.size(), x);
    Padavine Novi(p.max_kolicina + x); // ovo upitno
    Novi.padavine.resize(p.padavine.size());
    std::transform(p.padavine.begin(), p.padavine.end(), SaberiSa.begin(), Novi.padavine.begin(), std::plus<int>());
    return Novi;
}

Padavine operator +(int x, const Padavine &p)
{
    if((p.DajMinimalnuKolicinuPadavina() + x) < 0) throw std::domain_error ("Nekorektan rezultat operacije");
    std::vector<int> SaberiSa(p.padavine.size(), x);
    Padavine Novi(p.max_kolicina + x); // ovo upitno
    Novi.padavine.resize(p.padavine.size());
    std::transform(p.padavine.begin(), p.padavine.end(), SaberiSa.begin(), Novi.padavine.begin(), std::plus<int>());
    return Novi;
}

Padavine operator -(const Padavine &p, int x)
{
    if((p.DajMinimalnuKolicinuPadavina() - x) < 0) throw std::domain_error ("Nekorektan rezultat operacije");
    std::vector<int> Oduzmi(p.padavine.size(), x);
    Padavine Novi(p.max_kolicina - x); // ovo upitno
    Novi.padavine.resize(p.padavine.size());
    std::transform(p.padavine.begin(), p.padavine.end(), Oduzmi.begin(), Novi.padavine.begin(), std::minus<int>());
    return Novi;
}

Padavine operator -(int x, const Padavine &p)
{
    if((x - p.DajMinimalnuKolicinuPadavina()) < 0) throw std::domain_error ("Nekorektan rezultat operacije");
    std::vector<int> Oduzmi(p.padavine.size(), x);
    Padavine Novi(x); // ovo upitno
    Novi.padavine.resize(p.padavine.size());
    std::transform(Oduzmi.begin(), Oduzmi.end(), p.padavine.begin(), Novi.padavine.begin(), std::minus<int>());
    return Novi;
}

Padavine operator- (const Padavine &p1, const Padavine &p2)
{
    if(p1.padavine.size() != p2.padavine.size()) throw std::domain_error ("Nesaglasni operandi");
    Padavine Novi(p1.max_kolicina); // ovo upitno
    Novi.padavine.resize(p1.padavine.size());
    std::transform(p1.padavine.begin(), p1.padavine.end(), p2.padavine.begin(), Novi.padavine.begin(), std::minus<int>());
    if(Novi.DajMinimalnuKolicinuPadavina() < 0) throw std::domain_error ("Nekorektan rezultat operacije");
    return Novi;
}

Padavine& Padavine::operator +=(int x)
{
    if((DajMinimalnuKolicinuPadavina() + x) < 0) throw std::domain_error ("Nekorektan rezultat operacije");
    std::vector<int> SaberiSa(padavine.size(), x);
    max_kolicina += x;
    std::transform(padavine.begin(), padavine.end(), SaberiSa.begin(), padavine.begin(), std::plus<int>());
    return *this;
}
Padavine& Padavine::operator -=(int x)
{
    if((DajMinimalnuKolicinuPadavina() - x) < 0) throw std::domain_error ("Nekorektan rezultat operacije");
    std::vector<int> Oduzmi(padavine.size(), x);
    std::transform(padavine.begin(), padavine.end(), Oduzmi.begin(), padavine.begin(), std::minus<int>());
    return *this;
}

Padavine& Padavine::operator -=(const Padavine &p)
{
    //objekat treba ostati u istom stanju
    if(padavine.size() != p.padavine.size()) throw std::domain_error ("Nesaglasni operandi");
    Padavine Novi(max_kolicina); // ovoitno
    Novi.padavine.resize(padavine.size());
    std::transform(padavine.begin(), padavine.end(), p.padavine.begin(), Novi.padavine.begin(), std::minus<int>());
    if(Novi.DajMinimalnuKolicinuPadavina() < 0) throw std::domain_error ("Nekorektan rezultat operacije");
    else *this = Novi;
    return *this;

}

Padavine Padavine::operator -() const
{
    std::vector<int> Max(padavine.size(), max_kolicina);
    Padavine Novi(max_kolicina);
    Novi.padavine.resize(padavine.size());
    transform(Max.begin(), Max.end(), padavine.begin(), Novi.padavine.begin(), std::minus<int>());
    return Novi;
}

bool operator==(const Padavine &p1, const Padavine &p2)
{
    if(p1.padavine.size() != p2.padavine.size()) return false;
    if(std::equal(p1.padavine.begin(), p1.padavine.end(), p2.padavine.begin()))
        return true;
    else return false;
}

bool operator !=(const Padavine &p1, const Padavine &p2)
{
    if(p1.padavine.size() != p2.padavine.size()) return true;
    if(std::equal(p1.padavine.begin(), p1.padavine.end(), p2.padavine.begin()))
        return false;
    else return true;
}


int main ()
{
    Padavine p1(100);
    Padavine p2(200);
    try{
    p1.RegistrirajPadavine(100);
    p2.RegistrirajPadavine(100);
    p1.RegistrirajPadavine(10);
    p2.RegistrirajPadavine(10);
    // if(p1 == p2) std::cout<<"ISTI";
    // else std::cout<<"NOT OK";

    // }
    auto Novi = p1+1;
    //Novi.Ispisi();
    auto pom = -p1;
    pom.Ispisi();
    }
    catch(...){
        std::cout<<"*********IZUZETAK*********"<<std::endl;
    }
    return 0;
}
