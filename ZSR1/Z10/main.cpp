//TP 2018/2019: ZSR 1, Zadatak 10
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <complex>
#include <stdexcept>
std::vector<std::complex<double>> ProcitajIzTekstualne(std::string ime_datoteke)
{
    std::ifstream ulazni_tok(ime_datoteke);
    if(!ulazni_tok) throw std::logic_error ("Datoteka ne postoji!");
    std::vector<std::complex<double>> VektorKompleksnih;
    while(ulazni_tok) {
        double re, im;
        char znak;
        ulazni_tok>>re>>znak>>im;
        std::complex<double> Smjesti{re,im};
        VektorKompleksnih.push_back(Smjesti);
        if(ulazni_tok.eof()) break;
        ulazni_tok>>std::ws;

    }
    return VektorKompleksnih;

}

// void NapraviBinarnuDatoteku(const std::vector<std::complex<double>> &VektorKompleksnih)
// {
//     std::ofstream izlazni_tok("KOMPLEKSNI.BIN", std::ios::binary);
//     if(!izlazni_tok) throw std::logic_error("Kreiranje datoteke nije uspjelo!");
//     izlazni_tok.write(reinterpret_cast<const char*>(&VektorKompleksnih), sizeof VektorKompleksnih);
//     std::ifstream ulazni_tok("KOMPLEKSNI.BIN", std::ios::binary);
//     std::vector<std::complex<double>> Provjera(VektorKompleksnih.size());
//     ulazni_tok.read(reinterpret_cast<char*>(&Provjera), sizeof Provjera);
//     for(auto i = Provjera.begin(); i != Provjera.end(); i++) {
//         std::cout<<"{"<<i->real()<<","<<i->imag()<<"}"<<std::endl;
//     }
//     // std::fstream ulazno_izlazni_tok("KOMPLEKSNI.BIN"m std::ios::binary);
//     // while(ulazno_izlazni_tok){
        
//     // }
    
// }
int main ()
{
    std::ifstream ulazni_tok("KOMPLEKSNI.TXT");
    std::ofstream izlazni_tok_bin("KOMPLEKSNI.DAT", std::ios::binary);
    if(!ulazni_tok) throw std::logic_error ("Datoteka ne postoji!");
    while(ulazni_tok) {
        double re, im;
        char znak;
        ulazni_tok>>re>>znak>>im;
        if(znak != ',' || !ulazni_tok) throw std::logic_error ("Neispravni podaci!");
        std::complex<double> Smjesti{re,im};
        if(ulazni_tok.eof()) break;
        ulazni_tok>>std::ws;
        izlazni_tok_bin.write(reinterpret_cast<char*>(&Smjesti), sizeof (std::complex<double>));
    }
    
    std::fstream ulazno_izlazni_tok("KOMPLEKSNI.DAT", std::ios::binary | std::ios::in | std::ios::out);
    ulazno_izlazni_tok.seekg(0, std::ios::end);
    auto duzina_datoteke = ulazno_izlazni_tok.tellg();
    auto broj_elemenata = duzina_datoteke/sizeof(std::complex<double>);
    for(int i = 0; i < broj_elemenata; i++){
        //hocu da procitam prvo
        
        std::complex<double> prvi;
        ulazno_izlazni_tok.seekg(i, std::ios::beg);
        ulazno_izlazni_tok.read(reinterpret_cast<char*>(&prvi), sizeof(std::complex<double>));
        std::complex<double> obrnuto(prvi.imag(), prvi.real());
        ulazno_izlazni_tok.write(reinterpret_cast<char*>(&obrnuto), sizeof obrnuto);
        ulazno_izlazni_tok.seekg(0, std::ios::cur);
    }
    
    for(auto i = 0; i < broj_elemenata; i++){
         std::complex<double> prvi;
        ulazno_izlazni_tok.seekg(i, std::ios::beg);
        ulazno_izlazni_tok.read(reinterpret_cast<char*>(&prvi), sizeof(std::complex<double>));
        std::cout<<prvi<<std::endl;
    }
    
    // std::vector<std::complex<double>> VektorKompleksnih(4);
    // std::ifstream ulazni_tok_bin("KOMPLEKSNI.BIN", std::ios::binary);
    // ulazni_tok_bin.read(reinterpret_cast<char*>(&VektorKompleksnih), sizeof VektorKompleksnih);
    // for(auto i = VektorKompleksnih.begin(); i != VektorKompleksnih.end(); i++){
    //      std::cout<<"{"<<i->real()<<","<<i->imag()<<"}"<<std::endl;
    // }
    return 0;
}
