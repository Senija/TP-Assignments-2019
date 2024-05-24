#include <iostream> 
#include <vector> 
#include <memory>
class Lik
{
public:
    enum Boje {Crvena, Zelena, Zuta, Plava, Ljubicasta, Crna, Bijela};
    Lik(Boje boja) : boja(boja) {}
    Boje DajBoju() const
    {
        return boja;
    }
    void Ispisi() const
    {
        std::cout << boja;
    }
private:
    Boje boja;
};
class Tacka : public Lik
{
    double x, y;
public:
    Tacka(Lik::Boje boja, double x, double y) : Lik(boja), x(x), y(y) {}
    void Ispisi() const
    {
        std::cout << "{" << x << "," << y << "}";
    }
};
class Mnogougao : public Lik
{
    int br_tjemena;
    double *x, *y;
public:
    Mnogougao(Lik::Boje boja, int broj_tjemena) : Lik(boja), br_tjemena(br_tjemena) {
        try{
            x = nullptr;
            y = nullptr;
            new double[br_tjemena];
            y = new double[br_tjemena];
        }
        catch(...){
            delete[] x;
            delete[] y;
            throw;
        }
    }
    void PostaviTjeme(int redni_broj, double x, double y)
    {
        Mnogougao::x[redni_broj - 1] = x;
        Mnogougao::y[redni_broj - 1] = y;
    }
    void Ispisi() const
    {
        std::cout << "{";
        for(int i = 0 ; i < br_tjemena; i++) {
            std::cout << "{" << x[i] << "," << y[i] << "}";
            if(i != br_tjemena - 1) std::cout << ",";
        }
        std::cout << "}";
    }
};
class KolekcijaLikova
{
    std::vector<std::shared_ptr<Lik>> likovi{};
public:
    KolekcijaLikova() {}
    void RegistrirajLik(Lik *lik)
    {
        likovi.push_back(std::make_shared<Lik>(*lik));
    } 
    void IspisiKolekciju()
    {
        for(int i = 0; i < likovi.size(); i++) {
            likovi[i]->Ispisi();
            std::cout << std::endl;
        }
    }
};
int main()
{
    KolekcijaLikova k;
    k.RegistrirajLik(new Tacka(Lik::Crvena, 30, 20));
    Mnogougao *m(new Mnogougao(Lik::Plava, 4));
    m->PostaviTjeme(1, 10, 10);
    m->PostaviTjeme(2, 10, 50);
    m->PostaviTjeme(3, 50, 50);
    m->PostaviTjeme(4, 50, 10);
    k.RegistrirajLik(m);
    k.IspisiKolekciju();
    return 0;
}
