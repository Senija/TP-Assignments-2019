//TP 2018/2019: Ispit 3, Zadatak 4
#include <iostream>
#include <cmath>
class Predmet
{
    double gustina_predmeta;
public:
    Predmet(double gustina) : gustina_predmeta(gustina)
    {

    }
    virtual ~Predmet()
    {

    }

    double DajGustinu() const
    {
        return gustina_predmeta;
    }
    virtual double DajZapreminu() const = 0;
    double DajMasu() const
    {
        return gustina_predmeta * DajZapreminu();
    } //gustina * zapremina


};

class Lopta : public Predmet
{
    double poluprecnik;
public:
    Lopta(double gustina_predmeta, double poluprecnik): Predmet(gustina_predmeta)
    {
        Lopta::poluprecnik = poluprecnik;
    }

    double DajZapreminu() const override
    {
        return (4 * 4 * atan(1) * poluprecnik * poluprecnik * poluprecnik)/3;
    }

};

class Cigla : public Predmet
{
    double a, b, c;
public:
    Cigla(double gustina_predmeta, double a, double b, double c): Predmet(gustina_predmeta)
    {
        Cigla::a = a;
        Cigla::b = b;
        Cigla::c = c;
    }

    double DajZapreminu() const override
    {
        return a * b * c;
    }
};
int main ()
{
    //Unesite broj predmeta: Unesite vrstu 1. predmeta (L ili C): Unesite gustinu i radijus lopte: Unesite vrstu 2. predmeta (L ili C): Unesite gustinu i radijus lopte: Unesite vrstu 3. predmeta (L ili C): Unesite gustinu i dimenzije cigle (duzina, sirina, visina): 175
    //niz pokazivaca na predmete
    int broj_predmeta;
    std::cout <<"Unesite broj predmeta: ";
    std::cin >> broj_predmeta;
    Predmet **predmeti = nullptr;
    predmeti = new Predmet*[broj_predmeta]{};
    for(int i = 0; i < broj_predmeta; i++) {
        std::cout<<"Unesite vrstu "<<i + 1<<". predmeta (L ili C): ";
        char znak;
        std::cin >> znak;
        if(znak == 'L') {
           std::cout<<"Unesite gustinu i radijus lopte: "; 
            double gustina;
            double poluprecnik;
            std::cin>>gustina>>poluprecnik;
            predmeti[i] = new Lopta(gustina, poluprecnik);
        }
        
        if(znak == 'C'){
            std::cout<<"Unesite gustinu i dimenzije cigle (duzina, sirina, visina): ";
            double gustina;
            double a, b, c;
            std::cin>>gustina>>a>>b>>c;
            predmeti[i] = new Cigla(gustina, a, b, c);
            
        }
    }
    
    int min;
    for(int i = 0; i < broj_predmeta; i++){
        min = i;
        for(int j = i+1; j < broj_predmeta; j++){
            if(predmeti[j] ->DajMasu() > predmeti[min]->DajMasu())
                min = j;
        }
        
        auto tmp = predmeti[i];
        predmeti[i] = predmeti[min];
        predmeti[min] = tmp;
    }
    
    for(int i = 0; i < broj_predmeta; i++){
        std::cout<<predmeti[i]->DajMasu()<<std::endl;
    }
    
    for(int i = 0; i< broj_predmeta; i++){
        delete predmeti[i];
        predmeti[i] = nullptr;
    }
    delete[] predmeti;
    
    return 0;
}
