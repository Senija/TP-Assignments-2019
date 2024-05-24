//TP 2018/2019: ZSR 1, Zadatak 5
// zadatak 6 I primjer
#include <iostream>
#include <new>
#include <string>
#include <vector>
#include <algorithm>
#include <utility>
#include <stdexcept>

class Artikal
{
    std::string naziv;
    double cijena;
public:
    Artikal(std::string naziv, double cijena):naziv(naziv), cijena(cijena)
    {

    }

    virtual ~Artikal() {}

    std::string DajNaziv() const
    {
        return naziv;
    }

    double DajCijenu() const
    {
        return cijena;
    }

    virtual Artikal *DajKopiju() const = 0;
    virtual void Ispisi() const = 0;
};

class Brasno: public Artikal
{
    double kg;
public:
    Brasno(double cijena, double kilogrami):Artikal("Brasno", cijena), kg(kilogrami)
    {

    }
    double DajKilograme() const
    {
        return kg;
    }

    Artikal *DajKopiju() const override
    {
        return new Brasno(this->DajCijenu(), kg);
    }

    void Ispisi() const override
    {
        std::cout<<"Brasno "<<kg<<"kg, "<<DajCijenu()<<"KM"<<std::endl;
    }
};

class Ulje : public Artikal
{
    double litri;
public:
    Ulje(double cijena, double litri): Artikal("Ulje", cijena), litri(litri)
    {

    }

    double DajLitre() const
    {
        return litri;
    }

    Artikal *DajKopiju() const override
    {
        return new Ulje(this->DajCijenu(), litri);
    }

    void Ispisi() const
    {
        std::cout<<"Ulje "<<litri<<"l, "<<DajCijenu()<<"KM"<<std::endl;
    }
};

class Prodavnica
{
    std::vector<Artikal*> VektorPok;
public:
    Prodavnica() {}

    Prodavnica(const Prodavnica &p)
    {
        std::vector<Artikal*> pomocni;
        try {
            for(auto i = p.VektorPok.begin(); i !=p.VektorPok.end(); i++) {
                pomocni.push_back((*i)->DajKopiju());
            }
        } catch(...) {
            for(int i = 0; i < pomocni.size(); i++) {
                delete pomocni.at(i);
                pomocni.at(i) = nullptr;
            }
            throw;
        }
        VektorPok = pomocni;
    }

    Prodavnica(Prodavnica &&p)
    {
        VektorPok = p.VektorPok;
        for(auto i = 0; i < p.VektorPok.size(); i++) {
            VektorPok.at(i) = nullptr;
        }
    }

    Prodavnica &operator = (const Prodavnica &p)
    {
        std::vector<Artikal*> pomocni;
        try {
            for(auto i = p.VektorPok.begin(); i != p.VektorPok.end(); i++) {
                pomocni.push_back((*i)->DajKopiju());
            }
        } catch(...) {
            for(int i = 0; i < pomocni.size(); i++) {
                delete pomocni.at(i);
                pomocni.at(i) = nullptr;
            }
            throw;
        }

        for(auto i = 0; i < VektorPok.size(); i++) {
            delete VektorPok.at(i);
            VektorPok.at(i) = nullptr;
        }
        VektorPok.clear();
        VektorPok = pomocni;
        return *this;
    }

    Prodavnica& operator =(Prodavnica &&p)
    {
        std::swap(VektorPok, p.VektorPok);
        return *this;
    }
    ~Prodavnica()
    {
        for(auto i = 0; i != VektorPok.size(); i++) {
            delete VektorPok.at(i);
            VektorPok.at(i) = nullptr;
        }
        VektorPok.clear();
    }
    void DodajUlje(const Ulje &u)
    {
        VektorPok.push_back(u.DajKopiju());
    }
    void DodajUlje(double cijena, double litri)
    {
        VektorPok.push_back(new Ulje(cijena, litri));
    }
    void DodajBrasno(const Brasno &b)
    {
        VektorPok.push_back(b.DajKopiju());
    }
    void DodajBrasno(double cijena, double kg)
    {
        VektorPok.push_back(new Brasno(cijena, kg));
    }
    void Ispisi() const
    {
        for(auto i = VektorPok.begin(); i != VektorPok.end(); i++) {
            (*i)->Ispisi();
        }
    }
    
    Artikal* operator[](int redni_broj){
        if(redni_broj < 0 || redni_broj >= VektorPok.size()) throw std::range_error("Neispravan indeks!");
        return VektorPok[redni_broj];
    }
};

int main ()
{
    Prodavnica p, p2;
    Ulje u (2, 1);
    Brasno b (1.1, 1);
    p.DodajUlje(u);
    p.DodajUlje (7, 5);
    p.DodajBrasno(17, 20);
    p.DodajBrasno (b);
    Prodavnica p3 (p);
    p3.Ispisi(); //svaki artikal, u novom redu
     p2 = p;Artikal *a = p2[0];a->Ispisi(); //Ulje 1l, 2KM
     p2[2]->Ispisi(); //Brasno 17kg, 20KM

}
