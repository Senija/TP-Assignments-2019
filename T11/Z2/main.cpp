#include <iostream>
#include <stdexcept>

class StedniRacun{
    double racun;
    static int br_aktivnih; 
    static int br_kreiranih;
    public:
    StedniRacun (){
        racun = 0;
        br_kreiranih++;
        br_aktivnih++;
    }
    StedniRacun(double novac){
        if(novac < 0) throw std::logic_error ("Nedozvoljeno pocetno stanje");
        racun = novac;
        br_aktivnih++;
        br_kreiranih++;
    }
    StedniRacun( const StedniRacun &sr){
        racun = sr.racun;
        br_aktivnih++;
        br_kreiranih++;
    }
    ~StedniRacun(){
        br_aktivnih--;
    }
    
    StedniRacun &Ulozi(double novac){
        if(novac + racun < 0) throw std::logic_error ("Transakcija odbijena");
        racun += novac;
        return *this;
    }
    StedniRacun &Podigni(double novac){
        if(novac > racun) throw std::logic_error ("Transakcija odbijena");
        racun = racun - novac;
        return *this;
    }
    double DajStanje() const{
        return racun;
    }
    StedniRacun &ObracunajKamatu(double kamatna_stopa){
        if(kamatna_stopa < 0) throw std::logic_error ("Nedozvoljena kamatna stopa");
        racun += racun * (kamatna_stopa/100);
        return *this;
    }
    static int DajBrojKreiranih() {
        return br_kreiranih;
    }
    static int DajBrojAktivnih() {
        return br_aktivnih;
    }
    
};

int StedniRacun::br_aktivnih = 0;
int StedniRacun::br_kreiranih = 0;
int main ()
{   
    StedniRacun s1, s2(100);
    { StedniRacun s3(50); }// Nakon } s3 više ne postoji...
    std::cout << StedniRacun::DajBrojKreiranih()<< " " << StedniRacun::DajBrojAktivnih();
	return 0;
}