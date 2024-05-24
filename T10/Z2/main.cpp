#include <iostream>
#include <stdexcept>
#include <cmath>
#include <iomanip>

class Krug{
    double poluprecnik;
    public:
    explicit Krug(double poluprecnik){
        if(poluprecnik <= 0) throw std::domain_error ("Neispravan poluprecnik");
        Krug::poluprecnik = poluprecnik;
    }
    void Postavi(double r){
        if(r <= 0 ) throw std::domain_error ("Neispravan poluprecnik");
        poluprecnik = r;
    }
    double DajPoluprecnik() const{
        return poluprecnik;
    }
    double DajObim() const{
        return 8*atan(1)*poluprecnik;
    }
    double DajPovrsinu() const{
        return poluprecnik*poluprecnik*4*atan(1);
    }
    Krug &Skaliraj(double faktor_skaliranja){
        if(faktor_skaliranja <= 0) throw std::domain_error ("Neispravan faktor skaliranja");
        poluprecnik *= faktor_skaliranja;
        return *this;
    }
    void Ispisi() const{
        std::cout<<std::fixed<<std::setprecision(5)<<"R="<<poluprecnik<<" O="<<DajObim()<<" P="<<DajPovrsinu();
    }
};

class Valjak{
  Krug baza;
  double visina;
  public:  
    Valjak(double r, double h) : baza(r){
        if( h <= 0) throw std::domain_error ("Neispravna visina");
        visina = h;
    }
    void Postavi(double r, double h){
        baza.Postavi(r);
        if( h <= 0) throw std::domain_error ("Neispravna visina");
        visina = h;
    }
    Krug DajBazu() const{
        return baza;
    }
    double DajPoluprecnikBaze() const{
        return baza.DajPoluprecnik();
    }
    double DajVisinu() const{
        return visina;
    }
    double DajPovrsinu() const{
        return 2 * baza.DajPovrsinu() + baza.DajObim() * visina;
    }
    double DajZapreminu() const{
        return baza.DajPovrsinu() * visina;
    }
    
    Valjak &Skaliraj(double faktor_skaliranja){
        if(faktor_skaliranja <= 0) throw std::domain_error ("Neispravan faktor skaliranja");
        //double novi_r = baza.DajPoluprecnik() * faktor_skaliranja;
        baza.Postavi(baza.DajPoluprecnik() * faktor_skaliranja);
        visina = visina * faktor_skaliranja;
        return *this;
    }
    
    void Ispisi() const{
        std::cout<<std::fixed<<std::setprecision(5)<<"R="<< baza.DajPoluprecnik()<<" H="<<visina<<" P="<<DajPovrsinu()<<" V="<<DajZapreminu();
    }
    
};
int main ()
{
    
    Krug k1(5);
Valjak v1(1,9);
const Krug k2(k1);                          
const Valjak v2(v1);
k2.Ispisi(); std::cout << std::endl;
v2.Ispisi(); std::cout << std::endl;
	return 0;
}