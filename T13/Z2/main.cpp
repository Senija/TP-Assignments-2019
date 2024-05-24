#include <iostream>
#include <string>
#include <stdexcept>
#include <new>
class ApstraktniStudent{
	std::string ime, prezime;
	int index, polozeni_ispiti;
	double prosjecna_ocjena;
	public:
	ApstraktniStudent(std::string ime, std::string prezime, int index): ime(ime), prezime(prezime), index(index){
		polozeni_ispiti = 0;
		prosjecna_ocjena = 5;
	}
	virtual ~ApstraktniStudent(){}
	std::string DajIme() const{
		return ime;
	}
	std::string DajPrezime() const{
		return prezime;
	}
	int DajBrojPolozenih() const{
		return polozeni_ispiti;
	}
	double DajProsjek() const{
		return prosjecna_ocjena;
	}
	int DajBrojIndeksa() const{
		return index;
	}
	
	void RegistrirajIspit(int ocjena){
		if(ocjena < 5 || ocjena > 10) throw std::domain_error ("Neispravna ocjena");
		if (ocjena == 5) return;
		prosjecna_ocjena = ((prosjecna_ocjena * polozeni_ispiti) + ocjena)/(polozeni_ispiti + 1); 
		polozeni_ispiti++;
	}
	void PonistiOcjene(){
		polozeni_ispiti = 0;
		prosjecna_ocjena = 5;
	}
	virtual void IspisiPodatke() const = 0;
	virtual ApstraktniStudent *DajKopiju() const = 0;
	
	
};

class StudentBachelor: public ApstraktniStudent{
	public:
	StudentBachelor(std::string ime, std::string prezime, int index): ApstraktniStudent(ime, prezime, index){}
	ApstraktniStudent *DajKopiju() const override{
		return new StudentBachelor(*this);
	}
	void IspisiPodatke() const override{
		std::cout<<"Student bachelor studija "<<DajIme()<<" "<<DajPrezime()<<", sa brojem indeksa "<<DajBrojIndeksa()<<","<<std::endl<<"ima prosjek "<<DajProsjek()<<"."<<std::endl;
	}
};

class StudentMaster: public ApstraktniStudent{
	int god_diplomiranja;
	public:
	StudentMaster(std::string ime, std::string prezime, int index, int god): ApstraktniStudent(ime, prezime, index){
		god_diplomiranja = god;
	}
	ApstraktniStudent *DajKopiju() const override{
		return new StudentMaster(*this);
	}
	void IspisiPodatke() const override{
		std::cout<<"Student master studija "<<DajIme()<<" "<<DajPrezime()<<", sa brojem indeksa "<<DajBrojIndeksa()<<","<<std::endl<<"zavrsio bachelor studij godine "<<god_diplomiranja<<",ima prosjek "<<DajProsjek()<<"."<<std::endl;
	}
};
int main ()
{
	return 0;
}