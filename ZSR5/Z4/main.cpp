#include <iostream>
#include <fstream>

int main(){
    std::ofstream izlazni_tok("BROJEVI.DAT", std::ios::binary);
    std::ofstream tekstualna("POZITIVNI.TXT");
    double niz[10] = {1,-1, -10, 10, 0, 3.3, -4.4, 8, -8, 7};
    izlazni_tok.write(reinterpret_cast<char*>(niz), sizeof niz);
    izlazni_tok.close();
    std::fstream ulazno_izlazni_tok("BROJEVI.DAT", std::ios::binary | std::ios::in | std::ios::out);
    ulazno_izlazni_tok.seekg(0, std::ios::end);
    auto duzina_datoteke = ulazno_izlazni_tok.tellg();
    auto broj_elemenata = duzina_datoteke/sizeof(double);
    for(int i = 0; i < broj_elemenata; i++){
        ulazno_izlazni_tok.seekg(i, std::ios::beg);
        double element;
        ulazno_izlazni_tok.read(reinterpret_cast<char*>(&element), sizeof element);
        if(element < 0){
            double nula = 0;
            ulazno_izlazni_tok.write(reinterpret_cast<char*>(&nula), sizeof nula);
            ulazno_izlazni_tok.seekg(0, std::ios::cur);
        }
        else if(element > 0){
            tekstualna << element <<" ";
        }
    }
    tekstualna.close();
    ulazno_izlazni_tok.close();
    return 0;
}