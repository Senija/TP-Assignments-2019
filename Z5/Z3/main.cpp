//TP 2018/2019: Zadaća 5, Zadatak 3
#include <iostream>
#include <string>
#include <new>
#include <vector>
#include <algorithm>
#include <fstream>

class Narudzba
{
    std::string naziv_obroka;
    std::string ime_prezime;
    double cijena;

public:
    Narudzba(const char *naziv_jela, double cijena, const char *ime_prezime):naziv_obroka(naziv_jela), cijena(cijena), ime_prezime(ime_prezime)
    {

    }
    virtual ~Narudzba()
    {

    }
    std::string DajNazivObroka() const
    {
        return naziv_obroka;
    }
    double DajCijenuObroka() const
    {
        return cijena;
    }

    std::string DajNarucioca() const
    {
        return ime_prezime;
    }

    virtual void Ispisi() const
    {
        std::cout<<"Obrok: "<<naziv_obroka<<std::endl;
        std::cout<<"Cijena: "<<cijena<<" KM"<<std::endl; //NA KOLIKO DECINAMA?
        std::cout<<"Narucilac: "<<ime_prezime<<std::endl;
    }

    virtual double DajUkupnuCijenu() const
    {
        return cijena;
    }

    virtual Narudzba *DajKopiju() const
    {
        return new Narudzba(*this);
    }
};

class NarudzbaSaPicem : public Narudzba
{
    std::string naziv_pica;
    double cijena_pica;
public:
    NarudzbaSaPicem(const char *naziv_jela, double cijena_obroka, const char *ime_prezime, const char *pice, double cijena_pica) : Narudzba(naziv_jela, cijena_obroka, ime_prezime)
    {
        naziv_pica = pice;
        NarudzbaSaPicem::cijena_pica = cijena_pica;
    }
    std::string DajNazivPica() const
    {
        return naziv_pica;
    }

    double DajCijenuPica() const
    {
        return cijena_pica;
    }

    double DajUkupnuCijenu() const override
    {
        return cijena_pica + DajCijenuObroka();
    }

    void Ispisi() const override
    {
        std::cout<<"Obrok: "<<DajNazivObroka()<<std::endl;
        std::cout<<"Pice: "<<naziv_pica<<std::endl;
        std::cout<<"Cijena: "<<DajCijenuObroka()<<" KM"<<std::endl;
        std::cout<<"Cijena pica: "<<DajCijenuPica()<<" KM"<<std::endl;
        std::cout<<"Ukupna cijena: "<<DajUkupnuCijenu()<<" KM"<<std::endl;
        std::cout<<"Narucilac: "<<DajNarucioca()<<std::endl;

    }

    Narudzba *DajKopiju() const override
    {
        return new NarudzbaSaPicem(*this);
    }
};

class Narudzbe
{
    std::vector<Narudzba*> VektorNarudzbi;

    Narudzba *DajStudenta(std::string ime_prezime) const
    {
        auto it = find_if(VektorNarudzbi.begin(), VektorNarudzbi.end(),[ime_prezime](Narudzba *n) {
            return n->DajNarucioca() == ime_prezime;
        });

        return *it;
    }

public:
    Narudzbe()
    {

    }
    Narudzbe(const Narudzbe &n)
    {
        try {
            for(auto i = n.VektorNarudzbi.begin(); i != n.VektorNarudzbi.end(); i++) {
                VektorNarudzbi.push_back((*i)->DajKopiju());
            }
        } catch(...) {
            for(int i = 0; i < VektorNarudzbi.size(); i++) {
                delete VektorNarudzbi[i];
                VektorNarudzbi[i] = nullptr;
            }
            throw;
        }
    }

    Narudzbe(Narudzbe &&n)
    {
        VektorNarudzbi = n.VektorNarudzbi;
        for(int i = 0; i < n.VektorNarudzbi.size(); i++) {
            n.VektorNarudzbi[i] = nullptr;
        }
        n.VektorNarudzbi.resize(0);
    }

    Narudzbe &operator =(const Narudzbe &n)
    {
        std::vector<Narudzba*> novi_prostor;
        try {
            for(auto i = n.VektorNarudzbi.begin(); i != n.VektorNarudzbi.end(); i++) {
                novi_prostor.push_back((*i)->DajKopiju());

            }
        } catch(...) {
            for(int i = 0; i != novi_prostor.size(); i++) {
                delete novi_prostor[i];
                novi_prostor[i] = nullptr;
            }
        }
        for(int i = 0; i < VektorNarudzbi.size(); i++) {
            delete VektorNarudzbi[i];
            VektorNarudzbi[i] = nullptr;
        }
        VektorNarudzbi.clear();
        //VektorNarudzbi.resize(novi_prostor.size());
        VektorNarudzbi = novi_prostor;
        novi_prostor.clear();
        return *this;
    }

    Narudzbe &operator =(Narudzbe &&n)
    {
        std::swap(VektorNarudzbi, n.VektorNarudzbi);
        return *this;
    }
    ~Narudzbe()
    {
        for(int i = 0; i < VektorNarudzbi.size(); i++) {
            delete VektorNarudzbi[i];
            VektorNarudzbi[i] = nullptr;
        }
        VektorNarudzbi.resize(0);
    }

    void NaruciObrok(const char *naziv_jela, double cijena, const char *ime_prezime)
    {
        try {
            VektorNarudzbi.push_back(new Narudzba(naziv_jela, cijena, ime_prezime));
        } catch(...) {

        }
    }
    void NaruciObrokSaPicem(const char *naziv_jela, double cijena_obroka, const char *ime_prezime, const char *pice, double cijena_pica)
    {
        try {
            VektorNarudzbi.push_back(new NarudzbaSaPicem(naziv_jela,cijena_obroka,ime_prezime,pice,cijena_pica));
        } catch(...) {

        }
    }

    void ObradiNarudzbu()   // const???
    {
        if(VektorNarudzbi.size() == 0) throw std::range_error ("Nema vise narudzbi");
        if(VektorNarudzbi.size() != 0) {
            VektorNarudzbi[0]->Ispisi();
            delete VektorNarudzbi[0];
            VektorNarudzbi[0] = nullptr;
            auto it = VektorNarudzbi.begin();
            VektorNarudzbi.erase(it);
        }
    }

    bool DaLiImaNarudzbi() const
    {
        if(VektorNarudzbi.size() != 0) return true;
        return false;
    }

    // void Ispisi() const
    // {
    //     for(auto i = VektorNarudzbi.begin(); i != VektorNarudzbi.end(); i++ ) {
    //         (*i)->Ispisi();
    //     }
    // }

    double operator [] (std::string ime_prezime) const
    {
        //sta ako ga nema u nizi
        // auto it = DajStudenta(ime_prezime);
        // if(it != *VektorNarudzbi.end()){
        //     return it->DajUkupnuCijenu();
        // }
        int suma = 0;
        for(auto i = VektorNarudzbi.begin(); i != VektorNarudzbi.end(); i++) {
            if((*i)->DajNarucioca() == ime_prezime) {
                suma += (*i)->DajUkupnuCijenu();
            }
        }
        return suma;
    }

    void UcitajIzDatoteka(std::string NarudzbeDat, std::string Cijene)
    {
        if(VektorNarudzbi.size() != 0) {
            for(int i = 0; i != VektorNarudzbi.size(); i++) {
                delete VektorNarudzbi[i];
                VektorNarudzbi[i] = nullptr;
            }
            VektorNarudzbi.clear();
        }
        std::ifstream narudzba(NarudzbeDat);
        if(!narudzba) throw std::logic_error ("Trazena datoteka ne postoji");
        std::ifstream cijene(Cijene);
        if(!cijene) throw std::logic_error ("Trazena datoteka ne postoji");
        std::vector<std::pair<std::string, double>> VektorCijena;
        while(cijene) {
            std::string jelo_pice;
            double novac;
            std::getline(cijene, jelo_pice);
            cijene>>novac;
            cijene.ignore(10000, '\n');
            VektorCijena.push_back({jelo_pice, novac});
        }
        if(!cijene && !cijene.eof()) {
            cijene.clear();
            throw std::logic_error ("Problemi pri citanju");
        }
        while(narudzba) {
            std::string Narucioc;
            std::string hrana;
            std::string pice;
            std::getline(narudzba, Narucioc);
            if(narudzba.eof()) break;
            //narudzba>>std::ws;
            std::getline(narudzba, hrana);
            std::getline(narudzba, pice);
            auto cijena_hrane = std::find_if(VektorCijena.begin(), VektorCijena.end(), [hrana](std::pair<std::string, double> Cijena) {
                return hrana == Cijena.first;
            });
            if(pice.length() != 0) {
                auto cijena_pica = std::find_if(VektorCijena.begin(), VektorCijena.end(), [pice](std::pair<std::string,double> Cijena) {
                    return Cijena.first == pice;
                });

                if(cijena_hrane != VektorCijena.end() && cijena_pica != VektorCijena.end()) {
                    NaruciObrokSaPicem(hrana.c_str(), cijena_hrane->second, Narucioc.c_str(), pice.c_str(), cijena_pica->second);
                } else throw std::logic_error ("Nema odgovarajuce cijene");
            }
            else {
                if(cijena_hrane != VektorCijena.end())
                    NaruciObrok(hrana.c_str(), cijena_hrane->second, Narucioc.c_str());
                else throw std::logic_error ("Nema odgovarajuce cijene");
            }
            
        }

        if(!narudzba && !narudzba.eof()) {
            narudzba.clear();
            throw std::logic_error ("Problemi pri citanju");
        }

    }
};
int main ()
{
    // Narudzbe n;
    // n.NaruciObrokSaPicem("Burek", 5, "Ime Prezime", "fanta", 1);
    // // n.NaruciObrokSaPicem("Burek", 5, "Ime Prezime", "fanta", 1);
    // // n.NaruciObrokSaPicem("Burek", 5, "Ime Prezime", "fanta", 1);
    // // n.NaruciObrok("Burek", 5, "Ime Prezime");
    // Narudzbe n2(n);
    // //n2.NaruciObrokSaPicem("aaaaa", 5, "Ime Prezime", "fanta", 1);
    // //n2.NaruciObrokSaPicem("Baaaaaa", 5, "Ime Prezime", "fanta", 1);
    // // n2.NaruciObrokSaPicem("aaaa", 5, "Ime Prezime", "fanta", 1);
    // // n2.NaruciObrok("aaaaaaaa", 5, "Ime Prezime");
    // //n2 = n;
    // Narudzbe f4;  //2 studenta
    // f4.NaruciObrok("Piza", 5, "Ime Prezime");
    // f4.NaruciObrokSaPicem("Grah", 5, "Ime Prezime", "fanta", 5);

    // std::cout << std::endl << std::endl;
    // n2 = f4;  //dodjela manjeg većem, sadai f3 i f4 imaju 2 elementa
    // std::cout << "POMIJERAJUCI OPERATOR DODJELE - manji većem" << std::endl;
    // f4.Ispisi(); //f4 je prazno

    // f4.NaruciObrokSaPicem("Grah", 5, "Ime Prezime", "fanta", 5);
    // f4.NaruciObrokSaPicem("Sataras", 5, "Ime Prezime", "fanta", 5);
    // f4.NaruciObrokSaPicem("Grasak", 5, "Azra", "fanta", 5);
    // n2 = std::move(f4);  //f3 je prazno
    // n2.Ispisi();
    // std::cout<<std::endl<<n2["Ime Prezime"];
    // //n2.UcitajIzDatoteka("bla", "bla");
    return 0;
}
