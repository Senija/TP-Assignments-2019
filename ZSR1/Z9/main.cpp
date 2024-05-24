//TP 2018/2019: ZSR 1, Zadatak 9
#include <iostream>
#include <string>
class Zivotinja{
    std::string Vrsta;
    public:
    virtual ~Zivotinja(){}
    virtual void OglasiSe() const = 0; 
    virtual Zivotinja* DajKopiju() const = 0;
};
class Pas : public Zivotinja{
    public:
    void OglasiSe() const override{
        std::cout<<"Av!"<<std::endl;
    }
    Zivotinja* DajKopiju() const override{
        return new Pas(*this);
    }
};
class Macka : public Zivotinja{
    public:
    void OglasiSe() const override{
        std::cout<<"Mjau!"<<std::endl;
    }
    
    Zivotinja* DajKopiju() const override{
        return new Macka(*this);
    }
};
class Krava: public Zivotinja{
    public:
    void OglasiSe() const override{
        std::cout<<"Muu!"<<std::endl;
    }
    
    Zivotinja* DajKopiju() const override{
        return new Krava(*this);
    }
};
class PolimorfnaZivotinja{
    Zivotinja *polimorfna_zivotinja;
    public:
    PolimorfnaZivotinja(){
        polimorfna_zivotinja = nullptr;
    }
    PolimorfnaZivotinja(const Zivotinja &z){
        polimorfna_zivotinja = z.DajKopiju();
    }
    
    void OglasiSe() const{
        return polimorfna_zivotinja->OglasiSe();
    }
    
};
int main ()
{
    Macka m;
    Pas p;
    Krava k;
    m.OglasiSe();
    PolimorfnaZivotinja pm(m);
    pm.OglasiSe();
	return 0;
}