#include <iostream>
#include <cmath>
#include <stdexcept>
#include <string>
#include <vector>
#include <memory>
class Lik
{
public:
	virtual void IspisiSpecificnosti() const = 0;
	virtual double DajObim() const = 0;
	virtual double DajPovrsinu() const = 0;
	void Ispisi() const
	{
		IspisiSpecificnosti();
		std::cout<<"Obim: "<<DajObim()<<" Povrsina: "<<DajPovrsinu()<<std::endl;
	}
	virtual ~Lik() {}

};
class Krug : public Lik
{
	double radius;
	static constexpr double PI = 4*atan(1);
public:
	Krug(double poluprecnik)
	{
		if(poluprecnik <= 0) throw std::domain_error ("Neispravni parametri");
		radius = poluprecnik;
	}
	void IspisiSpecificnosti() const override
	{
		std::cout<<"Krug poluprecnika "<<radius<<std::endl;
	}
	double DajObim() const override
	{
		return 2*radius*PI;
	}
	double DajPovrsinu() const override
	{
		return radius*radius*PI;
	}


};
class Pravougaonik: public Lik
{
	double stranica1, stranica2;
public:
	Pravougaonik(double a, double b)
	{
		if(a <= 0 || b <= 0) throw std::domain_error ("Neispravni parametri");
		stranica1 = a;
		stranica2 = b;
	}
	void IspisiSpecificnosti() const override
	{
		std::cout<<"Pravougaonik sa stranicama duzine "<<stranica1<<" i "<<stranica2<<std::endl;
	}
	double DajObim() const override
	{
		return 2 * (stranica1 + stranica2);
	}
	double DajPovrsinu() const override
	{
		return stranica1 * stranica2;
	}

};
class Trougao: public Lik
{
	double stranica1, stranica2, stranica3;
	bool VeciZbir(double prva, double druga, double treca)
	{
		return prva + druga > treca;
	}
public:
	Trougao(double a, double b, double c)
	{
		if(VeciZbir(a,b,c) && VeciZbir(a,c,b) && VeciZbir(b,c, a)) {
			stranica1 = a;
			stranica2 = b;
			stranica3 = c;
		} else throw std::domain_error ("Neispravni parametri");
	}
	void IspisiSpecificnosti() const override
	{
		std::cout<<"Trougao sa stranicama duzine "<<stranica1<<", "<<stranica2<<" i "<<stranica3<<std::endl;
	}
	double DajObim() const override
	{
		return  stranica1 + stranica2 + stranica3;
	}
	double DajPovrsinu() const override
	{
		double s = DajObim() / 2;
		return std::sqrt(s * (s - stranica1) * (s - stranica2) * (s - stranica3));
	}

};
int main ()
{
	int broj_likova;

	std::cout<<"Koliko zelite likova: ";
	std::cin>>broj_likova;
	std::cin.ignore(10000, '\n');
	std::vector<std::shared_ptr<Lik>> VektorPok;
	for(int i = 0; i < broj_likova; i++) {
		try {
			std::cout<<"Lik "<<i+1<<": ";
			char slovo, zarez;
			std::cin>>slovo;
			if(slovo != 'P' && slovo != 'T' && slovo != 'K') {
				i--;
				std::cin.clear();
				std::cin.ignore(10000, '\n');
				std::cout<<"Pogresni podaci, ponovite unos!"<<std::endl;
				continue;
				
			} else {

				if(slovo == 'K') {
					double poluprecnik;
					std::cin>>poluprecnik;
					if(!(std::cin) || std::cin.peek() != '\n') {
						i--;
						std::cin.clear();
						std::cin.ignore(10000, '\n');
						std::cout<<"Pogresni podaci, ponovite unos!"<<std::endl;
						continue;
					} else VektorPok.push_back(std::make_shared<Krug>(poluprecnik));
				} else if(slovo == 'P') {
					double a, b;
					char znak;
					std::cin>>a>>znak>>b;
					if(!(std::cin) || znak != ',' || std::cin.peek() != '\n') {
						std::cin.clear();
						std::cin.ignore(10000, '\n');
						i--;
						std::cout<<"Pogresni podaci, ponovite unos!"<<std::endl;
						continue;
					} else VektorPok.push_back(std::make_shared<Pravougaonik>(a, b));
				} else if(slovo == 'T') {
					double a, b, c;
					char znak1, znak2;
					std::cin>>a>>znak1>>b>>znak2>>c;
					if(!(std::cin) || znak1 != ',' || znak2 != ',' || std::cin.peek() != '\n') {
						i--;
						std::cin.clear();
						std::cin.ignore(10000, '\n');
						std::cout<<"Pogresni podaci, ponovite unos!"<<std::endl;
						continue;
					} else VektorPok.push_back(std::make_shared<Trougao>(a, b, c));

				}

			}

		} catch(...) {
			std::cout<<"Pogresni podaci, ponovite unos!"<<std::endl;
			i--;
			continue;
		}
	}
	std::cout<<std::endl;
	for(auto i = VektorPok.begin(); i != VektorPok.end(); i++) (*i)->Ispisi();
	return 0;
}
