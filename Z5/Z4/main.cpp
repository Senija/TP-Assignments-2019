//TP 2018/2019: Zadaća 5, Zadatak 4
#include <iostream>
#include <vector>
#include <fstream>
#include <algorithm>

class ApstraktnoVozilo
{

    int tezina;

public:

    ApstraktnoVozilo(int tezina) : tezina(tezina)
    {
        // ApstraktnoVozilo::tezina = tezina;
    }
    virtual ~ApstraktnoVozilo() {}
    int DajTezinu() const
    {
        return tezina;
    }
    virtual int DajUkupnuTezinu() const = 0;
    virtual ApstraktnoVozilo* DajKopiju() const = 0;
    virtual void IspisiPodatke() const = 0;
};

class Automobil : public ApstraktnoVozilo
{

    std::vector<int> tezine_putnika;

    int Suma_tezina_putnika(std::vector<int> tezine) const
    {
        int suma = 0;
        for(int i = 0; i < tezine.size(); i++) {
            suma += tezine[i];
        }
        return suma;
    }
public:

    Automobil(int tezina, std::vector<int>putnici): ApstraktnoVozilo(tezina), tezine_putnika(putnici)
    {
        //tezine_putnika = putnici;
    }
    // ~Automobil(){

    // }
    int DajUkupnuTezinu() const override
    {
        int suma = 0;
        for(auto x : tezine_putnika) suma += x;
        return suma + this->DajTezinu();
    }

    ApstraktnoVozilo *DajKopiju() const override
    {
        return new Automobil(this->DajTezinu(), tezine_putnika);
    }

    void IspisiPodatke() const override
    {
        std::cout<<"Vrsta vozila: Automobil"<<std::endl;
        std::cout<<"Vlastita tezina: "<<this->DajTezinu()<<" kg"<<std::endl;
        std::cout<<"Tezine putnika: ";
        for(int i = 0; i < tezine_putnika.size(); i++) {
            if(i != tezine_putnika.size() - 1) std::cout<<tezine_putnika[i]<<" kg,";
            else std::cout<<tezine_putnika[i]<<" kg"<<std::endl;
        }
        std::cout<<"Ukupna tezina: "<<DajUkupnuTezinu()<<" kg"<<std::endl;
    }
};

class Kamion : public ApstraktnoVozilo
{

    int tezina_tereta;
public:

    Kamion(int tezina_vozila, int tezina_tereta) : ApstraktnoVozilo(tezina_vozila), tezina_tereta(tezina_tereta)
    {
        //Kamion::tezina_tereta = tezina_tereta;
    }
    // ~Kamion(){

    // }
    int DajUkupnuTezinu() const override
    {
        return this->DajTezinu() + tezina_tereta;
    }

    ApstraktnoVozilo *DajKopiju() const override
    {
        return new Kamion(this->DajTezinu(), tezina_tereta);
    }

    void IspisiPodatke() const override
    {
        std::cout<<"Vrsta vozila: Kamion"<<std::endl;
        std::cout<<"Vlastita tezina: "<<this->DajTezinu()<<" kg"<<std::endl;
        std::cout<<"Tezina tereta: "<<tezina_tereta<<" kg"<<std::endl;
        std::cout<<"Ukupna tezina: "<<DajUkupnuTezinu()<<" kg"<<std::endl;
    }
};

class Autobus : public ApstraktnoVozilo
{
    int broj_putnika;
    int prosjecna_tezina;

public:


    Autobus(int tezina_vozila, int broj_putnika, int prosjecna_tezina) : ApstraktnoVozilo(tezina_vozila), broj_putnika(broj_putnika), prosjecna_tezina(prosjecna_tezina)
    {
        // Autobus::broj_putnika = broj_putnika;
        // Autobus::prosjecna_tezina = prosjecna_tezina;
    }
    // ~Autobus(){
    //
    // }
    ApstraktnoVozilo *DajKopiju() const override
    {
        return new Autobus(this->DajTezinu(), broj_putnika, prosjecna_tezina);
    }

    int DajUkupnuTezinu() const override
    {
        //auto tezina = ;
        return (broj_putnika * prosjecna_tezina) + this->DajTezinu();
    }

    void IspisiPodatke() const override
    {
        std::cout<<"Vrsta vozila: Autobus"<<std::endl;
        std::cout<<"Vlastita tezina: "<<this->DajTezinu()<<" kg"<<std::endl;
        std::cout<<"Broj putnika: "<<broj_putnika<<std::endl;
        std::cout<<"Prosjecna tezina putnika: "<<prosjecna_tezina<<" kg"<<std::endl;
        std::cout<<"Ukupna tezina: "<<DajUkupnuTezinu()<<" kg"<<std::endl;
    }

};

class Vozilo
{
    ApstraktnoVozilo *polimorfnoVozilo;

public:
    Vozilo()
    {
        polimorfnoVozilo = nullptr;
    }


    // Vozilo(ApstraktnoVozilo *Apstraktni)
    // {
    //     polimorfnoVozilo = Apstraktni->DajKopiju();
    // }

    Vozilo(const ApstraktnoVozilo &aVto_kamiJon_aVtobus) : polimorfnoVozilo(aVto_kamiJon_aVtobus.DajKopiju())
    {
        //polimorfnoVozilo = aVto_kamiJon_aVtobus.DajKopiju();
    }

    Vozilo(const Vozilo &V)
    {
        if(V.polimorfnoVozilo != nullptr) polimorfnoVozilo = V.polimorfnoVozilo->DajKopiju();
    }
    ~Vozilo()
    {
        delete polimorfnoVozilo;
        polimorfnoVozilo = nullptr;
    }
    Vozilo(Vozilo &&V)
    {
        if(V.polimorfnoVozilo != nullptr) {
            polimorfnoVozilo = V.polimorfnoVozilo;
            V.polimorfnoVozilo = nullptr;
        }
    }

    Vozilo &operator =(const Vozilo &V)
    {
        ApstraktnoVozilo *novi_prostor = nullptr;;
        try {
            novi_prostor = V.polimorfnoVozilo->DajKopiju();
        } catch (...) {
            delete novi_prostor;
            novi_prostor = nullptr;
        }

        delete polimorfnoVozilo;
        polimorfnoVozilo = nullptr;
        polimorfnoVozilo = novi_prostor;
        return *this;

    }

    Vozilo &operator = (Vozilo &&V)
    {
        std::swap(polimorfnoVozilo, V.polimorfnoVozilo);
        return *this;
    }
    int DajTezinu() const
    {
        return polimorfnoVozilo->DajTezinu();
    }
    int DajUkupnuTezinu() const
    {
        return polimorfnoVozilo->DajUkupnuTezinu();
    }
    ApstraktnoVozilo *DajKopiju() const
    {
        return polimorfnoVozilo->DajKopiju();
    }
    void IspisiPodatke() const
    {
        return polimorfnoVozilo->IspisiPodatke();
    }



};

int main ()
{


    std::ifstream ulazni_tok("VOZILA.TXT");
    std::vector<Vozilo> BrmBrm;
    if(!ulazni_tok) {
        throw std::logic_error ("Datoteka ne postoji!");
    }
    while(ulazni_tok) {
        if(ulazni_tok.eof()) break;
        char slovo;
        int vlastita_weight;
        ulazni_tok>>slovo>>vlastita_weight>>std::ws;
        if(slovo =='A') {
            int broj_putnika;
            ulazni_tok>>broj_putnika>>std::ws;
            std::vector<int> tezine_putnika;
            for(int i = 0; i < broj_putnika; i++) {
                int tezina;
                ulazni_tok>>tezina>>std::ws;
                tezine_putnika.push_back(tezina);
            }
            Automobil Auto(vlastita_weight, tezine_putnika);
            Vozilo avto (Auto);
            //avto.IspisiPodatke();
            BrmBrm.push_back(avto);
        } else if(slovo == 'K') {
            int tezina_tereta;
            ulazni_tok>>tezina_tereta>>std::ws;
            Kamion kamion(vlastita_weight, tezina_tereta);
            Vozilo kamion2(kamion);
            BrmBrm.push_back(kamion2);
        } else if(slovo == 'B') {
            int broj_putnika;
            int prosjecna_tezina;
            ulazni_tok>>broj_putnika>>std::ws>>prosjecna_tezina>>std::ws;
            Autobus bus(vlastita_weight, broj_putnika, prosjecna_tezina);
            Vozilo bus2(bus);
            BrmBrm.push_back(bus2);
        }
    }
    if(!ulazni_tok && !ulazni_tok.eof()) throw std::logic_error ("Greska prilikom citanja datoteke.");

    // for(auto i = BrmBrm.begin(); i != BrmBrm.end(); i++){
    //     std::cout<<i->DajUkupnuTezinu()<<std::endl;
    // }
     if(BrmBrm.size() != 0) {
    std::sort(BrmBrm.begin(), BrmBrm.end(), [](Vozilo v1, Vozilo v2) {
        return v1.DajUkupnuTezinu() < v2.DajUkupnuTezinu();
    });

        std::for_each(BrmBrm.begin(), BrmBrm.end(), [](Vozilo v){
            std::cout<<v.DajUkupnuTezinu()<<std::endl;
        });
    }

    return 0;
}
