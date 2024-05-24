#include <iostream>
#include <fstream>
#include <stdexcept>

int main(){
    std::ifstream citac("BROJEVI.TXT");
    if(!citac) throw std::logic_error ("Ne postoji datoteka");
    std::ofstream pisac_bin("BROJEVI.DAT", std::ios::binary); 
    while(citac){
        //std::ofstream pisac_bin("BROJEVI.DAT", std::ios::binary); 
        if(citac.eof()) break;
        double broj;
        citac >> broj >>std::ws;
        if(!citac && !citac.eof()) throw std::logic_error("Problemi pri citanju");
        pisac_bin.write(reinterpret_cast<char*>(&broj), sizeof broj);
        if(!pisac_bin) throw std::logic_error("Problemi pri upisu");
    }

    pisac_bin.close();
    std::fstream citac_pisac("BROJEVI.DAT", std::ios::binary | std::ios::in | std::ios::out);
    citac_pisac.seekg(0, std::ios::end);
    auto broj_elemenata = citac_pisac.tellg()/ sizeof (double);
    std::fstream citac_pisac2("BROJEVI.DAT", std::ios::binary | std::ios::in | std::ios::out);
    for(int i = 0; i <= broj_elemenata/2; i++){
        double sprijeda, szada;
        citac_pisac.seekg(i * sizeof(double), std::ios::beg);
        citac_pisac.read(reinterpret_cast<char*>(&sprijeda), sizeof sprijeda);
        citac_pisac2.seekg((broj_elemenata - i - 1) * sizeof(double), std::ios::beg);
        citac_pisac2.read(reinterpret_cast<char*>(&szada), sizeof szada);
        citac_pisac2.seekp((broj_elemenata - i - 1) * sizeof(double), std::ios::beg);
        citac_pisac2.write(reinterpret_cast<char*>(&sprijeda), sizeof sprijeda);
        citac_pisac.seekp(i * sizeof(double), std::ios::beg);
        citac_pisac.write(reinterpret_cast<char*>(&szada), sizeof szada);
        citac_pisac.seekg(0, std::ios::cur);
        citac_pisac2.seekg(0, std::ios::cur);

    }

    // citac_pisac.close();
    // std::ofstream tekstualna("OBRNUT_BROJEVI.TXT");
    double obrnuto[6];
    std::ifstream citac2("BROJEVI.DAT", std::ios::binary);
    citac2.read(reinterpret_cast<char*>(obrnuto), sizeof obrnuto);
    for(int i = 0; i < 6; i++) std::cout<<obrnuto[i];
    return 0;
}