#include <iostream>
#include <stdexcept>
#include <cmath>
#include <iomanip>

class Ugao
{

  double radijan;
  static double PI;
  // void PretvoriUStepene(double radijani){
  //   stepen = radijani * 180/PI;
  //   minuta = ((radijani * 180/PI) - stepen ) * 60;
  //   sekunda = (((radijani * 180/PI) - stepen ) * 60 - minuta) * 60;
  // }
  
  void PretvoriURadijane(int stepeni, int minute, int sekunde){
    radijan = (stepeni + minute/60. + sekunde/3600.) * (PI/ 180);
  }
  
  int SekundaZaokruzeno(double sekunde) const{
    constexpr double Eps = 1e-10;
    return int(sekunde + Eps * sekunde);
  }
  
public:
  Ugao (double radijani = 0)
  {
    Postavi(radijani);
  }
  Ugao (int stepeni, int minute, int sekunde)
  {
    Postavi(stepeni, minute, sekunde);
  }
  void Postavi (double radijani)
  {
    while(radijani < 0){
      radijani = 2*PI + (radijani - (int(radijani/(2 * PI)) * 2 * PI));
    }
    while(radijani >= 2 * PI){
      radijani = radijani - int(radijani / (2 * PI)) * 2 * PI;
    }
    radijan = radijani;
    
  }
  void Postavi(int stepeni, int minute, int sekunde)
  {
      while(sekunde < 0 ) {
      sekunde = 60 + sekunde;
      minute --;
    }
    while(minute < 0){
      minute = 60 + minute;
      stepeni --;
    }
    while(stepeni < 0){
      stepeni = 360 + stepeni;
    }
    if(sekunde > 59){
      minute += sekunde/60;
      sekunde = sekunde % 60;
     
    }
    if(minute > 59){
      stepeni += minute/60;
      minute = minute % 60;
    }
    if(stepeni >= 360){
      stepeni = stepeni % 360;
    }
    
    // stepen = stepeni;
    // minuta = minute;
    // sekunda = sekunde;
    PretvoriURadijane(stepeni, minute, sekunde);
  }
  
  double DajRadijane() const
  {
    return radijan;
  }
  
  void OcitajKlasicneJedinice(int &stepeni, int &minute, int &sekunde){
    stepeni = radijan * 180/PI;
    minute = ((radijan * 180/PI) - stepeni ) * 60;
    sekunde = (((radijan * 180/PI) - stepeni ) * 60 - minute) * 60;
  }
  
  int DajStepene() const
  {
    //if(radijan * 180/PI == 360) return 0;
   // if(radijan >= 2 * PI) radijan = 
    return radijan * 180/PI;
  }
  int DajMinute() const
  {
    auto pom =  (radijan * 180/PI);
    pom -= int(pom);
    return SekundaZaokruzeno(pom*60);
  }
  int DajSekunde() const
  {
    auto pom = radijan * 180/PI;
    pom -= int(pom) + DajMinute()/60.;
    return SekundaZaokruzeno(pom * 3600);
  }
  void Ispisi() const
  {
    std::cout<<std::fixed<<std::setprecision(5)<<radijan;
  }
  void IspisiKlasicno() const
  {
    std::cout<<DajStepene()<<"deg "<<DajMinute()<<"min "<<DajSekunde()<<"sec";
  }

  Ugao &SaberiSa(const Ugao &u)
  {
    radijan += u.radijan;
    Postavi(radijan);
    return *this;
  }

  Ugao &PomnoziSa(double parametar)
  {
    radijan *= parametar;
    Postavi(radijan);
    return *this;
  }
  
  friend Ugao ZbirUglova(const Ugao &u1, const Ugao &u2);
  friend Ugao ProduktUglaSaBrojem(const Ugao &u, double x);
};

Ugao ZbirUglova(const Ugao &u1, const Ugao &u2){
  
  Ugao sabran;
  sabran.Postavi(u1.radijan + u2.radijan);
  return sabran;
}

Ugao ProduktUglaSaBrojem(const Ugao &u, double x){
  return x * u.radijan;
}

 double Ugao :: PI = 4 * atan(1);

int main ()
{
    Ugao u1(50, 25, 12), u2(5*4 * atan(1)/4);
u1.PomnoziSa(4);
u1.IspisiKlasicno(); std::cout << std::endl;
u2.Ispisi();
std::cout << std::endl;
u2.IspisiKlasicno();
std::cout << std::endl;
auto zbir = ZbirUglova(u1, u1);
zbir.Ispisi();
std::cout << std::endl;
zbir.IspisiKlasicno();
std::cout << std::endl;
  return 0;
}
