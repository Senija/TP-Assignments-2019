#include <iostream>
#include <stdexcept>

class StedniRacun{
    double racun;
    
    public:
    StedniRacun (){
        racun = 0;
    }
    StedniRacun(double novac){
        if(novac < 0) throw std::logic_error ("Nedozvoljeno pocetno stanje");
        racun = novac;
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
};
int main ()
{   
    

	return 0;
}