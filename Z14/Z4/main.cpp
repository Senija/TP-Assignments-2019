#include <iostream>
#include <fstream>
#include <string>
#include <stdexcept>

void IzvrniDatoteku(std::string ime_datoteke){
    std::fstream ulazni_tok(ime_datoteke, std::ios::binary | std::ios::in | std::ios::out);
    if(!ulazni_tok) throw std::logic_error("Datoteka ne postoji");
    ulazni_tok.seekg(0, std::ios::end);
    int duzina_datoteke = ulazni_tok.tellg();
    int broj_elemenata = duzina_datoteke / sizeof(double);
    std::fstream ulazni_tokNo_2(ime_datoteke, std::ios::binary | std::ios::in | std::ios::out);
    ulazni_tokNo_2.seekg(0,std::ios::beg);
    for(int i = broj_elemenata - 1; i >= (broj_elemenata) / 2; i--){
        double broj_kraj;
        double broj_poc;
        ulazni_tok.seekg(i * sizeof(double), std::ios::beg);
        ulazni_tok.read(reinterpret_cast<char*>(&broj_kraj), sizeof broj_kraj);
        ulazni_tokNo_2.seekg(duzina_datoteke - (i + 1) * sizeof(double));
        ulazni_tokNo_2.read(reinterpret_cast<char*>(&broj_poc), sizeof broj_poc);
        ulazni_tok.seekp(i * sizeof(double), std::ios::beg);
        ulazni_tok.write(reinterpret_cast<char*>(&broj_poc), sizeof broj_poc);
        ulazni_tokNo_2.seekp(duzina_datoteke - (i + 1) * sizeof(double));
        ulazni_tokNo_2.write(reinterpret_cast<char*>(&broj_kraj), sizeof broj_kraj);
        ulazni_tok.seekg(0, std::ios::cur);
        ulazni_tokNo_2.seekg(0, std::ios::cur);
        // std::cout<<broj_kraj<<std::endl;
        // std::cout<<broj_poc<<std::endl;
    }
    if(!ulazni_tok && !ulazni_tok.eof()) throw std::logic_error("Problemi pri citanju datoteke");
    
}

int main ()
{
    double niz[] = {-1, -2, -3, -4, -5, -5.5, -76, 1, 2, 3, 0, 100};
	double novi[12]{};
	std::ofstream f ("dat.bin", std::ios::binary);
	f.write((char *)niz, sizeof niz);
	f.close();
	IzvrniDatoteku("dat.bin");
	std::ifstream ff ("dat.bin", std::ios::binary);
	ff.read((char *)novi, sizeof novi);
	for (int i = 0; i < 12; ++i) std::cout << novi[i] << ", ";
	ff.close();
      
	return 0;
}