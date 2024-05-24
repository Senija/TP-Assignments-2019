#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

enum Pol {Musko, Zensko};
class GradjaninBiH{
    std::string ImePrezime;
    std::string jmbg;
    GradjaninBiH *prethodni = nullptr;
    static GradjaninBiH *Zadnji;
    bool JeLiPravilanDatum(int dan, int mjesec, int godina){
        if(mjesec <1 || mjesec > 12 || godina <= 0 || godina > 2020) return false;
        if((mjesec == 1 || mjesec == 3 || mjesec == 5 || mjesec == 7 || mjesec == 8 || mjesec == 10 || mjesec == 12) && (dan< 0 && dan > 31)) return false;
        if((mjesec == 4 || mjesec == 6 || mjesec == 9 || mjesec == 11) &&  (dan< 0 && dan > 30)) return false;
        if(mjesec == 2 && godina % 4 == 0 && godina % 100 != 0 && godina % 400 == 0 && dan< 0 && dan > 29) return false;
        if(mjesec == 2 && (godina % 4 != 0 || (godina % 100 == 0 && godina % 400 != 0 )) && dan< 0 && dan > 28) return false;
        return true;
    }

    bool PostojiLiVec(const std::string &JMBG){
        for(auto i = Zadnji; i != nullptr; i = i->prethodni){
            if(i != this && i->jmbg == JMBG) return true;
        }
        return false;
    }

    bool PodudarniDatumRegija(const std::string &JMBG){
        for(auto i = Zadnji; i != nullptr; i = i->prethodni){
            if((i->jmbg).substr(0, 9) == JMBG) return true;
        }
        return false;
    }

    void NapraviJMBG(std::string &JMBG, Pol pol){
        std::vector<int> podudarni;
        for(auto i = Zadnji; i != nullptr; i = i->prethodni){
            if((i->jmbg).substr(0, 9) == JMBG){
                    podudarni.push_back(stoi((i->jmbg).substr(9, 3)));
            }
        }
        if (pol == Musko){
            std::vector<int> podudarni_male;
            for(int i = 0; i < podudarni.size(); i++){
                if(podudarni[i] < 500) podudarni_male.push_back(podudarni[i]);
            }
            if(podudarni_male.size() == 0) JMBG += "001";
            else{ auto maks = *std::max_element(podudarni_male.begin(), podudarni_male.end());
            JMBG +=std::to_string(maks + 1);}
        }
        if (pol == Zensko){
            std::vector<int> podudarni_female;
            for(int i = 0; i < podudarni.size(); i++){
                if(podudarni[i] >= 500) podudarni_female.push_back(podudarni[i]);
            }
            if(podudarni_female.size() == 0) JMBG += "001";
            else {auto max = *std::max_element(podudarni_female.begin(), podudarni_female.end());
            JMBG +=std::to_string(max + 1);}
        }
    }
    public:
        GradjaninBiH(std::string ime_i_prezime, long long int jmbg){
            std::string JMBG = std::to_string(jmbg);
            if(JMBG.length() > 13) throw std::logic_error ("JMBG nije validan");
            if(JMBG.length() == 12) JMBG.insert(JMBG.begin(), 0);
            auto c13 = 11- (7 *(JMBG[0] - '0' + JMBG[6] - '0') + 6 * (JMBG[1] + JMBG[7] - 2 * '0') + 5 *(JMBG[2] + JMBG[8] - 2 * '0') + 4 * (JMBG[3] + JMBG[9] - 2 * '0') + 3 * (JMBG[4] + JMBG[10] - 2 * '0') + 2 * (JMBG[5] + JMBG[11] - 2 * '0')) % 11;
            if(c13 != JMBG[12] - '0' || (c13 == 11 &&  JMBG[12] != '0') || c13 == 10) throw std::logic_error ("JMBG nije validan");
            auto godina =  std::stoi(JMBG.substr(4, 3));
            if(godina > 17) godina = godina + 1000;
            else godina += godina + 2000;
            if(!JeLiPravilanDatum(std::stoi(JMBG.substr(0, 2)), std::stoi(JMBG.substr(2, 2)), godina)) throw std::logic_error ("JMBG nije validan");
            if(PostojiLiVec(JMBG)) throw std::logic_error ("Vec postoji gradjanin sa istim JMBG");
            ImePrezime = ime_i_prezime;
            GradjaninBiH::jmbg = jmbg;
            if(Zadnji == nullptr){
                prethodni = nullptr;
                Zadnji = this;
            }
            else{
                prethodni = Zadnji;
                Zadnji = this;
            }
        }
        GradjaninBiH(std::string ime_i_prezime, int dan_rodjenja, int mjesec_rodjenja, int godina_rodjenja, int sifra_regije, Pol pol){
            if(!JeLiPravilanDatum(dan_rodjenja, mjesec_rodjenja, godina_rodjenja)) throw std::logic_error ("Neispravni podaci");
            if(sifra_regije < 0 || sifra_regije > 99)  throw std::logic_error ("Neispravni podaci");
            std::string JMBG;
            if(dan_rodjenja <= 9) JMBG = "0";
            JMBG += std::to_string(dan_rodjenja);
            if(mjesec_rodjenja < 10){
                JMBG +="0";
                JMBG += std::to_string(mjesec_rodjenja);
            } 
            else JMBG += std::to_string(mjesec_rodjenja);
            JMBG += std::to_string(godina_rodjenja).substr(1, 3);
            JMBG += std::to_string(sifra_regije);
            if(PodudarniDatumRegija(JMBG)){
                NapraviJMBG(JMBG, pol);
            }
            else JMBG += "000";
            auto c13 = 11- (7 *(JMBG[0] - '0' + JMBG[6] - '0') + 6 * (JMBG[1] + JMBG[7] - 2 * '0') + 5 *(JMBG[2] + JMBG[8] - 2 * '0') + 4 * (JMBG[3] + JMBG[9] - 2 * '0') + 3 * (JMBG[4] + JMBG[10] - 2 * '0') + 2 * (JMBG[5] + JMBG[11] - 2 * '0')) % 11;
            JMBG += std::to_string(c13);
            jmbg = JMBG;
            ImePrezime = ime_i_prezime;
        }
        GradjaninBiH &operator = (const GradjaninBiH &GB) = delete;
        GradjaninBiH (const GradjaninBiH &GB) = delete;
        ~GradjaninBiH(){
            auto pomocna = this->prethodni;
            GradjaninBiH *sljedeci;
            if(Zadnji == this) {
                prethodni = nullptr;
                Zadnji = pomocna;

            } else {
                for(auto i = Zadnji; i != nullptr; i = i->prethodni) {
                    if(this == i->prethodni) {
                        sljedeci = i;
                        break;
                    }
                }
                prethodni = nullptr;
                sljedeci->prethodni = pomocna;

            }
        }
        std::string DajImeIPrezime() const{
            return ImePrezime;
        }
        long long int DajJMBG() const{
            return std::stoll(jmbg);
        }
        int DajDanRodjenja() const{
            return std::stoi(jmbg.substr(0,2));
        }
        int DajMjesecRodjenja() const{
            return std::stoi(jmbg.substr(2,2));
        }
        int DajGodinuRodjenja() const{
            auto god = std::stoi(jmbg.substr(4,3));
            if(god > 17) return 1000 + god; //  2017. godina je max
            else return 2000 + god;
        }
        int DajSifruRegije() const{
            return std::stoi(jmbg.substr(7,2));
        }
        Pol DajPol() const{
            auto pol = std::stoi(jmbg.substr(9,3));
            if(pol <= 499) return Musko;
            else return Zensko;
        }
        void PromijeniImeIPrezime(std::string novo_ime){
            ImePrezime = novo_ime;
        }
};
GradjaninBiH* GradjaninBiH::Zadnji = nullptr;
int main(){
    //PRVI KONSTRUKTOR + METODE
    // long long int jmbg=608000175046;
    // GradjaninBiH g("Leka Elma", jmbg);
    // // GradjaninBiH g1("Ne treba raditi", jmbg);
    // std::cout << g.DajJMBG() << " " << g.DajImeIPrezime() << " " << g.DajPol() << " " << g.DajSifruRegije() << " " << g.DajSifru() << std::endl;
    // std::cout << g.DajDanRodjenja() << " " << g.DajMjesecRodjenja() << " " << g.DajGodinuRodjenja() << std::endl;
    // g.PromijeniImeIPrezime("Novo Ime");
    // std::cout << g.DajImeIPrezime() << std::endl;
    //DRUGI KONSTRUKTOR
    GradjaninBiH g4("Leka ELma", 6, 8, 2000, 17, Zensko);
    std::cout << g4.DajJMBG() 
    << " " << g4.DajImeIPrezime() 
    << " " << g4.DajPol() << " " 
    << g4.DajSifruRegije() << " " <<std::endl;
    std::cout << g4.DajDanRodjenja() << " " << g4.DajMjesecRodjenja() << " " << g4.DajGodinuRodjenja() << std::endl;
    //UVEZIVANJE
    long long int jmbg = 2309000175054;
    GradjaninBiH g("Leka Elma", jmbg);
     GradjaninBiH g1("Ne treba raditi", jmbg);
    std::cout << g.DajJMBG() << " " << g.DajImeIPrezime() << " " << g.DajPol() << " " << g.DajSifruRegije() << " " << std::endl;
    std::cout << g.DajDanRodjenja() << " " << g.DajMjesecRodjenja() << " " << g.DajGodinuRodjenja() << std::endl;
    // g.PromijeniImeIPrezime("Novo Ime");
    // std::cout << g.DajImeIPrezime() << std::endl;
    // GradjaninBiH g6("Leka ELma", 6, 8, 2000, 17, Zensko);
    // std::cout << g6.DajJMBG() << " " << g6.DajImeIPrezime() << " " << g6.DajPol() << " " << g6.DajSifruRegije() << " "  << std::endl;
    // std::cout << g6.DajDanRodjenja() << " " << g1.DajMjesecRodjenja() << " " << g6.DajGodinuRodjenja() << std::endl;
    return 0;
}
