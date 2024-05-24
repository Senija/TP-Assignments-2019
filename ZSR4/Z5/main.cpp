#include <iostream>
#include <string>
#include <vector>
#include <utility>
#include <new>
#include <initializer_list>
#include <algorithm>
#include <fstream>
class Stan
{
    std::string naselje;
    int broj_soba;
    double kvadratura;
    public:
    Stan(const std::string &naselje, int broj_soba, double kvadratura): naselje(naselje), broj_soba(broj_soba), kvadratura(kvadratura){

    }
    virtual ~Stan(){
    }

    Stan(const Stan &s) {
        broj_soba = s.broj_soba;
        naselje = s.naselje;
        kvadratura = s.kvadratura;
    }

    virtual Stan *DajKopiju() const{
        return new Stan(*this);
    }

    //getteri

    int DajBrojSoba() const{
        return broj_soba;
    }

    double DajKvadraturu() const{
        return kvadratura;
    }

    std::string DajNaselje() const{
        return naselje;
    }

    double operator~ (){
        return DajKvadraturu() * 1000;
    }

    void PromijeniBrojSoba(int novi_broj_soba){
        broj_soba = novi_broj_soba;
    }



};
class NamjesteniStan : public Stan
{
    std::vector<std::pair<std::string, int>> stvari;
    public:

    NamjesteniStan(const std::string &naselje, int broj_soba, double kvadratura, const std::vector<std::pair<std::string, int>> stvari) : Stan(naselje, broj_soba, kvadratura){
        NamjesteniStan::stvari = stvari;
    }

    NamjesteniStan(const NamjesteniStan &ns): Stan(ns.DajNaselje(), ns.DajBrojSoba(), ns.DajKvadraturu()){
        stvari = ns.stvari;
    }

    Stan *DajKopiju() const override{
        return new NamjesteniStan(*this);
    }

    ~NamjesteniStan(){

    }

    double operator~ (){
        return DajKvadraturu() * 1000;
    }
    
    std::vector<std::pair<std::string, int>> DajStvari() const{
        return stvari;
    }

};
class StambenaAgencija
{
    Stan **stanovi;
    int broj, kapacitet;
    public:
    explicit StambenaAgencija(int kapacitet = 50){
       
        try{
            stanovi = new Stan*[kapacitet]{};
        }
        catch(...){
            delete[] stanovi;
            throw;
        }
         StambenaAgencija::kapacitet = kapacitet;
         broj = 0;
    }

    StambenaAgencija(const StambenaAgencija &Sa){
        Stan **pomocni;
        try{
            pomocni = new Stan*[Sa.kapacitet]{};
            for(int i = 0; i < Sa.broj; i++){
                //pomocni[i];
                //auto pom =  Sa.stanovi[i]->DajKopiju();
                pomocni[i] = Sa.stanovi[i]->DajKopiju();
            }
        }
        catch(...){
            for(int i = 0; i < Sa.broj; i++) delete pomocni[i];
            delete[] pomocni;
        }

        stanovi = pomocni;
        kapacitet = Sa.kapacitet;
        broj = Sa.broj;
    }

    StambenaAgencija(StambenaAgencija &&Sa){
        kapacitet = Sa.kapacitet;
        broj = Sa.broj;
        stanovi = Sa.stanovi;
        Sa.stanovi = nullptr;

    }

    StambenaAgencija(const std::string &ime_datoteke){
        std::ifstream ulazni_tok(ime_datoteke);
        if(!ulazni_tok) throw std::logic_error ("Ne postoji datoteka");
        int broj_pom = 0;
        Stan **pomocni;
        try{
            pomocni = new Stan*[50]{};
            while(ulazni_tok){
                if(ulazni_tok.eof()) break;
                std::string naselje;
                int broj_soba;
                double kvadratura;
                std::getline(ulazni_tok, naselje);
                ulazni_tok >> std::ws >>broj_soba >>std::ws >> kvadratura >> std::ws;
                if(!ulazni_tok && !ulazni_tok.eof()) throw std::logic_error ("Problemi pri citanju datoteke");
                pomocni[broj_pom] = new Stan(naselje, broj_soba, kvadratura);
                broj_pom++;
            }
        }
        catch(...){
            //delete nebitno
        }

        stanovi = pomocni;
        broj = broj_pom;
        kapacitet = 50;

    }

    ~StambenaAgencija(){
        for(auto i = 0; i < broj; i++){
            delete stanovi[i];
            stanovi[i] = nullptr;
        }
        
        delete[] stanovi;
    }

    void DodajStan(const std::string &naselje, int broj_soba, double kvadrati) {
        try{
            stanovi[broj] = new Stan(naselje, broj_soba, kvadrati);
            broj++;
        }
        catch(...){
            delete stanovi[broj];
            stanovi[broj] = nullptr;
            throw;
        }
        
    }

    void DodajStan(const Stan &stan){
        try{
            stanovi[broj] = stan.DajKopiju();
            broj++;
        }
        catch(...){
            delete stanovi[broj];
            stanovi[broj] = nullptr;
            throw;
        }
    }

    void DodajNamjestenStan(const NamjesteniStan &NS){
        if(broj == kapacitet) throw std::range_error ("Overflow");
        stanovi[broj]= NS.DajKopiju();
        broj++;
    }

    void DodajNamjestenStan(const std::string &naselje, int broj_soba, double kvadratura, const std::vector<std::pair<std::string, int>> &stvari){
        if(broj == kapacitet) throw std::range_error ("Overflow");
        try{
            stanovi[broj] = new NamjesteniStan(naselje, broj_soba, kvadratura, stvari);
            broj++;
        }
        catch(...){
            delete stanovi[broj];
            stanovi[broj] = nullptr;
            throw;
        }
    }

    Stan &DajNajveciStan() const{
        if(broj == 0) throw std::logic_error ("Ne postoje stanovi!");
        int max = -1; 
        int index;
        for(int i = 0; i < broj; i++){
            if(stanovi[i]->DajKvadraturu() > max){
                max = stanovi[i]->DajKvadraturu();
                index = i;
            }
        }
        return *stanovi[index];
    }

    StambenaAgencija &operator +=(const StambenaAgencija &sa){
        if(broj + sa.broj > kapacitet) throw std::range_error ("Overflow");
        try{
            for(int i = 0; i < sa.broj; i++){
                stanovi[i + broj] = sa.stanovi[i]->DajKopiju();
                broj++;
            }
        }
        catch(...){
            throw;
        }

        return *this;
    }

    Stan *operator[](int index) const{
        if(index < 0 || index > broj) throw std::logic_error ("Ne postoij stan sa datim indeksom");
        return stanovi[index];
        
    }
    Stan operator[](int index) {
        if(index < 0 || index > broj) throw std::logic_error ("Ne postoij stan sa datim indeksom");
        return *stanovi[index];
        
    }
    void Prodaj(int index){
        //da li na to mjesto dolazi novi stan???????????
        try{
            if(index < 0 || index > broj) throw std::logic_error ("Ne postoij stan sa datim indeksom");
            delete stanovi[index - 1];
            stanovi[index - 1] = nullptr;
            stanovi[index - 1] = stanovi[broj - 1]->DajKopiju();
            delete stanovi[broj - 1];
            stanovi[broj - 1] = nullptr;
            broj--;
        }
        catch(...){
            throw;
            //fali dosta ili ne
        }
    }

    StambenaAgencija &operator=(const StambenaAgencija &sa){
        Stan** pomocni;
        try{
            pomocni = new Stan*[sa.kapacitet] {};
            for(int i = 0; i < sa.broj; i++){
                pomocni[i] = sa.stanovi[i]->DajKopiju();
            }
        }
        catch(...){
            for(int i = 0; i < sa.broj; i++) delete pomocni[i];
            delete[] pomocni;
        }

        for(int i = 0; i < broj; i++){
            delete stanovi[i];
            stanovi[i] = nullptr;
        }
        delete[] stanovi;

        stanovi = pomocni;
        broj = sa.broj;
        kapacitet = sa.kapacitet;
        return *this;
    }

    StambenaAgencija &operator =(StambenaAgencija &&sa){
        std::swap(stanovi, sa.stanovi);
        std::swap(kapacitet, sa.kapacitet);
        std::swap(broj, sa.broj);
    }

    double operator()(const std::string &naselje) const{
        double suma = 0;
        for(int i = 0; i < broj; i++){
            if(stanovi[i]->DajNaselje() == naselje) suma += stanovi[i]->DajKvadraturu();
        }
        return suma;
    }

    friend std::ostream &operator <<(std::ostream &tok, const StambenaAgencija &sa);
    friend StambenaAgencija operator +(const StambenaAgencija &s1, const StambenaAgencija &s2);
};

StambenaAgencija operator +(const StambenaAgencija &s1, const StambenaAgencija &s2){
    StambenaAgencija S_Huge; // ma 50 je kapacitet
    if(s2.broj + s1.broj > 50) throw std::range_error ("Overflow");
    try{
        for(int i = 0; i < s1.broj; i++){
        S_Huge.stanovi[i] = s1.stanovi[i]->DajKopiju(); 
        S_Huge.broj++;
        }
        for(int i = 0; i < s2.broj; i++){
        S_Huge.stanovi[s1.broj+i] = s2.stanovi[i]->DajKopiju();
        S_Huge.broj++;
        }
    }
    catch(...){
        for(int i = 0; i < S_Huge.broj; i++) delete S_Huge.stanovi[i];
        delete[] S_Huge.stanovi;
        throw;
    }
    return S_Huge;
}

std::ostream &operator <<(std::ostream &tok, const StambenaAgencija &sa){
    for(int i = 0; i < sa.broj; i++){
        tok<<sa.stanovi[i]->DajNaselje()<<std::endl;
        tok<<sa.stanovi[i]->DajBrojSoba()<<std::endl;
        tok<<sa.stanovi[i]->DajKvadraturu()<<std::endl;
        if(auto pok = dynamic_cast<NamjesteniStan *> (sa.stanovi[i])){
            auto stvari = pok->DajStvari();
            for(auto i = stvari.begin(); i < stvari.end(); i++){
                tok << i->first <<" "<< i->second;
            }
        }
    }

    return tok;
}
int main ()
{
    StambenaAgencija s1(10); // (1)  
    //StambenaAgencija s1 = 10; // ovo se ne smije kompajlirati 
    s1.DodajStan("Novo Sarajevo", 3, 60); // (2)  
    Stan stan("Ilidza", 4, 75.5); // (3)   
    s1.DodajStan(stan); // (4) - dodaje kopiju stana   
    StambenaAgencija s2(s1); // (5)  
    Stan &ref = s2.DajNajveciStan(); // (6)  
    std::vector<std::pair<std::string, int>> stvari {{"Televizor", 700},      {"Frizider", 450}, {"Ormar", 300}}; // {naziv, cijena}  
    NamjesteniStan nstan("Vratnik", 2, 50, stvari); // (7)   
    s2.DodajNamjestenStan(nstan); // (8)  
    Stan &sref(nstan);   
    s2.DodajNamjestenStan("Bjelave", 3, 70, {{"Jacuzzi", 4450},      {"Ves masina", 500}}); // (9)  
    std::cout << "Cijena stana: " << ~stan; // (10)    // cijena se računa kao kvadratura * 1000  
    std::cout << "Cijena namjestenog stana: " << ~sref; // (11)       // cijena se računa kao kvadratura * 2000 + vrijednost stvari    
    StambenaAgencija s3; // (12) - s3 ima kapacitet od 50 stanova   
    s3 = s1 + s2; // (13) - s3 će sadržavati sve stanove iz s1 i iz s2   
    s1 += s2; // (14) - u s1 dodaje sve stanove iz s2   
    const StambenaAgencija &cs3(s3); // referenca na const    
    const Stan *moj_stan = cs3[1]; // (15) moj_stan je pokazivač   
    s1[0].PromijeniBrojSoba(3); // (16) označava renoviranje stana   
    s3.Prodaj(2); // (17) briše 2. stan iz kolekcije    
    std::cout << "Ukupna kvadratura za naselje: " << s2("Novo Sarajevo"); // (18)     
    std::ofstream dat("stanovi.txt");  
    dat << s3; // (19)     
    StambenaAgencija s4("stanovi.txt"); // (20) učitava iz datoteke    
    std::cout << s4; // daje isti ispis kao i std::cout << s3  
    return 0;   
    }