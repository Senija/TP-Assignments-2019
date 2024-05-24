#include <iostream>
#include <cstring>
#include <stdexcept>
#include <iomanip>
#include <memory>
#include <initializer_list>
#include <algorithm>
#include <vector>
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
    std::vector<std::shared_ptr<Tim>> timovi;
    bool DaLiPostojiTim(const char ime_tima[])
    {
        for(int i = 0; i < timovi.size(); i++) {
            if(strcmp(ime_tima, timovi[i]->DajImeTima()) == 0) return true;
        }
        return false;
    }
    std::shared_ptr<Tim> PokNaTim(const char ime_tima[])
    {
        for(int i = 0; i < timovi.size(); i++) {
            if(strcmp(ime_tima, timovi[i]->DajImeTima()) == 0) return timovi[i];
        }
    }
    static bool Manji(std::shared_ptr<Tim> tim1, std::shared_ptr<Tim> tim2)
    {
        if(tim1->DajBrojPoena() == tim2->DajBrojPoena()) {
            if(tim1->DajGolRazliku() == tim2->DajGolRazliku()) {
                if(strcmp(tim1->DajImeTima(), tim2->DajImeTima()) < 0) return true;
                else return false;
            } else return tim1->DajGolRazliku() > tim2->DajGolRazliku();
        } else return tim1->DajBrojPoena() > tim2->DajBrojPoena();
    }
public:
    explicit Liga() {}
    explicit Liga(std::initializer_list<Tim> lista_timova) : timovi(lista_timova.size())
    {
        for(auto i = 0; i != lista_timova.size(); i++) timovi[i] = std::make_shared<Tim>(*(lista_timova.begin() + i));
    }

    Liga(const Liga &l)//prepravka
    {
            for(int i = 0; i < l.timovi.size(); i++) {
                timovi.push_back(std::make_shared<Tim> (*l.timovi[i]));
            }

    }

    Liga(Liga &&l) : timovi(std::move(l.timovi)) {}

    Liga &operator = (const Liga &l)
    {
        timovi.resize(l.timovi.size());
        for(int i = 0; i != timovi.size(); i++){
            timovi[i] = std::make_shared<Tim>(*l.timovi[i]);
        }
        return *this;
    }
    Liga &operator = (Liga &&l)
    {
        timovi = std::move(l.timovi);
        return *this;
    }
    void DodajNoviTim(const char ime_tima[])
    {
        if(strlen(ime_tima) > 19) throw std::range_error ("Predugacko ime tima");
        if(DaLiPostojiTim(ime_tima)) throw std::logic_error ("Tim vec postoji");
        auto pok = std::make_shared<Tim>(ime_tima);
        timovi.push_back(pok);
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
        std::sort(timovi.begin(), timovi.end(), Manji);
        for(int i = 0; i < timovi.size(); i++) {
            timovi[i]->IspisiPodatke();
        }
    }

};


int main ()
{
    Liga prvaci{ "Sarajevo", "Zeljeznicar", "Zrinjski", "Borac", "Celik", "Jedinstvo",};
    prvaci.IspisiTabelu();
    try{
    for(;;) {
        try {
            char tim1[20], tim2[20];
            int br_golova1, br_golova2;
            std::cout<<"Unesite ime prvog tima (ENTER za kraj): ";
            std::cin.getline(tim1, 20);
            if(strlen(tim1) == 0) break;
            //prvaci.DodajNoviTim(tim1);
            std::cout<<"Unesite ime drugog tima: ";
            std::cin.getline(tim2, 20);
            //prvaci.DodajNoviTim(tim2);
            std::cout<<"Unesite broj postigutih golova za oba tima: ";
            std::cin>>br_golova1>>br_golova2;
            std::cin.ignore(10000, '\n');
            prvaci.RegistrirajUtakmicu(tim1, tim2, br_golova1, br_golova2);
            std::cout<<std::endl;
            prvaci.IspisiTabelu();
            
        } 
        
        catch(std::logic_error e) {
            std::cout<<e.what()<<std::endl;
        }
        
        catch(std::range_error e) {
            std::cout<<e.what()<<std::endl;
        }
    }
    // catch(std::domain_error e) {
    //     std::cout<<e.what()<<std::endl;
    // }
 }catch(...){
    
}

return 0;
}
