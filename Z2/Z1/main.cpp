#include <iostream>
#include <vector>
#include <algorithm>
#include <cmath>
#include <exception>

typedef std::vector<std::vector<char>> Matrica;
typedef std::vector<std::vector<int>> MatricaInt;
typedef std::vector<Matrica> Matrica3D;

int BrojRedova(const Matrica &mat)
{
    return mat.size();
}
int BrojKolona(const Matrica &mat)  //pravilna ako je
{
    if(BrojRedova(mat) != 0 ) return mat.at(0).size();
    else return 0;
}
bool JeLiPravilna(const Matrica &mat)
{
    bool pravilna =true;
    for(int i=0; i<mat.size() -1; i++) {
        if(mat.at(i).size() != mat.at(i+1).size()) return false;
    }
    return pravilna;
}
bool JeLiKvadratna (const Matrica &mat)
{
    return BrojKolona(mat) == BrojRedova(mat);
}

bool IsteDimSpratova(const Matrica3D &mat)
{
    return BrojRedova(mat.at(0)) == BrojRedova(mat.at(1));
}

std::vector<std::vector<std::vector<char>>> KreirajMatrice(int m, int n)
{
    if(m<=0 || n<=0) throw std::domain_error ("Dimenzije matrica moraju biti pozitivne");
    if(m>=100 || n>=100) throw std::domain_error ("Prevelike dimenzije");
    if(m!=n) throw std::domain_error ("Matrice moraju biti kvadratne");

    Matrica PrviIgrac = Matrica(m, std::vector<char>(n, '-'));
    Matrica DrugiIgrac = Matrica(m, std::vector<char>(n, '-'));
    // for(int i=0; i<m; i++) {
    //     for(int j=0; j<n; j++) {
    //         std::cout<<PrviIgrac.at(i).at(j);
    //     }
    //     std::cout<<std::endl;
    // }
    Matrica3D MatIgrice(2) ;                                                                            //VELICINA 3D MATRICE
    MatIgrice[0] = PrviIgrac;
    MatIgrice[1] = DrugiIgrac;
    return MatIgrice;
}

bool Minimun(int x, int y)
{
    return x <= y;
}

bool DaLiSuKooJednake(int x, int y)
{
    return x == y;
}

MatricaInt TransformirajMatKoordinata(MatricaInt Koordinate)
{
    MatricaInt povratna (2, std::vector<int>(2));
    if(DaLiSuKooJednake(Koordinate.at(0).at(0), Koordinate.at(1).at(0))) {
        povratna.at(0).at(0) = Koordinate.at(0).at(0);//iste  koordinate prve istoim je j
        povratna.at(0).at(1) = 201;

        if(Minimun(Koordinate.at(0).at(1), Koordinate.at(1).at(1))) {
            povratna.at(1).at(0) = Koordinate.at(0).at(1);
            povratna.at(1).at(1) = Koordinate.at(1).at(1);
        } else {
            povratna.at(1).at(0) = Koordinate.at(1).at(1);
            povratna.at(1).at(1) = Koordinate.at(0).at(1);
        }
    } else {
        povratna.at(0).at(0) = Koordinate.at(0).at(1);
        povratna.at(0).at(1) = 101;        //IMAJU ISTO I

        if(Minimun(Koordinate.at(0).at(0), Koordinate.at(1).at(0))) {
            povratna.at(1).at(0) = Koordinate.at(0).at(0);
            povratna.at(1).at(1) = Koordinate.at(1).at(0);
        } else {
            povratna.at(1).at(0) = Koordinate.at(1).at(0);
            povratna.at(1).at(1) = Koordinate.at(0).at(0);
        }
    }

    return povratna;
}

bool NacrtajKoordinate(const MatricaInt &Koordinate)
{
    for(int i=0; i<2; i++) {
        for(int j=0; j<2; j++) {
            if(Koordinate.at(i).at(j) != -2) return false;
        }
    }
    return true;
}

bool ProvjeraKoordinata(const Matrica &Igrac,  MatricaInt &Koordinate, int RedniBrRobota)
{

    bool valjane = true;
    //bool SpecKoordinate = NacrtajKoordinate(Koordinate);
    for(int i=0; i<2; i++) {
        for(int j=0; j<2; j++) {
            if((Koordinate.at(i).at(j) < 0 && Koordinate.at(i).at(j) != -2) || Koordinate.at(i).at(j)> BrojRedova(Igrac)-1 || Koordinate.at(i).at(j) > BrojKolona(Igrac)-1) {
                std::cout<<"Pogresne koordinate gdje zelite smjestiti robota"<<std::endl;
                return valjane = false;
            }
        }
    }


    if(!DaLiSuKooJednake(Koordinate.at(0).at(0), Koordinate.at(1).at(0))  && !DaLiSuKooJednake(Koordinate.at(0).at(1), Koordinate.at(1).at(1))) {
        std::cout<<"Pogresne koordinate gdje zelite smjestiti robota"<<std::endl;
        return valjane = false;
    } else {
        Koordinate = TransformirajMatKoordinata(Koordinate);
        int br_polja_izmedju = std::abs (Koordinate.at(1).at(1) - Koordinate.at(1).at(0));
        //std::cout<<br_polja_izmedju;PROVJERA
        if(br_polja_izmedju == RedniBrRobota) {
            if(Koordinate.at(0).at(1) == 101) {
                for(int i=Koordinate.at(1).at(0); i<=Koordinate.at(1).at(1); i++) {
                    if(Igrac.at(Koordinate.at(0).at(0)).at(i) != '-') {
                        std::cout<<"Pogresne koordinate gdje zelite smjestiti robota"<<std::endl;
                        return valjane = false;
                    }
                }
            } else {
                for(int i=Koordinate.at(1).at(0); i<=Koordinate.at(1).at(1); i++) {
                    if(Igrac.at(i).at(Koordinate.at(0).at(0)) != '-') {
                        std::cout<<"Pogresne koordinate gdje zelite smjestiti robota"<<std::endl;
                        return valjane = false;
                    }
                }
            }
        } else {
            std::cout<<"Pogresne koordinate gdje zelite smjestiti robota"<<std::endl;
            valjane = br_polja_izmedju == RedniBrRobota;
            if(!valjane) return valjane=false;
        }
    }
    return valjane;

}

void UpisiUMatricu(Matrica &Igrac, const MatricaInt &Koordinate, int RedniBrRobota)
{

    const char Roboti[16]= {'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'I', 'J', 'K', 'L', 'M', 'N', 'O'};
    if(Koordinate.at(0).at(1) == 101) {
        for(int i=Koordinate.at(1).at(0); i<=Koordinate.at(1).at(1); i++) {
            Igrac.at(Koordinate.at(0).at(0)).at(i) = Roboti[RedniBrRobota];
        }
    } else {
        for(int i=Koordinate.at(1).at(0); i<=Koordinate.at(1).at(1); i++) {
            Igrac.at(i).at(Koordinate.at(0).at(0)) = Roboti[RedniBrRobota];
        }
    }
}

bool MozeLiRobotStati(const Matrica &mat, int RedniBrRobota)
{

    bool kontinuitet = false;
    int brojac=0;
    for(int i=0; i<BrojRedova(mat); i++) {
        brojac=0;
        for(int j=0; j<BrojRedova(mat); j++) {
            if(mat.at(i).at(j) =='-') {
                kontinuitet = true;
                brojac++;
            } else if(kontinuitet) {
                if(brojac >= RedniBrRobota+1) return true;
                kontinuitet = false;
                brojac = 0;
            }

        }
        if(kontinuitet) {
            if(brojac >= RedniBrRobota+1) return true;
            kontinuitet= false;
            brojac =0;
        }
    }


    for(int j=0; j<BrojRedova(mat); j++) {
        brojac=0;
        for(int i=0; i<BrojRedova(mat); i++) {
            if(mat.at(i).at(j) =='-') {
                brojac++;
                kontinuitet=true;
            } else if(kontinuitet) {
                if(brojac >= RedniBrRobota+1) return true;
                kontinuitet = false;
                brojac =0;
            }
        }
        if(kontinuitet) {
            if(brojac >= RedniBrRobota+1) return true;
            kontinuitet= false;
            brojac = 0;
        }

    }
    return brojac >= RedniBrRobota+1;
}

void Nacrtaj(const std::vector<std::vector<std::vector<char>>> &mat, int n)
{
    for(int i=0; i< mat.at(n).size(); i++) {
        for(int j=0; j<mat.at(n).size(); j++) {
            if(mat.at(n).at(i).at(j) != '-' && mat.at(n).at(i).at(j) !='X' && mat.at(n).at(i).at(j) !='O') std::cout<<"R"<<" ";
            else std::cout<<mat.at(n).at(i).at(j)<<" ";
        }
        std::cout<<std::endl;
    }
}

void Unos(std::vector<std::vector<std::vector<char>>> &matrice, int p)
{

    if(matrice.size() == 0) throw std::domain_error ("Matrica ne postoji");
    if(matrice.size() != 2) throw std::range_error ("3D matrica ima pogrešne dimenzije");
    if(matrice.at(0).size() == 0 || matrice.at(1).size() == 0) throw std::domain_error ("Neka od dvije matrice je prazna");
    if(!JeLiPravilna(matrice.at(0)) || !JeLiPravilna(matrice.at(1))) throw std::domain_error ("Neka matrica je grbava");
    if(!JeLiKvadratna(matrice.at(0)) || !JeLiKvadratna(matrice.at(1))) throw std::domain_error ("Neka od matrica nije kvadratna");
    if(!IsteDimSpratova(matrice)) throw std::domain_error ("Matrice nemaju iste dimenzije");
    if(p > 15) throw std::range_error ("Zelite igrati sa previse robota");//ponovan unos
    if(p > BrojRedova(matrice.at(0))) throw std::overflow_error ("Zelite igrati sa previse robota");

    if(p<=0) throw std::domain_error ("Ne mozete igrati bez robota"); //ponovan unos

    for(int igrac=0; igrac<2; igrac++) {
        for(int RedniBrRobota=0; RedniBrRobota<p; RedniBrRobota++) { //unos koliko i broj robota;
            //std::vector<int> UnosKoordinata(2);
            if(!MozeLiRobotStati(matrice.at(igrac), RedniBrRobota)) throw std::overflow_error ("Nemoguce dovrsiti postavljanje robota");
            MatricaInt Prva_DrugaKoo(2, std::vector<int>(2));
            bool dobro_unesena = true;
            while(dobro_unesena) {
                if(igrac == 0 ) std::cout<<"Naida unesi pocetne i krajnje koordinate "<<RedniBrRobota+1<<". robota:"<<std::endl;
                if(igrac == 1) std::cout<<"Alina unesi pocetne i krajnje koordinate "<<RedniBrRobota+1<<". robota:"<<std::endl;
                double pomocna;
                for(int j=0; j<2; j++) {
                    int i=0;
                    while(1) {

                        std::cin>> pomocna;//Prva_DrugaKoo.at(j).at(i);
                        if(/*(std::cin.peek()!=' ' && std::cin.peek()!='\n') ||*/ !(std::cin) || int(pomocna) != pomocna) {
                            std::cout<<"Pogresne koordinate gdje zelite smjestiti robota"<<std::endl;
                            std::cin.clear();
                            //std::cin>>std::ws;
                            std::cin.ignore(10000, '\n');
                            i=0;
                            j=0;
                            if(igrac == 0 ) std::cout<<"Naida unesi pocetne i krajnje koordinate "<<RedniBrRobota+1<<". robota:"<<std::endl;
                            if(igrac == 1) std::cout<<"Alina unesi pocetne i krajnje koordinate "<<RedniBrRobota+1<<". robota:"<<std::endl;
                        } else {
                            Prva_DrugaKoo.at(j).at(i) = pomocna;
                            i++;
                        }
                        if(i==2) break;
                    }
                }
                if(NacrtajKoordinate(Prva_DrugaKoo)) {
                    Nacrtaj(matrice, igrac);
                    //RedniBrRobota--;
                } else if(ProvjeraKoordinata(matrice.at(igrac),Prva_DrugaKoo, RedniBrRobota)) {
                    dobro_unesena = false;
                    UpisiUMatricu(matrice.at(igrac), Prva_DrugaKoo, RedniBrRobota);
                }
            }
        }
    }
}
bool ProvjeraKoordinata(const Matrica3D &Mat3D, const int Igrac, const std::vector<int> &Koordinate)
{
    bool valjane = true;
    for(int i=0; i<2; i++) {
        if(Koordinate.at(i) < 0 || Koordinate.at(i) > BrojRedova(Mat3D.at(Igrac))-1 || Koordinate.at(i) > BrojKolona(Mat3D.at(Igrac))-1) {
            std::cout<<"Pogresne koordinate gdje zelite gadjati"<<std::endl;
            return valjane = false;
        }
    }
    bool SuprptniIgrac = !(bool(Igrac));
    if(Mat3D.at(SuprptniIgrac).at(Koordinate.at(1)).at(Koordinate.at(0)) == 'X' || Mat3D.at(SuprptniIgrac).at(Koordinate.at(1)).at(Koordinate.at(0)) == 'O') {
        std::cout<<"Vec ste gadjali ovo polje"<<std::endl;
        return valjane = false;
    }
    return valjane;

}
bool Izlaz(const std::vector<int> &UnosKoo)
{

    //bool nemoj_izaci = true;
    for(int i=0; i<2; i++) {
        if(UnosKoo.at(i) != -1) return  false;
    }
    return true;
}

bool DaLiJePromasaj(Matrica &mat, std::vector<int> &Koordinate)
{
    bool promasaj = false;
    if(mat.at(Koordinate.at(1)).at(Koordinate.at(0)) =='-') {
        std::cout<<"Promasaj"<<std::endl;
        promasaj=true;
        mat.at(Koordinate.at(1)).at(Koordinate.at(0)) = 'O';
    }
    return promasaj;
}

bool UpisiPogotke(Matrica3D &mat, int Igrac, const std::vector<int> &Koordinate, const std::vector<int> &NizPogodjenosti, int BrojRobota)
{
    int SuprotniIgrac = !(bool(Igrac));//indeks 0 u nizu

    //int nova = mat.at(SuprotniIgrac).at(Koordinate.at(1)).at(Koordinate.at(0)) - 65; 23
    if(NizPogodjenosti.at(mat.at(SuprotniIgrac).at(Koordinate.at(1)).at(Koordinate.at(0)) - 65) == mat.at(SuprotniIgrac).at(Koordinate.at(1)).at(Koordinate.at(0)) - 64) { //koordinata u matrici gdje je slovo A npr -64 =1
        std::cout<<"Unisteno"<<std::endl;
    } else std::cout<<"Pogodak"<<std::endl;

    mat.at(SuprotniIgrac).at(Koordinate.at(1)).at(Koordinate.at(0)) = 'X';
    bool unisteno = true;
    for(int i=0; i<BrojRobota; i++) {
        if(NizPogodjenosti.at(i) != i+1) {
            return unisteno = false;
        }
    }
    return unisteno;
}

void IspisRezultata(int Igrac, std::vector<int> NizPogodjenosti, int BrojRobota)
{
    int br_unistenih = 0;
    int br_citav = 0;
    int br_ostecenih =0;
    for(int i=0; i<BrojRobota; i++) {
        if(NizPogodjenosti.at(i) == i+1) br_unistenih++;
        else if(NizPogodjenosti.at(i) == 0) br_citav++;
        else if(NizPogodjenosti.at(i)>0 && NizPogodjenosti.at(i)< i+1) br_ostecenih++;
    }

    if(!Igrac) std::cout<<"Naida ima "<<br_unistenih<<" unistenih, "<<br_ostecenih<<" ostecenih i "<<br_citav<<" citavih robota."<<std::endl;
    if(Igrac)  std::cout<<"Alina ima "<<br_unistenih<<" unistenih, "<<br_ostecenih<<" ostecenih i "<<br_citav<<" citavih robota.\n";
}

bool PogadjanjeRobota(std::vector<std::vector<std::vector<char>>> &mat, int p)
{
    //int brUnosa =0;
    bool Igrac1 = true;
    std::vector<int> NizPogodjenostiIgrac1(15);
    std::vector<int> NizPogodjenostiIgrac2(15);
    for(;;) {

        std::vector<int> UnosKoordinata(2);
        double pomocna;
        if(Igrac1) std::cout<<"Naida unesi koordinate koje zelis gadjati:"<<std::endl;
        if(!Igrac1) std::cout<<"Alina unesi koordinate koje zelis gadjati:"<<std::endl;
        int i=0;
        while(1) {

            std::cin>>pomocna;//UnosKoordinata.at(i);
            if(/*(std::cin.peek()!=' ' && std::cin.peek()!='\n') || */!(std::cin) || int(pomocna) != pomocna) {
                std::cout<<"Pogresne koordinate gdje zelite gadjati"<<std::endl;
                std::cin.clear();
                std::cin.ignore(10000, '\n');
                i=0;
                Igrac1 = !Igrac1;
                if(Igrac1) std::cout<<"Naida unesi koordinate koje zelis gadjati:"<<std::endl;
                if(!Igrac1) std::cout<<"Alina unesi koordinate koje zelis gadjati:"<<std::endl;
            } else {
                UnosKoordinata.at(i) = pomocna;
                i++;
            }
            if(i==2) break;
        }


        if(UnosKoordinata.at(0) == -2 && UnosKoordinata.at(1) == -2) {
            if(Igrac1) Nacrtaj(mat, 0);
            else Nacrtaj(mat, 1);
        } else if(Izlaz(UnosKoordinata)) {
            IspisRezultata(0, NizPogodjenostiIgrac2, p);
            IspisRezultata(1, NizPogodjenostiIgrac1, p);
            return false;

        }

        else if(Igrac1) {
            if(ProvjeraKoordinata(mat, 0, UnosKoordinata)) {
                //napraviti vektor pogodjenosti i poslatoi ga gore

                if(!DaLiJePromasaj(mat.at(1), UnosKoordinata)) {
                    NizPogodjenostiIgrac1.at(mat.at(1).at(UnosKoordinata.at(1)).at(UnosKoordinata.at(0)) - 65)+=1;

                    if(UpisiPogotke(mat, 0, UnosKoordinata, NizPogodjenostiIgrac1, p)) {
                        std::cout<<"Naida je pobijedila. ";
                        IspisRezultata(0, NizPogodjenostiIgrac2, p);
                        return true;
                    }
                }

            }
            Igrac1 = false;
        } else if(!Igrac1) {
            if(ProvjeraKoordinata(mat, 1, UnosKoordinata)) {

                if(!DaLiJePromasaj(mat.at(0), UnosKoordinata)) {
                    NizPogodjenostiIgrac2.at(mat.at(0).at(UnosKoordinata.at(1)).at(UnosKoordinata.at(0)) - 65)+=1;

                    if(UpisiPogotke(mat, 1, UnosKoordinata, NizPogodjenostiIgrac2, p)) {
                        std::cout<<"Alina je pobijedila. ";
                        IspisRezultata(1, NizPogodjenostiIgrac1, p);
                        return true;
                    }
                }
            }
            Igrac1 = true;
        }
    }
    return Igrac1;

}
// void UnosDimenzija(std::vector<int> &Unos)
// {

//     int i=0;
//     while(1) {
//         std::cin>>Unos.at(i);
//         if(/*(std::cin.peek()!=' ' && std::cin.peek()!='\n') ||*/ !(std::cin)) {
//             std::cin.clear();
//             //std::cin>>std::ws;
//             std::cin.ignore(10000, '\n');
//             i=0;
//         } else i++;
//         if(i ==2) break;
//     }
// }
int main ()
{
    std::vector<int> Dimenzije(2);
    bool UnosNotOK = true;
    while(UnosNotOK)
        try {

            std::cout<<"Igra je pocela, unesite dimenzije matrica (dva broja):"<<std::endl;
            double pomocna;
            int i=0;
            while(1) {
                std::cin>>pomocna; //Dimenzije.at(i);
                if(/*(std::cin.peek()!=' ' && std::cin.peek()!='\n') ||*/ !(std::cin) || int(pomocna)!= pomocna) {
                    std::cin.clear();
                    //std::cin>>std::ws;
                    std::cin.ignore(10000, '\n');
                    i=0;
                } else {
                    Dimenzije.at(i) = pomocna;
                    i++;
                }
                if(i ==2) break;
            }
            auto Mat3D = KreirajMatrice(Dimenzije.at(0), Dimenzije.at(1));
            //Matrica3D Mat3D; Provjer
            UnosNotOK = false;

            bool BrojRobotaNotOK = true;
            while(BrojRobotaNotOK) {
                int BrRobota;
                std::cout<<"Unesite broj robota:"<<std::endl;
                std::cin>>BrRobota;
                bool UnosKooRepeat = true;
                //if(BrRobota >15 || BrRobota<= 0 || BrRobota!= Dimenzije.at(0))
                while(UnosKooRepeat) {
                    try {
                        Unos(Mat3D, BrRobota);
                        BrojRobotaNotOK = false;
                        UnosKooRepeat = false;
                        std::cout<<"Uspjesno ste unijeli pozicije robota. Sada moze poceti pogadjanje."<<std::endl;
                        PogadjanjeRobota(Mat3D, BrRobota);
                    } catch (std::domain_error izuzetak) {
                        if(BrRobota > 0) {
                            BrojRobotaNotOK = false;
                        }
                        UnosKooRepeat = false;
                        std::cout <<izuzetak.what()<< std::endl;
                    } catch(std::range_error izuzetak) {
                        if(BrRobota < 15) {
                            BrojRobotaNotOK = false;

                        }
                        UnosKooRepeat = false;
                        std::cout<<izuzetak.what()<<std::endl;
                    } catch(std::overflow_error izuzetak) {
                        if(BrRobota > Dimenzije.at(0)) UnosKooRepeat = false;
                        else BrojRobotaNotOK = false;
                        Mat3D = KreirajMatrice(Dimenzije.at(0), Dimenzije.at(1));
                        std::cout<<izuzetak.what()<<std::endl;
                    }

                }
            }


        } catch(std::domain_error izuzetak) {
            std::cout<<izuzetak.what()<<std::endl;
        }
    // MOZE LI STATI PROVJERA
    // auto a = KreirajMatrice(4,4);
    // a.at(0).at(2).at(2) = 'A';
    // a.at(0).at(1).at(3) = 'B';
    // a.at(0).at(2).at(3) = 'B';
    // a.at(0).at(0).at(1) = 'C';
    // a.at(0).at(0).at(2) = 'C';
    // a.at(0).at(0).at(3) = 'C';
    // for(int i=0; i<4; i++) {
    //     for(int j=0; j<4; j++) {
    //         std::cout<<a.at(0).at(i).at(j)<<" ";
    //     }
    //     std::cout<<std::endl;
    // }
    // MozeLiRobotStati(a.at(0), 3);
    // bool vat = MozeLiRobotStati(a.at(0), 3);
    // std::cout<<vat;
    /////////////////////////////////////////////////

    return 0;
}
