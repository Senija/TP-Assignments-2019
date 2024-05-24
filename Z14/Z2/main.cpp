#include <iostream>
#include <string>
#include <memory>
#include <algorithm>
#include <fstream>

class Spremnik
{
public:
    virtual ~Spremnik()
    {

    }
    virtual void Ispisi() const = 0;
    virtual std::shared_ptr<Spremnik> DajKopiju() const = 0;
    virtual double DajTezinu() const = 0;
    virtual double DajUkupnuTezinu() const = 0;

};
class Sanduk : public Spremnik
{
    double tezina_sanduka;
    std::string naziv_predmeta;
    int broj_predmeta;
    double tezina_predmeta;
public:
    Sanduk(double tezina, const char naziv_predmeta[], int broj_predmeta, double tezina_predmeta):tezina_sanduka(tezina), naziv_predmeta(naziv_predmeta), tezina_predmeta(tezina_predmeta), broj_predmeta(broj_predmeta) {}
    double DajTezinu() const
    {
        return tezina_sanduka;
    }
    double DajUkupnuTezinu() const
    {
        return tezina_predmeta * broj_predmeta + tezina_sanduka;
    }
    void Ispisi() const
    {
        std::cout<<"Vrsta spremnika: Sanduk"<<std::endl;
        std::cout<<"Sadrzaj: "<<naziv_predmeta<<std::endl;
        std::cout<<"Vlastita tezina: "<<tezina_sanduka<<" kg"<<std::endl;
        std::cout<<"Ukupna tezina: "<<tezina_predmeta * broj_predmeta + tezina_sanduka<<" kg"<<std::endl;
    }

    std::shared_ptr<Spremnik> DajKopiju() const override
    {
        return std::make_shared<Sanduk>(*this);
    }
};
class Bure : public Spremnik
{
    double tezina_bureta;
    std::string naziv_tecnosti;
    double tezina_tecnosti;
public:
    Bure(double tezina, const char naziv_tecnosti[], double tezina_tecnosti) : tezina_bureta(tezina), naziv_tecnosti(naziv_tecnosti), tezina_tecnosti(tezina_tecnosti)
    {

    }
    double DajTezinu() const
    {
        return tezina_bureta;
    }
    double DajUkupnuTezinu() const
    {
        return tezina_tecnosti + tezina_bureta;
    }
    void Ispisi() const
    {
        std::cout<<"Vrsta spremnika: Bure"<<std::endl;
        std::cout<<"Sadrzaj: "<<naziv_tecnosti<<std::endl;
        std::cout<<"Vlastita tezina: "<<tezina_bureta<<" kg"<<std::endl;
        std::cout<<"Ukupna tezina: "<<tezina_tecnosti + tezina_bureta<<" kg"<<std::endl;
    }
    std::shared_ptr<Spremnik> DajKopiju() const override
    {
        return std::make_shared<Bure>(*this);
    }
};
typedef std::shared_ptr<Spremnik> PokNaSpremnik;
class Skladiste
{
    PokNaSpremnik *DupliNaSpremnik;
    int kapacitet;
    int popunjeno;
public:
    explicit Skladiste(int max_broj): kapacitet(max_broj), DupliNaSpremnik(new PokNaSpremnik[max_broj] {})
    {
        popunjeno = 0;
    }
    ~Skladiste()
    {
        delete[] DupliNaSpremnik;
    }
    Skladiste(const Skladiste &s)
    {
        PokNaSpremnik *Pomocni = new PokNaSpremnik[s.kapacitet] {};
        try {

            for(auto i = 0; i != s.popunjeno; i++) {
                Pomocni[i] = s.DupliNaSpremnik[i]->DajKopiju();
            }
            DupliNaSpremnik = Pomocni;
            kapacitet = s.kapacitet;
            popunjeno = s.popunjeno;
            Pomocni = nullptr;
        } catch(...) {
            delete[] Pomocni;
            throw;
        }
    }
    Skladiste(Skladiste &&BezimenoSkladiste)
    {
        DupliNaSpremnik = BezimenoSkladiste.DupliNaSpremnik;
        kapacitet = BezimenoSkladiste.kapacitet;
        popunjeno = BezimenoSkladiste.popunjeno;
        BezimenoSkladiste.DupliNaSpremnik = nullptr;
        BezimenoSkladiste.popunjeno = 0;
    }
    Skladiste  &operator =(Skladiste s)
    {
        std::swap(DupliNaSpremnik, s.DupliNaSpremnik);
        std::swap(popunjeno, s.popunjeno);
        std::swap(kapacitet, s.kapacitet);
        return *this;
    }
    void DodajSanduk(double tezina, const char naziv_predmeta[], int broj_predmeta, double tezina_predmeta)
    {
        if(popunjeno == kapacitet) throw std::domain_error("Popunjeno skladiste");
        DupliNaSpremnik[popunjeno] = std::make_shared<Sanduk>(tezina, naziv_predmeta, broj_predmeta, tezina_predmeta);
        popunjeno++;
    }
    void DodajBure(double tezina, const char naziv_tecnosti[], double tezina_tecnosti)
    {
        if(popunjeno == kapacitet) throw std::domain_error("Popunjeno skladiste");
        DupliNaSpremnik[popunjeno] = std::make_shared<Bure>(tezina, naziv_tecnosti, tezina_tecnosti);
        popunjeno++;
    }
    Spremnik &DajNajlaksi()
    {
        if(popunjeno == 0) throw std::range_error ("Skladiste je prazno");
        int index_min = 0;
        int min_tezina = DupliNaSpremnik[0]->DajTezinu();
        for(auto i = 1; i < popunjeno; i++) {
            if(DupliNaSpremnik[i]->DajTezinu() < min_tezina) {
                min_tezina = DupliNaSpremnik[i]->DajTezinu();
                index_min = i;
            }
        }
        return *DupliNaSpremnik[index_min];
    }
    Spremnik &DajNajtezi()
    {
        if(popunjeno == 0) throw std::range_error ("Skladiste je prazno");
        int index_max = 0;
        int max_tezina = DupliNaSpremnik[0]->DajTezinu();
        for(auto i = 1; i < popunjeno; i++) {
            if(DupliNaSpremnik[i]->DajTezinu() > max_tezina) {
                max_tezina = DupliNaSpremnik[i]->DajTezinu();
                index_max = i;
            }
        }
        return *DupliNaSpremnik[index_max];
    }
    int BrojPreteskih(int pretesko) const
    {
        int brojac = 0;
        for(int i = 0; i < popunjeno; i++) {
            if(DupliNaSpremnik[i]->DajUkupnuTezinu() > pretesko) brojac++;
        }
        return brojac;
    }
    void IzlistajSkladiste() const
    {
        if(popunjeno != 0) {
            std::sort(DupliNaSpremnik, DupliNaSpremnik + popunjeno, [](std::shared_ptr<Spremnik> s1, std::shared_ptr<Spremnik> s2) {
                return s1->DajUkupnuTezinu() > s2->DajUkupnuTezinu();
            });

            for(int i = 0; i < popunjeno; i++) {
                DupliNaSpremnik[i]->Ispisi();
            }
        }

    }
    void UcitajIzDatoteke(const char naziv_datoteke[])
    {
        std::ifstream ulazni_tok(naziv_datoteke);
        if(!ulazni_tok) throw std::logic_error ("Trazena datoteka ne postoji");
        if(popunjeno != 0) {
            delete[] DupliNaSpremnik;
            popunjeno = 0;
            DupliNaSpremnik = new PokNaSpremnik[kapacitet];
        }

        char slovo, znak;
        std::string sadrzaj_skladista;
        
        while(ulazni_tok) {
            getline(ulazni_tok, sadrzaj_skladista);
            slovo = sadrzaj_skladista[0];
            sadrzaj_skladista.erase(0, 2);
            if(slovo == 'S') {
                if(kapacitet == popunjeno) throw std::domain_error ("Popunjeno skladiste");
                double tezina_sanduka, broj_predmeta, tezina_pojedinacnig;
                ulazni_tok>>tezina_sanduka>>broj_predmeta>>tezina_pojedinacnig;
                ulazni_tok.ignore(10000, '\n');
                DupliNaSpremnik[popunjeno] = std::make_shared<Sanduk>(tezina_sanduka, sadrzaj_skladista.c_str(), broj_predmeta, tezina_pojedinacnig);
                popunjeno++;

            } else if(slovo == 'B') {
                if(kapacitet == popunjeno) throw std::domain_error ("Popunjeno skladiste");
                double tezina_bureta, tezina_tecnosti;
                ulazni_tok>>tezina_bureta>>tezina_tecnosti;
                ulazni_tok.ignore(10000, '\n');
                DupliNaSpremnik[popunjeno] = std::make_shared<Bure>(tezina_bureta, sadrzaj_skladista.c_str(), tezina_tecnosti);
                popunjeno++;
                
            } else if(!ulazni_tok.eof()) throw std::logic_error ("Datoteka sadrzi besmislene podatke");
        }
        if(!ulazni_tok && !ulazni_tok.eof()) {
            ulazni_tok.clear();
            throw std::logic_error ("Problemi pri citanju datoteke");
        }
    }



};
int main ()
{
        
    return 0;
}
