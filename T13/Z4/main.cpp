#include <iostream>
#include <string>
#include <stdexcept>
#include <new>
#include <utility>
#include<vector>
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

class Student
{
    ApstraktniStudent *polimorfniStudent;
    bool Test() const
    {
        if(!polimorfniStudent) return true;
        return false;
    }
public:
    Student()
    {
        polimorfniStudent = nullptr;
    }
    ~Student()
    {
        delete polimorfniStudent;
    }
    Student(const ApstraktniStudent &s)
    {
        polimorfniStudent = s.DajKopiju();
    }
    Student(const Student &s)
    {
        polimorfniStudent = s.polimorfniStudent->DajKopiju();
    }
    Student(Student &&s)
    {
        polimorfniStudent = s.polimorfniStudent;
        s.polimorfniStudent= nullptr;
    }
    Student &operator =(const Student &s)
    {
        ApstraktniStudent *novi = nullptr;
        try {

            novi = s.polimorfniStudent->DajKopiju();
            delete polimorfniStudent;
            polimorfniStudent = novi;
        } catch(...) {
            delete novi;
        }
        return *this;
    }
    Student &operator =(Student &&s)
    {
        std::swap(polimorfniStudent, s.polimorfniStudent);
        return *this;
    }
     std::string DajIme() const
    {
        return polimorfniStudent->DajIme();
    }
    std::string DajPrezime() const
    {
        return polimorfniStudent->DajPrezime();
    }
    int DajBrojPolozenih() const
    {
        return polimorfniStudent->DajBrojPolozenih();
    }
    double DajProsjek() const
    {
        return polimorfniStudent->DajProsjek();
    }
    int DajBrojIndeksa() const
    {
        return polimorfniStudent->DajBrojIndeksa();
    }

    void RegistrirajIspit(int ocjena)
    {
       polimorfniStudent->RegistrirajIspit(ocjena);
    }
    void PonistiOcjene()
    {
        polimorfniStudent->PonistiOcjene();
    }
    void IspisiPodatke(){
        polimorfniStudent->IspisiPodatke();
    }


};
int main ()
{
    //registriraj ispit
  StudentBachelor sb("Dusko", "Dugousko", 1234);
  StudentMaster sm("Paja", "Patak", 4312, 2015);
  Student s1(sb), s2(sm);
  s1.RegistrirajIspit(6); s1.RegistrirajIspit(9);
  s2.RegistrirajIspit(8);
  s1.IspisiPodatke();
  s2.IspisiPodatke();
    return 0;
}
