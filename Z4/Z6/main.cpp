#include <iostream>
#include <string>
#include <stdexcept>
#include <utility>
#include <map>
#include <memory>

struct Korisnik {
    std::string ime, prezime, adresa, telefon;
};

class Knjiga
{
    std::string naslov, ime_pisca, zanr;
    int godina_izdavanja;
    Korisnik *PokNaKorisnika;
public:
    Knjiga(std::string naslov, std::string ime_pisca, std::string zanr, int godina_izdavanja) : naslov(naslov),ime_pisca(ime_pisca), zanr(zanr), godina_izdavanja(godina_izdavanja)
    {
        PokNaKorisnika = nullptr;
    }
    std::string DajNaslov() const
    {
        return naslov;
    }
    std::string DajAutora() const
    {
        return ime_pisca;
    }
    std::string DajZanr() const
    {
        return zanr;
    }
    int DajGodinuIzdavanja() const
    {
        return godina_izdavanja;
    }
    Korisnik* DajKodKogaJe() const
    {
        //uslov dodatni
        return PokNaKorisnika;
    }
    void ZaduziKnjigu(Korisnik &k)
    {
        PokNaKorisnika = &k;
    }
    void RazduziKnjigu()
    {
        PokNaKorisnika = nullptr;
    }
    bool DaLiJeZaduzena()
    {
        if(PokNaKorisnika) return true;
        return false;
    }
};
class Biblioteka
{
    std::map<int, std::shared_ptr<Korisnik>> korisnici;
    std::map<int, std::shared_ptr<Knjiga>> knjige;
    template<typename TipE>
    bool DaLiPostoji(const std::map<int, TipE> &m, int id) const
    {
        if(m.find(id) != m.end()) return true; // postoji
        return false;
    }

    bool JesuLiJednakiKorisnici(Korisnik *k1, std::shared_ptr<Korisnik> k2) const
    {
        if(k1->ime == k2->ime && k1->prezime == k2->prezime && k1->adresa == k2->adresa && k1->telefon == k2->telefon) return true;
        return false;
    }
public:
    Biblioteka() {} 
    Biblioteka(const Biblioteka &biblioteka)  //duboko kopiranje
    {
        std::map<int, std::shared_ptr<Korisnik>> korisnik_pom;
        std::map<int, std::shared_ptr<Knjiga>> knjiga_pom;
        try {
            for(auto i = biblioteka.korisnici.begin(); i!= biblioteka.korisnici.end(); i++) {
                std::shared_ptr<Korisnik> pomocni = std::make_shared<Korisnik>(*(i->second));
                korisnik_pom.insert(std::pair<int, std::shared_ptr<Korisnik>>(i->first, pomocni));
            }
            for(auto i = biblioteka.knjige.begin(); i!= biblioteka.knjige.end(); i++) {
                std::shared_ptr<Knjiga> pomocni = std::make_shared<Knjiga>(*(i->second));
                knjiga_pom.insert(std::pair<int, std::shared_ptr<Knjiga>>(i->first, pomocni));
            }

        } 
        catch(...) {
            throw;
        }
        korisnici = korisnik_pom;
        knjige = knjiga_pom; ////////MOVE?????????
        // korisnik_pom.clear();
        // knjiga_pom.clear();
    }
    Biblioteka(Biblioteka &&biblioteka){
        korisnici = biblioteka.korisnici;
        knjige = biblioteka.knjige;
    }
    Biblioteka& operator= (const Biblioteka &biblioteka)
    {
        std::map<int, std::shared_ptr<Knjiga>> novi_prostorKnjige;
        std::map<int, std::shared_ptr<Korisnik>> novi_prostorKorisnik;
        try {
            for(auto i = biblioteka.knjige.begin(); i != biblioteka.knjige.end(); i++) {
                auto pomocni = std::make_shared<Knjiga>(*(i->second));
                novi_prostorKnjige.insert(std::pair<int, std::shared_ptr<Knjiga>>(i->first, pomocni));
            }

            for(auto i = biblioteka.korisnici.begin(); i != biblioteka.korisnici.end(); i++) {
                auto pomocni= std::make_shared<Korisnik>(*(i->second));
                novi_prostorKorisnik.insert(std::pair<int, std::shared_ptr<Korisnik>>(i->first, pomocni));
            }
            std::swap(korisnici, novi_prostorKorisnik); // ili dodijeli pa postavi na nullptr
            std::swap(knjige, novi_prostorKnjige); // postaviti na nuluuu!!!!!!!!!!!

        } catch(...) {

        }
        return *this;
    }
    Biblioteka & operator =(Biblioteka &&biblioteka)
    {
        std::swap(korisnici, biblioteka.korisnici);
        std::swap(knjige, biblioteka.knjige);
        return *this;
    }
    void RegistrirajNovogKorisnika( int id_korisnika, std::string ime, std::string prezime, std::string adresa, std::string mobile)
    {
        if(DaLiPostoji(korisnici, id_korisnika)) throw std::logic_error ("Korisnik vec postoji");
        auto pomocna = std::make_shared<Korisnik>();
        pomocna->ime = ime;
        pomocna->prezime = prezime;
        pomocna->adresa = adresa;
        pomocna->telefon = mobile;
        korisnici.insert(std::pair<int, std::shared_ptr<Korisnik>>(id_korisnika, pomocna));

    }
    void RegistrirajNovuKnjigu(int id_knjige, std::string naslov, std::string ime_pisca, std::string zanr, int godina_izdavanja)
    {
        if(DaLiPostoji(knjige, id_knjige)) throw std::logic_error ("Knjiga vec postoji");
        auto pomocna = std::make_shared<Knjiga>(naslov, ime_pisca, zanr, godina_izdavanja);
        knjige.insert(std::pair<int, std::shared_ptr<Knjiga>>(id_knjige, pomocna));

    }
    Korisnik &NadjiKorisnika(int id_korisnika) const   //dvoje verzije???
    {
        auto it = korisnici.find(id_korisnika);
        if(it != korisnici.end()) return *(it->second);
        else throw std::logic_error ("Korisnik nije nadjen");
    }
    Knjiga &NadjiKnjigu(int id_knjige) const
    {
        auto it = knjige.find(id_knjige);
        if(it != knjige.end()) return *(it->second);
        else throw std::logic_error ("Knjiga nije nadjena");
    }
    void IzlistajKorisnike()
    {
        for(auto i = korisnici.begin(); i != korisnici.end(); i++) {
            if(i != korisnici.begin()) std::cout<<std::endl;
            std::cout<<"Clanski broj: "<<i->first<<std::endl;
            std::cout<<"Ime i prezime: "<<i->second->ime<<" "<<i->second->prezime<<std::endl;
            std::cout<<"Adresa: "<<i->second->adresa<<std::endl;
            std::cout<<"Broj telefona: "<<i->second->telefon<<std::endl;
        }
    }
    void IzlistajKnjige()
    {
        for(auto i = knjige.begin(); i != knjige.end(); i++) {
            if(i != knjige.begin()) std::cout<<std::endl;
            std::cout<<"Evidencijski broj: "<<i->first<<std::endl;
            std::cout<<"Naslov: "<<i->second->DajNaslov()<<std::endl;
            std::cout<<"Pisac: "<<i->second->DajAutora()<<std::endl;
            std::cout<<"Zanr: "<<i->second->DajZanr()<<std::endl;
            std::cout<<"Godina izdavanja: "<<i->second->DajGodinuIzdavanja()<<std::endl;
            if(i->second->DaLiJeZaduzena()) std::cout<<"Zaduzena kod korisnika: "<<i->second->DajKodKogaJe()->ime<<" "<<i->second->DajKodKogaJe()->prezime<<std::endl;

        }
    }
    void ZaduziKnjigu(int id_knjige, int id_korisnika)
    {
        auto it_knjiga = knjige.find(id_knjige);
        auto it_korisnik = korisnici.find(id_korisnika);
        if(it_knjiga == knjige.end()) throw std::logic_error ("Knjiga nije nadjena");
        if(it_korisnik == korisnici.end()) throw std::logic_error ("Korisnik nije nadjen");
        if(it_knjiga->second->DaLiJeZaduzena()) throw std::logic_error ("Knjiga vec zaduzena");
        it_knjiga->second->ZaduziKnjigu(*it_korisnik->second);
    }
    void RazduziKnjigu(int id_knjige)
    {
        auto it_knjiga = knjige.find(id_knjige);
        if(it_knjiga == knjige.end()) throw std::logic_error ("Knjiga nije nadjena");
        if(!it_knjiga->second->DaLiJeZaduzena()) throw std::logic_error ("Knjiga nije zaduzena");
        it_knjiga->second->RazduziKnjigu();
    }
    void PrikaziZaduzenja(int id_korisnika)
    {
        auto zaduzivac = korisnici.find(id_korisnika);
        if(zaduzivac == korisnici.end()) throw std::logic_error("Korisnik nije nadjen");
        bool zaduzio = false;
        for(auto i = knjige.begin(); i != knjige.end(); i++) {
            if(i->second->DaLiJeZaduzena() && JesuLiJednakiKorisnici(i->second->DajKodKogaJe(), zaduzivac->second)) {
                zaduzio = true;
                if(i != knjige.begin()) std::cout<<std::endl;
                std::cout<<"Evidencijski broj: "<<i->first<<std::endl;
                std::cout<<"Naslov: "<<i->second->DajNaslov()<<std::endl;
                std::cout<<"Pisac: "<<i->second->DajAutora()<<std::endl;
                std::cout<<"Zanr: "<<i->second->DajZanr()<<std::endl;
                std::cout<<"Godina izdavanja: "<<i->second->DajGodinuIzdavanja()<<std::endl;
            }
        }
        if(!zaduzio) std::cout<<"Nema zaduzenja za tog korisnika!";
    }


};
int main ()
{
    // Biblioteka b;
    // b.RegistrirajNovogKorisnika(1, "senija", "kaleta", "blabla", "123");
    // b.RegistrirajNovogKorisnika(2, "denija", "daleta", "blabla", "123");
    // b.RegistrirajNovuKnjigu(1, "dervi", "mesa", "roman", 1965);
    // Biblioteka b3;
    // b3.RegistrirajNovogKorisnika(1, "elma", "osmangaci", "blabla", "123");
    // b3.RegistrirajNovogKorisnika(2, "vedad", "daleta", "blabla", "123");
    // b3.RegistrirajNovuKnjigu(1, "lovac na zmajeve", "mesa", "roman", 1965);
    // {
    //     Biblioteka b2(b);
    //     b2.IzlistajKnjige();
    //     b2.IzlistajKorisnike();
    //     b2 = b3;
    //     std::cout<<"DODJELA\n";
    //     b2.IzlistajKnjige();
    //     Biblioteka b4 = std::move(b2);
    //     std::cout<<"INICIJALIZACIJA &&\n";
    //     b4.IzlistajKnjige();
    //     b2.IzlistajKnjige();
    // }
    Biblioteka b;
    int opcija_Bibilioteka = 1;
    while(opcija_Bibilioteka != 0) {
        std::cout<<std::endl;
        std::cout<<"Izaberite opciju za klasu Biblioteka: \n";
        std::cout<<"1-Registriraj Novog Korisnika\n";
        std::cout<<"2-Registriraj Novu Knjigu\n";
        std::cout<<"3-Nadji Knjigu\n";
        std::cout<<"4-Nadji Korisnika\n5-Izlistaj Knjige\n6-Izlistaj Korisnike\n7-Zaduzi Knjigu\n8-Razduzi Knjigu\n9-Prikazi Zaduzenja\n0-IZLAL\n";
        std::cin>>opcija_Bibilioteka;
        if(opcija_Bibilioteka == 1) {
            int id;
            std::string ime, prezime, adresa, telefon;
            std::cout<<"Evidencijski broj: ";
            std::cin>>id;
            std::cin.ignore(10000, '\n');
            std::cout<<"Unesi podatke za korisnika.\nIme: ";
            Korisnik korisnik;
            std::getline(std::cin, ime);
            std::cout<<"Prezime: ";
            std::getline(std::cin, prezime);
            std::cout<<"Aresa: ";
            std::getline(std::cin, adresa);
            std::cout<<"Broj: ";
            std::getline(std::cin, telefon);
            try {
                b.RegistrirajNovogKorisnika(id, ime, prezime, adresa, telefon);
            } catch(std::logic_error e) {
                std::cout<<e.what();
            }
        } else if(opcija_Bibilioteka == 2) {
            std::string naslov, ime, zanr;
            int godina_izdavanja, id;
            std::cout<<"Broj knjige: ";
            std::cin>>id;
            std::cin.ignore(10000, '\n');
            std::cout<<"Naslov: ";
            std::getline(std::cin, naslov);
            std::cout<<"Ime Pisca: ";
            std::getline(std::cin, ime);
            std::cout<<"Zanr: ";
            std::getline(std::cin, zanr);
            std::cout<<"Godina izdavanja: ";
            std::cin>>godina_izdavanja;
            try {
                b.RegistrirajNovuKnjigu(id, naslov, ime, zanr, godina_izdavanja);
            } catch(std::logic_error e) {
                std::cout<<e.what();
            }
        } else if(opcija_Bibilioteka == 3) {
            int id;
            std::cout<<"Unesi id knjige: ";
            std::cin>>id;
            try {
                std::cout<<b.NadjiKnjigu(id).DajNaslov();
            } catch (std::logic_error error) {
                std::cout << error.what() << std::endl;
            }

        } else if(opcija_Bibilioteka == 4) {
            int id;
            std::cout<<"Unesi id korisnika: ";
            std::cin>>id;
            try {
                std::cout<<b.NadjiKorisnika(id).ime<<" "<<b.NadjiKorisnika(id).prezime;
            } catch(std::logic_error e) {
                std::cout<<e.what();
            }
        } else if(opcija_Bibilioteka == 5) {
            b.IzlistajKnjige();
        } else if(opcija_Bibilioteka == 6) {
            b.IzlistajKorisnike();
        } else if(opcija_Bibilioteka == 7) {
            int id_knjige, id_korisnika;
            std::cout<<"Unesi id knjige i korisnika: ";
            std::cin>>id_knjige>>id_korisnika;
            try {
                b.ZaduziKnjigu(id_knjige, id_korisnika);
            } catch(std::logic_error e) {
                std::cout<<e.what();
            }
        } else if(opcija_Bibilioteka == 8) {
            int id;
            std::cout<<"Unesi id: ";
            std::cin>>id;
            try {
                b.RazduziKnjigu(id);
            } catch(std::logic_error e) {
                std::cout<<e.what();
            }
        } else if(opcija_Bibilioteka == 9) {
            int id;
            std::cout<<"Unesite id korisnika: ";
            std::cin>>id;
            try {
                b.PrikaziZaduzenja(id);
            } catch(std::logic_error e) {
                std::cout<<e.what();
            }
        } else std::cout<<"Nevalidan unos.\nUnesite ponovo!\n";

    }
    return 0;
}
