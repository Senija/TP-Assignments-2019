//TP 2018/2019: ZSR 5, Zadatak 1
#include <iostream>
#include <fstream>
#include <stdexcept>

template<typename TipElemenata>
class DatotecniKontejner {
    std::fstream tok;
    public:
    DatotecniKontejner(const std::string &ime_datoteke){
        if(!std::ifstream(ime_datoteke, std::ios::binary)){
            std::ofstream(ime_datoteke, std::ios::binary);
        }
        tok.open(ime_datoteke, std::ios::in | std::ios::out | std::ios::binary);
        if(!tok) throw std::logic_error("Problemi pri kreiranju datoteke");
    }
    void DodajNoviElement(const TipElemenata &element){
        tok.seekp(0,std::ios::end);
        tok.write(reinterpret_cast<const char*>(&element), sizeof(TipElemenata));
        tok.seekp(0,std::ios::beg);
        if(!tok) throw std::logic_error ("Problemi pri upisu elementa");
    }
    int DajBrojElemenata(){
        tok.seekg(0, std::ios::end);
        auto duzina_datoteke = tok.tellg();
        return duzina_datoteke / sizeof(TipElemenata);
        tok.seekg(0, std::ios::beg);
    }
    TipElemenata DajElement(int pozicija){
        if(pozicija < 0 || pozicija >= DajBrojElemenata()) throw std::range_error("Ne postoji pozicija!");
        tok.seekg(pozicija, std::ios::beg);
        TipElemenata element;
        tok.read(reinterpret_cast<char*>(&element), sizeof (TipElemenata));
        tok.seekg(0, std::ios::beg);
        return element;
    }
    void IzmijeniElement(int pozicija, const TipElemenata &element){
        tok.seekp(pozicija, std::ios::beg);
        tok.write(reinterpret_cast<const char*>(&element), sizeof (TipElemenata));
        if(!tok) throw std::logic_error ("Problemi pri upisu elementa");
        tok.seekg(0, std::ios::beg);
    }
};
int main ()
{
    DatotecniKontejner<int> datoteka("DATOTEKA.DAT");
    datoteka.DodajNoviElement(15);
    std::cout<<datoteka.DajBrojElemenata()<<std::endl;
    
	return 0;
}