//TP 2018/2019: Ispit 3, Zadatak 1
#include <iostream>
#include <cmath>
#include <stdexcept>
class Tacka
{
    double x, y;
public:
    Tacka(double x, double y):x(x), y(y)
    {

    }

    Tacka(const Tacka &t)
    {
        x = t.x;
        y = t.y;
    }
    double DajX() const
    {
        return x;
    }
    double DajY() const
    {
        return y;
    }

    Tacka &PostaviX(double x)
    {
        Tacka::x = x;
        return *this;
    }
    Tacka &PostaviY(double y)
    {
        Tacka::y = y;
        return *this;
    }

    static double Rastojanje(const Tacka &t1, const Tacka &t2);
    friend std::ostream &operator <<(std::ostream &tok, const Tacka &t);

};

double Tacka::Rastojanje(const Tacka &t1, const Tacka &t2)
{
    
    return std::sqrt((t1.x - t2.x) * (t1.x - t2.x) + (t1.y - t2.y) * (t1.y - t2.y));
    //return std::sqrt(pow((t1.x - t2.x),2)  - (t1.y - t2.y) * (t1.y - t2.y));
}

std::ostream &operator <<(std::ostream &tok, const Tacka &t)
{

    tok << "("<<t.x<<","<<t.y<<")";
    return tok;
}

class Krug
{
    Tacka centar;
    double r;
public:
    Krug(Tacka t, double r) : centar(t)
    {
        if (r < 0) throw std::domain_error ("Neispravan poluprecnik");
        Krug::r = r;
    }
    
    void Postavi(Tacka t, double r){
        if (r < 0) throw std::domain_error ("Neispravan poluprecnik");
        Krug::r = r;
        centar = t;
    }

    Krug(double x, double y, double r):centar(Tacka(x,y))
    {
        if (r < 0) throw std::domain_error ("Neispravan poluprecnik");
        Krug::r = r;
    }

    void Postavi(double x, double y, double r)
    {
        if (r < 0) throw std::domain_error ("Neispravan poluprecnik");
        centar.PostaviX(x);
        centar.PostaviY(y);
        Krug::r = r;
    }

    Krug( Tacka t, Tacka rub):centar(t)
    {
        r = Tacka::Rastojanje(t, rub);

    }

    void Postavi(Tacka t, Tacka rub)
    {
        centar = t;
        r = Tacka::Rastojanje(t, rub);
    }
    
    Tacka DajCentar() const{
        return centar;
    }
    double DajCentarX() const{
        return centar.DajX();
    }
    
    double DajCentarY() const{
        return centar.DajY();
    }
    
    double DajPoluprecnik() const{
        return r;
    }
    
    double DajObim() const{
        return 2 * r * 4 * atan(1);
    }
    
    double DajPovrsinu() const{
        return r *r * 4 * atan(1);
    }
    
    Krug &operator +=(Tacka t){
        this->Postavi(DajCentarX() + t.DajX(), DajCentarY() + t.DajY(), r);
        return *this;
    }
    
    Krug &operator *=(double skalar){
        if(skalar < 0) throw std::domain_error ("Neispravno skaliranje");
        this->Postavi(centar.DajX(), centar.DajY(), r * skalar);
        return *this;
    }
    
    Krug &operator ++(){
        r += 1;
        return *this;
    }
    
    Krug operator ++(int){
        Krug vrati = *this;
        r += 1;
        return vrati;
    }
    
    friend Krug operator +(const Krug &k, Tacka t);
    friend Krug operator *(const Krug &k, double skalar);
    friend Krug operator *(double skalar,const Krug &k);
    friend std::ostream &operator <<(std::ostream &tok, const Krug &k);

};

Krug operator +(const Krug &k, Tacka t){
    Tacka noci_centar(k.DajCentarX() + t.DajX(), k.DajCentarY() + t.DajY());
    Krug novi(noci_centar, k.r);
    return novi;
}

Krug operator *(const Krug &k, double skalar){
    if(skalar < 0) throw std::domain_error ("Neispravno skaliranje");
    Krug novi(k.centar, k.r * skalar);
    return novi;
}

std::ostream &operator <<(std::ostream &tok, const Krug &k){
    tok<<"{("<<k.centar.DajX()<<","<<k.centar.DajY()<<"),"<<k.r<<"}";
    return tok;
}


int main ()
{
  std::cout<<"----- AT 1-----"<<std::endl;

    // AT 1: Testiranje konstruktora i metoda DajX i DajY klase Tacka
    {
        Tacka t(1,2);
        std::cout<<t.DajX()<<" "<<t.DajY();
    }

    std::cout<<std::endl<<"----- AT 2-----"<<std::endl;

    // AT 2: Testiranje konstruktora i metoda DajX i DajY klase Tacka
    {
        Tacka t(3,4);
        std::cout<<t.DajX()<<" "<<t.DajY();
    }

    std::cout<<std::endl<<"----- AT 3-----"<<std::endl;

    // AT 3: Testiranje metoda za postavljanje klase Tacka
    {
        Tacka t(1,2);
        t.PostaviX(3);
        t.PostaviY(4);

        std::cout<<t.DajX()<<" "<<t.DajY();
    }

    std::cout<<std::endl<<"----- AT 4-----"<<std::endl;

    // AT 4: Testiranje kaskadnog vezivanja metoda za postavljanje klase Tacka
    {
        Tacka t(1,2);
        t.PostaviX(3).PostaviY(4);

        std::cout<<t.DajX()<<" "<<t.DajY();
    }

    std::cout<<std::endl<<"----- AT 5-----"<<std::endl;

    // AT 5: Testiranje metode Rastojanje klasse Tacka
    {
        Tacka t1(1,2);
        Tacka t2(t1);
        t2.PostaviX(-1).PostaviY(-2);

        std::cout<<t1.Rastojanje(t1,t2);
    }

    return 0;
}
