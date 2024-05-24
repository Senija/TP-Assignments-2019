#include <iostream>
#include <vector>
#include <memory>
class GrafickiElement
{
public:
    enum Boje {Crvena, Zelena, Zuta, Plava, Ljubicasta, Crna, Bijela};
    virtual ~GrafickiElement() {}
    GrafickiElement(Boje boja) : boja(boja) {}
    Boje DajBoju() const
    {
        return boja;
    }
    virtual  void Ispisi() const
    {
        std::cout << boja;
    }
    virtual std::shared_ptr<GrafickiElement> DajKopiju() const
    {
        return  std::make_shared<GrafickiElement>(boja);
    }
private:
    Boje boja;
};
class Tacka : public GrafickiElement
{
    double x, y;
public:
    Tacka(GrafickiElement::Boje boja, double x, double y) : GrafickiElement(boja), x(x), y(y) {}
    void Ispisi() const
    {
        std::cout << "{" << x << "," << y << "}";
    }

    std::shared_ptr<GrafickiElement> DajKopiju() const override
    {
        return std::make_shared<Tacka>(this->DajBoju(), x, y);
    }
};
class Poligon : public GrafickiElement
{
    int broj_tjemena;
    double *x = nullptr, *y = nullptr;
public:
    Poligon(GrafickiElement::Boje boja, int broj_tjemena) : GrafickiElement(boja), broj_tjemena(broj_tjemena)
    {
        try {
            x = new double[broj_tjemena];
            y = new double[broj_tjemena];
        } catch(...) {
            delete[] x;
            x = nullptr;
            delete[] y;
            y = nullptr;
        }
    }

    ~Poligon()
    {
        delete[] x;
        x = nullptr;
        delete[] y;
        y = nullptr;
    }
    void PostaviTjeme(int redni_broj, double x, double y)
    {
        Poligon::x[redni_broj - 1] = x;
        Poligon::y[redni_broj - 1] = y;
    }
    void Ispisi() const
    {
        std::cout << "{";
        for(int i = 0 ; i < broj_tjemena; i++) {
            std::cout << "{" << x[i] << "," << y[i] << "}";
            if(i != broj_tjemena - 1) std::cout << ",";
        }
        std::cout << "}";
    }
    std::shared_ptr<GrafickiElement> DajKopiju() const override
    {
        return std::make_shared<Poligon>(this->DajBoju(), broj_tjemena);
    }
};
class GrafickiSistem
{
    std::vector<std::shared_ptr<GrafickiElement>> elementi;
public:
    GrafickiSistem() {}
    ~GrafickiSistem() {}
    GrafickiSistem(const GrafickiSistem &GE)
    {
        std::vector<std::shared_ptr<GrafickiElement>> pomocni;
        try {
            for(auto i = GE.elementi.begin(); i != GE.elementi.end(); i++) {
                pomocni.push_back((*i)->DajKopiju());
            }
        } catch(...) {
            throw;
        }
        elementi = pomocni;
    }

    GrafickiSistem(GrafickiSistem &&GE) : elementi(std::move(GE.elementi))
    {
    }

    GrafickiSistem &operator =(const GrafickiSistem &GE)
    {
        elementi.resize(GE.elementi.size());
        for(int i = 0; i < GE.elementi.size(); i++) {
            elementi[i] = GE.elementi[i]->DajKopiju();
        }
        return *this;
    }

    GrafickiSistem &operator =(GrafickiSistem &&GE)
    {
        std::swap(elementi, GE.elementi);
        return *this;
    }

    void RegistrirajElement(GrafickiElement *e)
    {
        elementi.push_back(std::shared_ptr<GrafickiElement>(e));
    }
    void IspisiSve()
    {
        for(int i = 0; i < elementi.size(); i++) {
            elementi[i]->Ispisi();
            std::cout << std::endl;
        }
    }
};
int main()
{
    GrafickiSistem s;
    s.RegistrirajElement(new Tacka(GrafickiElement::Crvena, 30, 20));
    Poligon *p(new Poligon(GrafickiElement::Plava, 4));
    p->PostaviTjeme(1, 10, 10);
    p->PostaviTjeme(2, 10, 50);
    p->PostaviTjeme(3, 50, 50);
    p->PostaviTjeme(4, 50, 10);
    s.RegistrirajElement(p);
    s.IspisiSve();
    return 0;
}
