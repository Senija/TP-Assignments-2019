#include <iostream>
#include <cmath>
#include <iomanip>

class Sat
{
	int sat, minuta, sekunda;
	
public:
	static bool DaLiJeIspravno(int sat, int minuta, int sekunda);
	void Postavi(int h, int min, int s) 
	{
		if(!DaLiJeIspravno(h, min, s)) throw std::domain_error ("Neispravno vrijeme");
		sat = h;
		minuta = min;
		sekunda = s;
	}
	void PostaviNormalizirano(int h, int min, int s)
	{
		while(s < 0) {
			s = 60 +s;
			min--;
		}
		while(min < 0) {
			min = 60 + min;
			h--;
		}
		while(h < 0) {
			h = 24 + h;
		}
		if(s > 59) {
			min += s / 60;
			s = s % 60;
		}
		if(min > 59) {
			h += min / 60;
			min = min % 60;
		}
		if(h > 23) h = h % 24;
		if(s < 0 ) {
			s = 60 + s;
		}
		sat = h;
		minuta = min;
		sekunda = s;
	}
	Sat &Sljedeci()
	{
		sekunda++;
		PostaviNormalizirano(sat, minuta, sekunda);
		return *this;
	}
	Sat &Prethodni()
	{
		sekunda--;
		PostaviNormalizirano(sat, minuta, sekunda);
		return *this;
	}
	Sat &PomjeriZa( int pomak)
	{
		if(pomak > 0)
			while(pomak) {
				Sljedeci();
				pomak --;
			}
		if(pomak < 0)	{
			pomak = std::abs(pomak);
			while(pomak != 0) {
				Prethodni();
				pomak--;
			}
		}
		return *this;
	}
	void Ispisi() const
	{
		std::cout<<std::setw(2)<<std::setfill('0')<<sat<<":"<<std::setw(2)<<std::setfill('0')<<minuta<<":"<<std::setw(2)<<std::setfill('0')<<sekunda;
	}
	int DajSate() const
	{
		return sat;
	}
	int DajMinute() const
	{
		return minuta;
	}
	int DajSekunde() const
	{
		return sekunda;
	}
	friend int BrojSekundiIzmedju(const Sat &sat1, const Sat &sat2);
	static int Razmak(const Sat &sat1, const Sat &sat2);
};
bool Sat::DaLiJeIspravno(int sat, int minuta, int sekunda)
{
	if(sat < 0 || sat > 23 || minuta < 0 || minuta > 59 || sekunda < 0 || sekunda > 59) return false;
	return true;
}
int BrojSekundiIzmedju(const Sat &sat1, const Sat &sat2)
{
	int sek_izmedju;
	sek_izmedju = sat1.sekunda - sat2.sekunda;
	sek_izmedju += (sat1.minuta - sat2.minuta) * 60;
	sek_izmedju += (sat1.sat - sat2.sat)* 3600;
	return sek_izmedju;
}
int Sat::Razmak(const Sat &sat1, const Sat &sat2)
{
	int sek_izmedju;
	sek_izmedju = sat1.sekunda - sat2.sekunda;
	sek_izmedju += (sat1.minuta - sat2.minuta) * 60;
	sek_izmedju += (sat1.sat - sat2.sat)* 3600;
	return sek_izmedju;
}
int main ()
{

	  Sat s;
  s.Postavi(10,10,10);
  s.PomjeriZa(5).Ispisi(); std::cout << std::endl;
  s.PomjeriZa(-5).Ispisi(); std::cout << std::endl;
  s.PomjeriZa(100).PomjeriZa(-100).Ispisi(); std::cout << std::endl;
  
  s.Postavi(23,59,59);
  s.PomjeriZa(5).Ispisi(); std::cout << std::endl;
  s.Postavi(10,59,59);
  s.PomjeriZa(5).Ispisi(); std::cout << std::endl;
  s.Postavi(10,10,59);
  s.PomjeriZa(5).Ispisi(); std::cout << std::endl;
  
  s.Postavi(0,0,0);
  s.PomjeriZa(-5).Ispisi(); std::cout << std::endl;
  s.Postavi(10,0,0);
  s.PomjeriZa(-5).Ispisi(); std::cout << std::endl;
  s.Postavi(10,10,0);
  s.PomjeriZa(-5).Ispisi();
	return 0;
}
