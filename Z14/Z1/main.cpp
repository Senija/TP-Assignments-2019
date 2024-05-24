#include <iostream>
#include <fstream>
#include <string>
#include <iomanip>
#include <algorithm>
#include <vector>

class Datum
{
    int dan;
    int mjesec;
    int godina;
public:
    Datum(int dan, int mjesec,int godina): dan(dan), mjesec(mjesec), godina(godina) {}
    bool operator ==(const Datum &d)
    {
        if(dan == d.dan && mjesec == d.mjesec && godina == d.godina) return true;
        return false;
    }
    bool operator < (const Datum &d){
        if(godina < d.godina) return true;
        if(godina > d.godina) return false;
        if(godina == d.godina && mjesec < d.mjesec) return true;
        if(godina == d.godina && mjesec > d.mjesec) return false;
        if(godina == d.godina && mjesec == d.mjesec && dan < d.dan) return true;
        else return false;
    }
    int DajGodinu() const
    {
        return godina;
    }
    int DajMjesec() const
    {
        return mjesec;
    }
    int DajDan() const
    {
        return dan;
    }
    void PostaviDatum(int dan, int mjesec, int godina){
        Datum::dan = dan;
        Datum::mjesec = mjesec;
        Datum::godina = godina;
    }

};

// Datum PretvoriUDatum(const std::string &datum)
// {
//     std::string dan,mjesec,godina;
//     int brojac_slasha = 0;
//     for(auto i = datum.begin(); i != datum.end(); i++) {
//         if(brojac_slasha == 0) {
//             if(*i >= '0' && *i<='9')
//                 dan.push_back(*i);
//             else brojac_slasha++;
//         } else if(brojac_slasha == 1) {
//             if(*i >= '0' && *i<='9')
//                 mjesec.push_back(*i);
//             else brojac_slasha++;
//         } else {
//             godina.push_back(*i);
//         }
//     }
//     int datumI = std::stoi(dan);
//     int mjesecI = std::stoi(mjesec);
//     int godinaI = std::stoi(godina);
//     return Datum(datumI, mjesecI, godinaI);
// }

class Meteoroloska_stanica
{
    std::string opis;
    Datum datum;
    std::vector<double> temperatura;
    double prosjecna_temp;
public:
    Meteoroloska_stanica(std::string opis, int dan, int mjesec, int godina, std::vector<double> temperatura, double prosjecna_temp) : opis(opis), temperatura(temperatura), prosjecna_temp(prosjecna_temp), datum(dan, mjesec, godina)
    {
    }
    // bool operator < (const Meteoroloska_stanica &m) const
    // {
    //     auto classDatum = PretvoriUDatum(datum);
    //     auto d = PretvoriUDatum(m.DajDatum());
    //     if( classDatum.DajGodinu() < d.DajGodinu()) return true;
    //     else return false;
    //     if(classDatum.DajGodinu() == d.DajGodinu() && classDatum.DajMjesec() < d.DajMjesec()) return true;
    //     else if(classDatum.DajGodinu() == d.DajGodinu() && classDatum.DajMjesec() > d.DajMjesec()) return false;
    //     else if(classDatum.DajGodinu() == d.DajGodinu() && classDatum.DajMjesec() == d.DajMjesec() && classDatum.DajDan() < d.DajDan()) return true;
    //     else return false;
    // }
    double DajProsjecnuTemperaturu() const
    {
        return prosjecna_temp;
    }
    Datum DajDatum() const
    {
        return datum;
    }
    std::string DajOpis() const
    {
        return opis;
    }
    std::vector<double> DajTemperature() const
    {
        return temperatura;
    }


};

int main(){
    std::ifstream ulazni_tok("TEMPERATURE.TXT");
    std::vector<Meteoroloska_stanica> Meteoroloske_stanice;
    if(!ulazni_tok) std::cout<<"Datoteka TEMPERATURE.TXT ne postoji!"<<std::endl;
    else {
        while(ulazni_tok) {
            int dan, mjesec, godina;
            std::string opis;
            char znak;
            std::vector<double> temperature;
            ulazni_tok>>dan>>znak>>mjesec>>znak>>godina;
            std::getline(ulazni_tok,opis);
            
            std::getline(ulazni_tok,opis);
            double suma = 0;
            double temp_temp;
            //ulazni_tok>>std::ws;
            auto nes = ulazni_tok.peek();
            while(ulazni_tok>>temp_temp && ulazni_tok.peek() == ',') {
                ulazni_tok>>znak;
                suma += temp_temp;
                temperature.push_back(temp_temp);
            }
            temperature.push_back(temp_temp);
            suma+=temp_temp;
            Meteoroloske_stanice.push_back(Meteoroloska_stanica(opis, dan, mjesec, godina, temperature, suma/temperature.size()));
            ulazni_tok.ignore(10000,'\n');
            if(ulazni_tok.eof()) break;
        }
        if(ulazni_tok.bad()) std::cout<<"Problemi pri citanju datoteke TEMPERATURE.TXT"<<std::endl;
        
        if(!ulazni_tok.eof() && !ulazni_tok){
            ulazni_tok.clear();
            std::cout<<"Problemi pri citanju datoteke TEMPERATURE.TXT"<<std::endl;
        }

        if(ulazni_tok.eof()) {
            std::sort(Meteoroloske_stanice.begin(), Meteoroloske_stanice.end(), [](Meteoroloska_stanica mjesto1, Meteoroloska_stanica mjesto2) {
                auto datum1 = mjesto1.DajDatum();
                auto datum2 = mjesto2.DajDatum();
                if(datum1 == datum2) {
                    return mjesto1.DajProsjecnuTemperaturu() < mjesto2.DajProsjecnuTemperaturu();
                }
                return datum1 < datum2;
            });
            // sada upis uizvjestaj
            std::ofstream izlazni_tok("IZVJESTAJ.TXT");//ocisti datoteku prije otvaranja
            for(auto i = Meteoroloske_stanice.begin(); i != Meteoroloske_stanice.end(); i++) {
                if(i->DajOpis() == "") continue;
                izlazni_tok<<i->DajOpis()<<std::endl;
                auto pom = i->DajOpis();
                izlazni_tok<<std::setfill('-')<<std::setw(pom.size() + 1);
                izlazni_tok<<"\n";
                auto dat = i->DajDatum();
                izlazni_tok << "Datum mjerenja: " <<dat.DajDan()<<"/"<<dat.DajMjesec()<<"/"<<dat.DajGodinu()<<std::endl;
                auto tempici = i->DajTemperature();
                izlazni_tok << "Minimalna temperatura: "<<std::fixed<<std::setprecision(0)<<*std::min_element(tempici.begin(), tempici.end())<<std::endl;
                izlazni_tok << "Maksimalna temperatura: "<<std::fixed<<std::setprecision(0)<<*std::max_element(tempici.begin(), tempici.end())<<std::endl;
                izlazni_tok << "Prosjecna temperatura: "<<std::fixed<<std::setprecision(2)<<i->DajProsjecnuTemperaturu()<<std::endl;
                izlazni_tok << "\n";
            }
            
        }
    }
    return 0;
}