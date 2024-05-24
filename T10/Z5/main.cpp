#include <iostream>
#include <stdexcept>
#include <cmath>
#include <iomanip>

class Ugao
{

  int stepen, minuta, sekunda;
  static double PI;
  void PretvoriUStepene(double radijani) {
    stepen = radijani * 180/PI;
    minuta = ((radijani * 180/PI) - stepen ) * 60;
    sekunda = (((radijani * 180/PI) - stepen ) * 60 - minuta) * 60;
  }
  
  double PretvoriURadijane(int stepeni, int minute, int sekunde) const{
    return (stepeni + minute/60. + sekunde/3600.) * (PI/ 180);
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
    PretvoriUStepene(radijani);
    // while(radijani < 0){
    //   radijani = 2*PI + (radijani - (int(radijani/(2 * PI)) * 2 * PI));
    // }
    // while(radijani > 2 * PI){
    //   radijani = radijani - int(radijani / (2 * PI)) * 2 * PI;
    // }
    // radijan = radijani;
    // PretvoriUStepene(radijan);
    Postavi(stepen, minuta, sekunda);
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
    if(stepeni > 359){
      stepeni = stepeni % 360;
    }
    
    stepen = stepeni;
    minuta = minute;
    sekunda = sekunde;
  }
  double DajRadijane() const
  {
    return PretvoriURadijane(stepen, minuta, sekunda);
  }
  int DajStepene() const
  {
    return stepen;
  }
  int DajMinute() const
  {
    return minuta;
  }
  int DajSekunde() const
  {
    return sekunda;
  }
  void Ispisi() const
  {
    std::cout<<std::fixed<<std::setprecision(5)<<DajRadijane();
  }
  void IspisiKlasicno() const
  {
    std::cout<<stepen<<"deg "<<minuta<<"min "<<sekunda<<"sec";
  }

  Ugao &SaberiSa( Ugao u)
  {
    stepen += u.stepen;
    minuta += u.minuta;
    sekunda += u.sekunda;
    Postavi(stepen, minuta, sekunda);
    return *this;
  }

  Ugao &PomnoziSa(double parametar)
  {
    auto ukupno_radijani = DajRadijane() * parametar;
    Postavi(ukupno_radijani);
    return *this;

  }
  
  friend Ugao ZbirUglova(const Ugao &u1, const Ugao &u2);
  friend Ugao ProduktUglaSaBrojem(const Ugao &u, double x);
};
Ugao ZbirUglova(const Ugao &u1, const Ugao &u2){
  
  Ugao sabran;
  sabran.Postavi(u1.stepen + u2.stepen, u1.minuta + u2.minuta, u1.sekunda + u2.sekunda);
  return sabran;
}

Ugao ProduktUglaSaBrojem(const Ugao &u, double x){
  Ugao pomnozen;
  auto ukupno_radijani = u.DajRadijane() * x;
  pomnozen.Postavi(ukupno_radijani);
  return pomnozen;
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
