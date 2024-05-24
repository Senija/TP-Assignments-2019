#include <iostream>
#include <cstring>
#include <stdexcept>
#include <iomanip>
#include <new>
#include <initializer_list>
#include <algorithm>
#include <fstream>
class Tim
{

    char ime_tima[20];
    int broj_odigranih;
    int broj_pobjeda;
    int broj_nerijesenih;
    int broj_poraza, broj_datih, broj_primljenih, broj_poena;
public:
    Tim(const char ime[]) : broj_odigranih(0), broj_pobjeda(0), broj_nerijesenih(0), broj_poraza(0), broj_datih(0), broj_primljenih(0), broj_poena(0)
    {
        if(strlen(ime) > 19) throw std::range_error ("Predugacko ime tima");
        strcpy(ime_tima, ime);
    }
    void ObradiUtakmicu(int broj_datih, int broj_primljenih)
    {
        if(broj_datih < 0 || broj_primljenih < 0) throw std::range_error ("Neispravan broj golova");
        if(broj_datih > broj_primljenih) {
            broj_pobjeda++;
            broj_odigranih++;
            Tim::broj_datih += broj_datih;
            Tim::broj_primljenih += broj_primljenih;
            broj_poena += 3;
        } else if(broj_datih == broj_primljenih) {
            broj_nerijesenih++;
            broj_odigranih++;
            Tim::broj_datih += broj_datih;
            Tim::broj_primljenih += broj_primljenih;
            broj_poena += 1;
        } else {
            broj_poraza++;
            broj_odigranih++;
            Tim::broj_datih += broj_datih;
            Tim::broj_primljenih += broj_primljenih;
        }
    }
    const char *DajImeTima() const
    {
        return ime_tima;
    }
    int DajBrojPoena() const
    {
        return broj_poena;
    }
    int DajGolRazliku() const
    {
        return broj_datih - broj_primljenih;
    }
    void IspisiPodatke() const
    {
        std::cout<<std::left<<std::setw(20)<<ime_tima<<std::right<<std::setw(4)<<broj_odigranih<<std::setw(4)<<broj_pobjeda<<std::setw(4)<<broj_nerijesenih<<std::setw(4)<<std::setw(4)<<broj_poraza<<std::setw(4)<<broj_datih<<std::setw(4)<<broj_primljenih<<std::setw(4)<<broj_poena<<std::endl;

    }
};

class Liga
{
    const int max_br_timova ;
    int broj_timova;
    Tim **timovi;
    bool DaLiPostojiTim(const char ime_tima[])
    {
        for(int i = 0; i < broj_timova; i++) {
            if(strcmp(ime_tima, timovi[i]->DajImeTima()) == 0) return true;
        }
        return false;
    }
    Tim *PokNaTim(const char ime_tima[])
    {
        for(int i = 0; i < broj_timova; i++) {
            if(strcmp(ime_tima, timovi[i]->DajImeTima()) == 0) return timovi[i];
        }
    }
    static bool Manji(Tim *tim1, Tim *tim2)
    {
        if(tim1->DajBrojPoena() == tim2->DajBrojPoena()) {
            if(tim1->DajGolRazliku() == tim2->DajGolRazliku()) {
                if(strcmp(tim1->DajImeTima(), tim2->DajImeTima()) < 0) return true;
                else return false;
            } else return tim1->DajGolRazliku() > tim2->DajGolRazliku();
        } else return tim1->DajBrojPoena() > tim2->DajBrojPoena();
    }
public:
    explicit Liga(int velicina_lige) : timovi(new Tim *[velicina_lige] {}), max_br_timova(velicina_lige), broj_timova(0) {}
    explicit Liga(std::initializer_list<Tim> lista_timova) : max_br_timova(lista_timova.size()), broj_timova(lista_timova.size()), timovi(new Tim*[lista_timova.size()] {})
    {
        for(auto i = 0; i != lista_timova.size(); i++) timovi[i] = new Tim(*(lista_timova.begin() + i));
    }

    Liga(const Liga &l):max_br_timova(l.broj_timova)
    {
        //if(l.max_br_timova != max_br_timova)throw std::logic_error ("Nesaglasni kapaciteti liga");
        timovi = new Tim*[l.max_br_timova] {};
        broj_timova = l.broj_timova;
        try {
            for(int i = 0; i < l.broj_timova; i++) {
                timovi[i] = new Tim(*l.timovi[i]);
            }
        } catch(...) {
            for(int i = 0; i < l.broj_timova; i++) delete timovi[i];
            delete timovi;
            throw;
        }

    }

    Liga(Liga &&l):max_br_timova(l.broj_timova)
    {
        //if(l.max_br_timova != max_br_timova)throw std::logic_error ("Nesaglasni kapaciteti liga");
        broj_timova = l.broj_timova;
        timovi = l.timovi;
        l.timovi = nullptr;
        l.broj_timova = 0;
    }
    explicit Liga(std::string ime_datoteke): max_br_timova(0) 
    {
        std::ifstream ulazni_tok(ime_datoteke, std::ios::binary);
        if(!ulazni_tok) throw std::logic_error("Datoteka ne postoji");
        ulazni_tok.read(reinterpret_cast<char*>(this), sizeof *this);
        if(broj_timova > max_br_timova) throw std::logic_error ("Datoteka sadrzi fatalne greske");
        try {
            timovi = new Tim*[max_br_timova] {};
            for(int i = 0; i < broj_timova; i++) {
                timovi[i] = new Tim("Nulti");
                ulazni_tok.read(reinterpret_cast<char*>(timovi[i]), sizeof(Tim));
            }
        }
        catch(...){
            for(int i = 0; i < broj_timova; i++) delete timovi[i];
            delete[] timovi;
        }
        if(!ulazni_tok){
            for(int i = 0; i < broj_timova; i++) delete timovi[i];
            delete[] timovi;
            throw std::logic_error ("Problemi pri citanju datoteke");
        }
    }

    ~Liga()
    {
        for(int i = 0; i < broj_timova; i++) delete timovi[i];
        delete[] timovi;
    }

    Liga &operator = (const Liga &l)
    {
        if(l.max_br_timova != max_br_timova)throw std::logic_error ("Nesaglasni kapaciteti liga");
        if(l.broj_timova > broj_timova) {
            try {
                for(int i = broj_timova; i < l.broj_timova; i++)
                    timovi[i] = new Tim(*l.timovi[i]);
            } catch(...) {
                for(int i = broj_timova; i < l.broj_timova; i++) {
                    delete timovi[i];
                    timovi[i] = nullptr;
                }
                throw;
            }
        } else {
            for(int i = l.broj_timova; i < broj_timova; i++) {
                delete timovi[i];
                timovi[i] = nullptr;
            }
        }
        broj_timova = l.broj_timova;
        for(int i = 0; i < broj_timova; i++) *timovi[i] = *l.timovi[i];
        return *this;
    }
    Liga &operator = (Liga &&l)
    {
        if(l.max_br_timova != max_br_timova)throw std::logic_error ("Nesaglasni kapaciteti liga");
        std::swap(broj_timova, l.broj_timova);
        std::swap(timovi, l.timovi);
        return *this;
    }
    void DodajNoviTim(const char ime_tima[])
    {
        if(strlen(ime_tima) > 19) throw std::range_error ("Predugacko ime tima");
        if(broj_timova  == max_br_timova) throw std::range_error ("Liga popunjena");
        if(DaLiPostojiTim(ime_tima)) throw std::logic_error ("Tim vec postoji");
        Tim *pok = new Tim(ime_tima);
        timovi[broj_timova] = pok;
        broj_timova++;
    }
    void RegistrirajUtakmicu(const char tim1[], const char tim2[], int rezultat_1, int rezultat_2)
    {
        if(!DaLiPostojiTim(tim1) || !DaLiPostojiTim(tim2)) throw std::logic_error ("Tim nije nadjen");
        if(rezultat_1 < 0 || rezultat_2 < 0) throw std::range_error ("Neispravan broj golova");
        auto PokTim1 = PokNaTim(tim1);
        PokTim1->ObradiUtakmicu(rezultat_1, rezultat_2);
        auto PokTim2 = PokNaTim(tim2);
        PokTim2->ObradiUtakmicu(rezultat_2, rezultat_1);

    }
    void IspisiTabelu()
    {
        std::sort(timovi, timovi+broj_timova, Manji);
        for(int i = 0; i < broj_timova; i++) {
            timovi[i]->IspisiPodatke();
        }
    }
    void ObrisiSve()
    {
        for(int i = 0; i < broj_timova; i++) {
            delete timovi[i];
            timovi[i] = nullptr;
        }
        delete[] timovi;
        timovi = nullptr;
    }
    void SacuvajStanje(std::string ime_datoteke) const
    {
        std::ofstream izlazni_tok(ime_datoteke, std::ios::binary);
        izlazni_tok.write(reinterpret_cast<const char*>(this), sizeof *this); //pise u datoteku cout ofstream
        for(int i = 0; i < broj_timova; i++){
            izlazni_tok.write(reinterpret_cast<char*> (timovi[i]), sizeof(Tim) );
        }
        if(!izlazni_tok)
            throw std::logic_error("Problemi pri upisu u datoteku");

    }
    void AzurirajIzDatoteke(std::string ime_datoteke)
    {
        std::ifstream ulazni_tok(ime_datoteke);
        if(!ulazni_tok) throw std::logic_error("Datoteka ne postoji");
        //if (broj_timova +1 == max_br_timova) throw std::range_error ("Timovi popunjeni");
        char ime_tima1[20];
        while(ulazni_tok.getline(ime_tima1, sizeof(ime_tima1))) {
            char ime_tima2[20];
            ulazni_tok.getline(ime_tima2, sizeof ime_tima2);
            int golovi_tim1, golovi_tim2;
            char znak;
            ulazni_tok>>golovi_tim1>>znak>>golovi_tim2>>std::ws;
            if(!ulazni_tok || golovi_tim1 < 0 || golovi_tim2 < 0) break;
            RegistrirajUtakmicu(ime_tima1, ime_tima2, golovi_tim1, golovi_tim2);
            //ulazni_tok.ignore(10000, '\n');
            

        }
        if(!ulazni_tok && !ulazni_tok.eof()) throw std::logic_error ("Problemi pri citanju datoteke");
    }

};


int main ()
{
      Liga l (10);
  l.DodajNoviTim("Tim1"); l.DodajNoviTim("Tim2"); l.DodajNoviTim("Tim3"); l.DodajNoviTim("Tim4");
	l.RegistrirajUtakmicu ("Tim1", "Tim4", 3, 1);
	std::remove ("liga.txt");
	const char *c = R"eon(Tim1
Tim2
3:2
Tim1
Tim2
3:2
Tim3
Tim1
2:1
Tim2
Tim3
0:1)eon";
  std::ofstream ("liga.txt") << c;
	l.AzurirajIzDatoteke("liga.txt");
	l.IspisiTabelu();
    // Liga("LIGA.DAT");
    // Liga prvaci{ "Sarajevo", "Zeljeznicar", "Zrinjski", "Borac", "Celik", "Jedinstvo",};
    // prvaci.IspisiTabelu();
    // try {
    //     for(;;) {
    //         try {
                
    //             char tim1[20], tim2[20];
    //             int br_golova1, br_golova2;
    //             std::cout<<"Unesite ime prvog tima (ENTER za kraj): ";
    //             std::cin.getline(tim1, 20);
    //             if(strlen(tim1) == 0) break;
    //             //prvaci.DodajNoviTim(tim1);
    //             std::cout<<"Unesite ime drugog tima: ";
    //             std::cin.getline(tim2, 20);
    //             //prvaci.DodajNoviTim(tim2);
    //             std::cout<<"Unesite broj postigutih golova za oba tima: ";
    //             std::cin>>br_golova1>>br_golova2;
    //             std::cin.ignore(10000, '\n');
    //             prvaci.RegistrirajUtakmicu(tim1, tim2, br_golova1, br_golova2);
    //             std::cout<<std::endl;
    //             prvaci.IspisiTabelu();
    //             prvaci.SacuvajStanje(LIGA.DAT);

    //         }

    //         catch(std::logic_error e) {
    //             std::cout<<e.what()<<std::endl;
    //         }

    //         catch(std::range_error e) {
    //             std::cout<<e.what()<<std::endl;
    //         }
    //     }
    //     // catch(std::domain_error e) {
    //     //     std::cout<<e.what()<<std::endl;
    //     // }
    // } catch(...) {

    // }

    return 0;
}
