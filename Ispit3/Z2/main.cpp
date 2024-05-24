//TP 2018/2019: Ispit 3, Zadatak 2
#include <iostream>
#include <stdexcept>
#include <string.h>
#include <vector>
#include <memory>
#include <string>
#include <algorithm>
class Grad
{
    char ime_grada[50];
    int broj_stanovnika;
public:
    Grad(const char ime[], int broj_stanovnika)
    {
        if(strlen(ime) > 49 || broj_stanovnika <= 0) throw std::domain_error("Neispravni podaci");
        strcpy(ime_grada, ime);
        Grad::broj_stanovnika = broj_stanovnika;
    }
    const char *DajIme() const
    {
        return ime_grada;
    }
    int DajBrojStanovnika() const
    {
        return broj_stanovnika;
    }
    int &DajBrojStanovnika()
    {
        return broj_stanovnika;
    }

};

class Gradovi
{
    std::vector<std::shared_ptr<Grad>> VektorGradova;
    bool DaLiPostojiGrad(const char ime[]) const
    {
        int brojac = -1;
        for(auto i = VektorGradova.begin(); i != VektorGradova.end(); i++) {
            if(strcmp((*i) -> DajIme(), ime) == 0) return true;
        }
        return false;
    }

    int VratiPokNaGrad(const char ime[]) const
    {
        for(auto i = 0; i != VektorGradova.size(); i++) {
            if(strcmp(VektorGradova[i] -> DajIme(), ime) == 0) return i;
        }
    }

public:
    Gradovi(){
        
    }
    void DodajGrad(const char ime[], int broj_stanovnika)
    {
        if(strlen(ime) > 49 || broj_stanovnika <= 0) throw std::domain_error("Neispravni podaci");
        if(DaLiPostojiGrad(ime)) throw std::domain_error ("Grad vec postoji");
        VektorGradova.push_back(std::make_shared<Grad>(ime, broj_stanovnika));
    }

    void ObrisiGrad(const char ime[])
    {
        if(DaLiPostojiGrad(ime)) {
            auto it = VratiPokNaGrad(ime);
            VektorGradova.erase(VektorGradova.begin() + it);
        } else return;
    }

    int DajBrojGradova() const
    {
        return VektorGradova.size();
    }
    Gradovi(const Gradovi &g)
    {
        //VektorGradova.resize(g.VektorGradova.size());
        for(int i = 0; i < g.VektorGradova.size(); i++) VektorGradova.push_back(std::make_shared<Grad>(*g.VektorGradova[i]));
    }

    Gradovi( Gradovi &&g) : VektorGradova(std::move(g.VektorGradova))
    {

    }

    Gradovi &operator =(const Gradovi &g)
    {
        std::vector<std::shared_ptr<Grad>> Pomocni;
        for(int i = 0; i < g.VektorGradova.size(); i++) {
            Pomocni.push_back(std::make_shared<Grad>(*g.VektorGradova[i]));
        }
        VektorGradova = Pomocni;
        return *this;
    }

    Gradovi & operator =(Gradovi &&g)
    {
        std::swap(VektorGradova, g.VektorGradova);
        return *this;
    }

    int operator [] (const char ime[]) const
    {
        if(!DaLiPostojiGrad(ime)) throw std::range_error ("Nepostojeci grad");
        else {
            auto index = VratiPokNaGrad(ime);
            return VektorGradova[index]->DajBrojStanovnika();
        }
    }

    int &operator [] (const char ime[])
    {
        if(!DaLiPostojiGrad(ime)) throw std::range_error ("Nepostojeci grad");
        else {
            auto index = VratiPokNaGrad(ime);
            return VektorGradova[index]->DajBrojStanovnika();
        }
    }
    
    void SortirajGradove(){
        //std::vector<Grad*> VektorGlupih(VektorGradova.size());
        //for(int i = 0; i < VektorGradova.size(); i++) VektorGlupih[i] = VektorGradova[i].get();
        std::sort(VektorGradova.begin(), VektorGradova.end(), [](std::shared_ptr<Grad> g1, std::shared_ptr<Grad> g2){
            return g1->DajBrojStanovnika() > g2->DajBrojStanovnika();
        });
    }
    
    void Ispisi(std::ostream &tok = std::cout) const{
        for(auto i = VektorGradova.begin(); i != VektorGradova.end(); i++){
            tok<<(*i) -> DajIme()<<": "<<(*i)->DajBrojStanovnika()<<std::endl;
        }
    }
    
    // void ObnoviIzBinarneDatoteke(){
        
    // }


};


int main ()
{
        std::cout << "AT12" << std::endl;
    {
        //AT12 - testiranje preklopljenog operatora []
        Gradovi g;
        g.DodajGrad("Tuzla", 130000);
        g.DodajGrad("Bihac", 50000);
        g.DodajGrad("Sarajevo", 350000);
        g.DodajGrad("Mostar", 100000);
        g.DodajGrad("Zenica", 113000);
        std::cout << "Tuzla: " << g["Tuzla"] << std::endl << 
                     "Bihac: " << g["Bihac"] << std::endl << 
                     "Sarajevo: " << g["Sarajevo"] << std::endl << 
                     "Zenica: " << g["Zenica"] << std::endl;
    }

        std::cout << "AT13" << std::endl;
    {
        //AT13 - testiranje preklopljenog operatora [] sa izuzecima
        Gradovi g;
        g.DodajGrad("Tuzla", 130000);
        g.ObrisiGrad("Tuzla");
        g.DodajGrad("Bihac", 50000);
        g.DodajGrad("Sarajevo", 350000);
        g.DodajGrad("Mostar", 100000);
        
        try
        {
          std::cout << g["Tuzla"];
          std::cout << "Ovo se ne smije ispisati";
        }
        catch(std::range_error e)
        {
          std::cout << e.what() << std::endl;
        }
        catch(...)
        {
          std::cout << "Pogrešan izuzetak";
        }
        
        std::cout << "Bihac: " << g["Bihac"] << std::endl;
        g.DodajGrad("Tuzla", 130000);
        g.ObrisiGrad("Bihac");
        
        std::cout << "Tuzla: " << g["Tuzla"] << std::endl;
        
        try
        {
          std::cout << g["Bihac"];
          std::cout << "Ovo se ne smije ispisati";
        }
        catch(std::range_error e)
        {
          std::cout << e.what() << std::endl;
        }
        catch(...)
        {
          std::cout << "Pogrešan izuzetak";
        }
    }
        std::cout << "AT15" << std::endl;
    {
        //AT15 - testiranje preklopljenog operatora []
            // kada se koristi sa lijeve strane znaka =
        Gradovi g;
        g.DodajGrad("Tuzla", 130000);
        g.DodajGrad("Bihac", 50000);
        g.DodajGrad("Sarajevo", 350000);
        g.DodajGrad("Mostar", 100000);
        g.DodajGrad("Zenica", 113000);
        g["Tuzla"] = 130001;
        g["Sarajevo"] = 350001;
        g["Mostar"] = 100001;
        
        std::cout << "Tuzla: " << g["Tuzla"] << std::endl << 
                     "Bihac: " << g["Bihac"] << std::endl << 
                     "Sarajevo: " << g["Sarajevo"] << std::endl << 
                     "Zenica: " << g["Zenica"] << std::endl <<
                     "Mostar: " << g["Mostar"] << std::endl;
    }
    return 0;
}
