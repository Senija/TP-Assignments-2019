#include <iostream>
#include <string>
#include <stdexcept>
#include <utility>
#include <map>
#include <new>

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
    std::map<int, Korisnik*> korisnici;
    std::map<int, Knjiga*> knjige;
    template<typename Tip1>
    void PostaviNaNullptr(std::map<int, Tip1> &m)
    {
        for(auto i = m.begin(); i != m.end(); i++) {
            //delete i->second;
            i->second = nullptr;
            //b.korisnici.erase(i->first);

        }
        // for(auto i = b.knjige.begin(); i != b.knjige.end(); i++) {
        //     //delete i->second;
        //     i->second = nullptr;
        //     //b.knjige.erase(i->first);
        // }
    }
    template<typename Tip2>
    void Dealokacija(std::map<int, Tip2> &m)
    {
        for(auto i = m.begin(); i != m.end(); i++) {
            delete i->second;
            i->second = nullptr;
            //b.korisnici.erase(i->first);

        }
        // for(auto i = b.knjige.begin(); i != b.knjige.end(); i++) {
        //     delete i->second;
        //     i->second = nullptr;
        //     //b.knjige.erase(i->first);
        // }
    }
    template<typename TipE>
    bool DaLiPostoji(const std::map<int, TipE> &m, int id) const
    {
        if(m.find(id) != m.end()) return true; // postoji
        return false;
    }

    bool JesuLiJednakiKorisnici(Korisnik *k1, Korisnik *k2) const
    {
        if(k1->ime == k2->ime && k1->prezime == k2->prezime && k1->adresa == k2->adresa && k1->telefon == k2->telefon) return true;
        return false;
    }
public:
    Biblioteka() {} // treba li nullptr;
    Biblioteka(int id_korisnika, int id_knjige) //??????????
    {
        Korisnik *korisnik = nullptr;
        Knjiga *knjiga = nullptr;
        korisnici.insert(std::pair<int, Korisnik*>(id_korisnika, korisnik));
        knjige.insert(std::pair<int, Knjiga*>(id_knjige, knjiga));
    }
    //MOVE NA KRAJU??????
    Biblioteka(const Biblioteka &biblioteka)  //duboko kopiranje
    {
        std::map<int, Korisnik*> korisnik_pom;
        std::map<int, Knjiga*> knjiga_pom;
        try {
            for(auto i = biblioteka.korisnici.begin(); i!= biblioteka.korisnici.end(); i++) {
                //auto pomocni = biblioteka.korisnici.second;

                Korisnik *pomocni = nullptr;
                pomocni = new Korisnik(*(i->second));
                korisnik_pom.insert(std::pair<int, Korisnik*>(i->first, pomocni));
            }
            for(auto i = biblioteka.knjige.begin(); i!= biblioteka.knjige.end(); i++) {
                //auto pomocni = biblioteka.korisnici.second;
                Knjiga *pomocni = nullptr;
                pomocni = new Knjiga(*(i->second));
                knjiga_pom.insert(std::pair<int, Knjiga*>(i->first, pomocni));
            }

        } catch(...) {
            if(korisnik_pom.size() != 0) Dealokacija(korisnik_pom);
            if(knjiga_pom.size() != 0) Dealokacija(knjiga_pom);
            throw;
        }
        korisnici = korisnik_pom; // ovdje moze move 
        knjige = knjiga_pom;
        PostaviNaNullptr(korisnik_pom);
        PostaviNaNullptr(knjiga_pom);
        korisnik_pom.clear();
        knjiga_pom.clear();
    }
    Biblioteka(Biblioteka &&biblioteka)
    {
        korisnici = biblioteka.korisnici;
        knjige = biblioteka.knjige;
        PostaviNaNullptr(biblioteka.korisnici);
        PostaviNaNullptr(biblioteka.knjige);
        biblioteka.korisnici.clear();
        biblioteka.knjige.clear();
    }
    Biblioteka& operator= (const Biblioteka &biblioteka)
    {
        std::map<int, Knjiga*> novi_prostorKnjige;
        std::map<int, Korisnik*> novi_prostorKorisnik;
        try {
            for(auto i = biblioteka.knjige.begin(); i != biblioteka.knjige.end(); i++) {
                Knjiga *pomocni = new Knjiga(*(i->second));
                novi_prostorKnjige.insert(std::pair<int, Knjiga*>(i->first, pomocni));
            }

            for(auto i = biblioteka.korisnici.begin(); i != biblioteka.korisnici.end(); i++) {
                Korisnik *pomocni= new Korisnik(*(i->second));
                novi_prostorKorisnik.insert(std::pair<int, Korisnik*>(i->first, pomocni));
            }
            Dealokacija(korisnici);
            Dealokacija(knjige);
            std::swap(korisnici, novi_prostorKorisnik); // ili dodijeli pa postavi na nullptr
            std::swap(knjige, novi_prostorKnjige); // postaviti na nuluuu!!!!!!!!!!!

        } catch(...) {
            if(novi_prostorKnjige.size() != 0 )Dealokacija(novi_prostorKnjige);
            if(novi_prostorKorisnik.size() != 0 )Dealokacija(novi_prostorKorisnik);
            //throw;

        }
        return *this;
    }
    Biblioteka & operator =(Biblioteka &&biblioteka)
    {
        std::swap(korisnici, biblioteka.korisnici);
        std::swap(knjige, biblioteka.knjige);
        // PostaviNaNullptr(biblioteka.korisnici);
        // PostaviNaNullptr(biblioteka.knjige);
        // biblioteka.korisnici.clear();
        // biblioteka.knjige.clear();
        return *this;
    }
    ~Biblioteka()
    {
        for(auto i = korisnici.begin(); i != korisnici.end(); i++) {
            delete i->second;
            i->second = nullptr;
        }
        for(auto i = knjige.begin(); i != knjige.end(); i++) {
            delete i->second;
            i->second = nullptr;
        }
        korisnici.clear();
        knjige.clear();
    }
    void RegistrirajNovogKorisnika( int id_korisnika, std::string ime, std::string prezime, std::string adresa, std::string mobile)
    {
        if(DaLiPostoji(korisnici, id_korisnika)) throw std::logic_error ("Korisnik vec postoji");
        Korisnik *pomocna =nullptr;
        try {

            pomocna = new Korisnik();
            pomocna->ime = ime;
            pomocna->prezime = prezime;
            pomocna->adresa = adresa;
            pomocna->telefon = mobile;
            korisnici.insert(std::pair<int, Korisnik*>(id_korisnika, pomocna));
        } catch(...) {
            delete pomocna;
            throw;
        }
    }
    void RegistrirajNovuKnjigu(int id_knjige, std::string naslov, std::string ime_pisca, std::string zanr, int godina_izdavanja)
    {
        if(DaLiPostoji(knjige, id_knjige)) throw std::logic_error ("Knjiga vec postoji");
        Knjiga *pomocna =nullptr;
        try {

            pomocna = new Knjiga(naslov, ime_pisca, zanr, godina_izdavanja);
            knjige.insert(std::pair<int, Knjiga*>(id_knjige, pomocna));
        } catch(...) {
            delete pomocna;
            throw;
        }

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

    Biblioteka b; //promjenit lokaciju
    // int opcija_klase = 5;
    // std::cout<<"Izaberite opciju: \n1-Klasa Knjiga\n2-Klasa Biblioteka\n0-IZLAZ\n";
    // std::cin>>opcija_klase;
    // if(opcija_klase == 0) break;
    // if(opcija_klase == 1) {
    //     int  opcija_Knjige = 1;
    //     std::string naslov, ime, zanr;
    //     int godina_izdavanja;
    //     std::cin.ignore(10000, '\n');
    //     std::cout<<"Naslov: ";
    //     std::getline(std::cin, naslov);
    //     std::cout<<"Ime Pisca: ";
    //     std::getline(std::cin, ime);
    //     std::cout<<"Zanr: ";
    //     std::getline(std::cin, zanr);
    //     std::cout<<"Godina izdavanja: ";
    //     std::cin>>godina_izdavanja;
    //     Knjiga k(naslov, ime, zanr, godina_izdavanja);

    //     while(opcija_Knjige != 0) {
    //         std::cout<<std::endl;
    //         std::cout<<"Izaberite opciju za klasu Knjiga: \n";
    //         std::cout<<"1-Daj naslov\n";
    //         std::cout<<"2-Daj autora\n3-Daj zanr\n4-Daj godinu izdavanja\n5-Daj kod koga je\n6-Zaduzi knjigu\n7-Razduzi knjigu\n0-IZLAL\n";
    //         std::cin>>opcija_Knjige;

    //         if(opcija_Knjige == 1) {
    //             std::cout<<k.DajNaslov();
    //         } else if(opcija_Knjige == 2) {
    //             std::cout<<k.DajAutora();
    //         } else if(opcija_Knjige == 3) {
    //             std::cout<<"Zanr: "<<k.DajZanr();
    //         } else if(opcija_Knjige == 4) {
    //             std::cout<<"Izdata: "<<k.DajGodinuIzdavanja();
    //         } else if(opcija_Knjige == 5) {
    //             auto Pok_korisnik = k.DajKodKogaJe();
    //             if(Pok_korisnik == nullptr) std::cout<<"Knjiga nije nije zaduzena";
    //             else std::cout<<Pok_korisnik->ime<<" "<<Pok_korisnik->prezime<<"je zaduzio/la knjigu";
    //         } else if(opcija_Knjige == 6) {
    //             std::cin.ignore(10000, '\n');
    //             std::cout<<"Unesi podatke za korisnika.\nIme: ";
    //             Korisnik korisnik;
    //             std::getline(std::cin, korisnik.ime);
    //             std::cout<<"Prezime: ";
    //             std::getline(std::cin, korisnik.prezime);
    //             std::cout<<"Aresa: ";
    //             std::getline(std::cin, korisnik.adresa);
    //             std::cout<<"Broj: ";
    //             std::getline(std::cin, korisnik.telefon);
    //             k.ZaduziKnjigu(korisnik);

    //         } else if(opcija_Knjige == 7) {
    //             k.RazduziKnjigu();
    //         }
    //     }


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
