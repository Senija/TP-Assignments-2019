#include <iostream>
#include <string>
#include <stdexcept>
#include <new>
#include <vector>
#include <algorithm>

class ApstraktniStudent
{
	std::string ime, prezime;
	int index, polozeni_ispiti;
	double prosjecna_ocjena;
public:
	ApstraktniStudent(std::string ime, std::string prezime, int index): ime(ime), prezime(prezime), index(index)
	{
		polozeni_ispiti = 0;
		prosjecna_ocjena = 5;
	}
	virtual ~ApstraktniStudent() {}
	std::string DajIme() const
	{
		return ime;
	}
	std::string DajPrezime() const
	{
		return prezime;
	}
	int DajBrojPolozenih() const
	{
		return polozeni_ispiti;
	}
	double DajProsjek() const
	{
		return prosjecna_ocjena;
	}
	int DajBrojIndeksa() const
	{
		return index;
	}

	void RegistrirajIspit(int ocjena)
	{
		if(ocjena < 5 || ocjena > 10) throw std::domain_error ("Neispravna ocjena");
		if (ocjena == 5) return;
		prosjecna_ocjena = ((prosjecna_ocjena * polozeni_ispiti) + ocjena)/(polozeni_ispiti + 1);
		polozeni_ispiti++;
	}
	void PonistiOcjene()
	{
		polozeni_ispiti = 0;
		prosjecna_ocjena = 5;
	}
	virtual void IspisiPodatke() const = 0;
	virtual ApstraktniStudent *DajKopiju() const = 0;
	friend class Fakultet;

};

class StudentBachelor: public ApstraktniStudent
{
public:
	StudentBachelor(std::string ime, std::string prezime, int index): ApstraktniStudent(ime, prezime, index) {}
	ApstraktniStudent *DajKopiju() const override
	{
		return new StudentBachelor(*this);
	}
	void IspisiPodatke() const override
	{
		std::cout<<"Student bachelor studija "<<DajIme()<<" "<<DajPrezime()<<", sa brojem indeksa "<<DajBrojIndeksa()<<","<<std::endl<<"ima prosjek "<<DajProsjek()<<"."<<std::endl;
	}
};

class StudentMaster: public ApstraktniStudent
{
	int god_diplomiranja;
public:

	StudentMaster(std::string ime, std::string prezime, int index, int god): ApstraktniStudent(ime, prezime, index)
	{
		god_diplomiranja = god;
	}
	ApstraktniStudent *DajKopiju() const override
	{
		return new StudentMaster(*this);
	}
	void IspisiPodatke() const override
	{
		std::cout<<"Student master studija "<<DajIme()<<" "<<DajPrezime()<<", sa brojem indeksa "<<DajBrojIndeksa()<<","<<std::endl<<"zavrsio bachelor studij godine "<<god_diplomiranja<<",ima prosjek "<<DajProsjek()<<"."<<std::endl;
	}
};

class Fakultet
{
	std::vector<ApstraktniStudent *> VektorPok;
	bool PostojiLiIndeks(int index) const
	{
		for(auto i = VektorPok.begin(); i != VektorPok.end(); i++) {
			if((*i)->DajBrojIndeksa() == index) return true;
		}
		return false;
	}
public:
	Fakultet() = default;
	~Fakultet()
	{
		for(auto i = 0; i != VektorPok.size(); i++) {
			delete VektorPok[i];
		}
	}
	Fakultet(const Fakultet &f)
	{
		try {
			//VektorPok(f.VektorPok.size(),nullptr);
			for(auto i = f.VektorPok.begin(); i != f.VektorPok.end(); i++)
				VektorPok.push_back((*i)->DajKopiju());
		} catch(...) {
			for(auto i = 0; i != VektorPok.size(); i++) {
				delete VektorPok[i];
				VektorPok[i] = nullptr;
			}
		}

	}
	Fakultet(Fakultet &&f) : VektorPok(std::move(f.VektorPok))
	{
		for(int i = 0; i != f.VektorPok.size(); i++) {
			f.VektorPok[i] = nullptr;
		}
		f.VektorPok.resize(0);

	}
	// Fakultet &operator = (const Fakultet &f){
	// 	std::vector<ApstraktniStudent *> pomocni;
	// 	try{
	// 		for(auto i = 0; i != f.VektorPok.size(); i++){
	// 			pomocni.push_back(f.VektorPok[i]->DajKopiju());
	// 		}
	// 		for(auto i = 0; i != VektorPok.size(); i++){
	// 			delete VektorPok[i];
	// 			VektorPok[i] = nullptr;
	// 		}
	// 		VektorPok.resize(pomocni.size());
	// 		VektorPok = pomocni;
	// 		pomocni.resize(0);
	// 	}
	// 	catch(...){
	// 		for(auto i = 0; i != pomocni.size(); i++){
	// 			delete pomocni.at(i);
	// 			pomocni.at(i) = nullptr;
	// 		}
	// 	}
	// 	return *this;
	// }
	// Fakultet &operator = (Fakultet &&f)
	// {
	// 	std::swap(f.VektorPok, VektorPok);
	// 	f.VektorPok.resize(0);
	// 	return *this;
	// }
	Fakultet &operator = (Fakultet f)
	{
		std::swap(VektorPok, f.VektorPok);
		return *this;
	}
	void UpisiStudenta(std::string ime, std::string prezime, int index)
	{
		if(PostojiLiIndeks(index)) throw std::logic_error ("Student sa zadanim brojem indeksa vec postoji");
		VektorPok.push_back(new StudentBachelor(ime, prezime, index));
	}
	void UpisiStudenta(std::string ime, std::string prezime, int index, int god)
	{
		if(PostojiLiIndeks(index)) throw std::logic_error ("Student sa zadanim brojem indeksa vec postoji");
		
		VektorPok.push_back(new StudentMaster(ime, prezime, index, god));
	}
	void ObrisiStudenta(int index)
	{
		if(!PostojiLiIndeks(index)) throw std::logic_error ("Student sa zadanim brojem indeksa ne postoji");
		for(auto i = 0; i != VektorPok.size(); i++) {
			if(VektorPok[i]->DajBrojIndeksa() == index) {
				delete VektorPok[i];
				VektorPok[i] = nullptr;
				VektorPok.erase(VektorPok.begin() + i);
				break;
			}
		}
		// std:find_if(VektorPok.begin(), VektorPok.end(), [index](ApstraktniStudent *s){
			
		// })
	}
	ApstraktniStudent &operator [](int index)
	{
		if(!PostojiLiIndeks(index)) throw std::logic_error ("Student sa zadanim brojem indeksa ne postoji");
		for(auto i = 0; i != VektorPok.size(); i++)
			if(VektorPok[i]->DajBrojIndeksa() == index) {
				return *VektorPok[i];
			}

	}
	ApstraktniStudent &operator[](int index) const
	{
		if(!PostojiLiIndeks(index)) throw std::logic_error ("Student sa zadanim brojem indeksa ne postoji");
		for(auto i = 0; i != VektorPok.size(); i++)
			if(VektorPok[i]->DajBrojIndeksa() == index) {
				return *VektorPok[i];
			}
	}
	void IspisiSveStudente() const
	{
		std::vector<ApstraktniStudent*> pomocni;
		pomocni = VektorPok;
		std::sort(pomocni.begin(), pomocni.end(), [](ApstraktniStudent *s1, ApstraktniStudent *s2) {
			if(s1->DajProsjek() == s2->DajProsjek()) return s1->DajBrojIndeksa() < s2->DajBrojIndeksa();
			return s1->DajProsjek() > s2->DajProsjek();
		});
		for(auto i = pomocni.begin(); i != pomocni.end(); i++) {
			(*i)->IspisiPodatke();
		}
	}
};
int main ()
{
	//kopirajući operator i pomijerajući operator
	Fakultet f1; //3 studenta
	f1.UpisiStudenta("Meho", "Mehic", 3412);
	f1.UpisiStudenta("Ibro", "Ibric", 3124, 2015);
	f1.UpisiStudenta("Pero", "Peric", 1243);

	Fakultet f2;  //2 studenta
	f2.UpisiStudenta("Meho", "Mehic", 1111);
	f2.UpisiStudenta("Ibro", "Ibric", 2222, 2015);

	f1 = f2;  //dodjela manjeg većem, sadai f1 i f2 imaju 2 elementa
	std::cout << "KOPIRAJUCI OPERATOR DODJELE - manji većem" << std::endl;
	std::cout << "Original prije promjene: " << std::endl;
	std::cout << "----------------------" << std::endl;
	f1.IspisiSveStudente();
	std::cout << "Kopija prije promjene: " << std::endl;
	std::cout << "----------------------" << std::endl;
	f2.IspisiSveStudente();

	f2.ObrisiStudenta(1111);  //f2 sada ima 1 element
	std::cout << "Original nakon promjene: " << std::endl;
	std::cout << "----------------------" << std::endl;
	f1.IspisiSveStudente();
	std::cout << "Kopija nakon promjene: " << std::endl;
	std::cout << "----------------------" << std::endl;
	f2.IspisiSveStudente();


	f2 = f1;  //f2 sada opet ima 2 elementa
	std::cout << "KOPIRAJUCI OPERATOR DODJELE - veći manjem" << std::endl;
	std::cout << "Original prije promjene: " << std::endl;
	std::cout << "----------------------" << std::endl;
	f1.IspisiSveStudente();
	std::cout << "Kopija prije promjene: " << std::endl;
	std::cout << "----------------------" << std::endl;
	f2.IspisiSveStudente();

	f2.ObrisiStudenta(1111); //f2 ima 1 element
	std::cout << "Original nakon promjene: " << std::endl;
	std::cout << "----------------------" << std::endl;
	f1.IspisiSveStudente();
	std::cout << "Kopija nakon promjene: " << std::endl;
	std::cout << "----------------------" << std::endl;
	f2.IspisiSveStudente();


	Fakultet f3; //3 studenta
	f3.UpisiStudenta("Meho", "Mehic", 3412);
	f3.UpisiStudenta("Ibro", "Ibric", 3124, 2015);
	f3.UpisiStudenta("Pero", "Peric", 1243);

	Fakultet f4;  //2 studenta
	f4.UpisiStudenta("Meho", "Mehic", 1111);
	f4.UpisiStudenta("Ibro", "Ibric", 2222, 2015);

	std::cout << std::endl << std::endl;
	f3 = std::move(f4);  //dodjela manjeg većem, sadai f3 i f4 imaju 2 elementa
	std::cout << "POMIJERAJUCI OPERATOR DODJELE - manji većem" << std::endl;
	f4.IspisiSveStudente(); //f4 je prazno

	f4.UpisiStudenta("Meho", "Mehic", 3412);
	f4.UpisiStudenta("Ibro", "Ibric", 3124, 2015);
	f4.UpisiStudenta("Pero", "Peric", 1243);
	f3 = std::move(f4);  //f3 je prazno
	f4.IspisiSveStudente();
	return 0;
}
