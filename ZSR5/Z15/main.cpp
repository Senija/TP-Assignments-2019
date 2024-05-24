class Stan
{
    std::string naselje;
    int broj_soba;
    double kvadratura;
};
class NamjesteniStan : public Stan
{
    std::vector<std::pair<std::string, int>> stvari;
};
class StambenaAgencija
{
    Stan **stanovi;
    int broj, kapacitet;
};
int main ()
{
    StambenaAgencija s1(10); // (1)  
    //StambenaAgencija s1 = 10; // ovo se ne smije kompajlirati 
    s1.DodajStan("Novo Sarajevo", 3, 60); // (2)  
    Stan stan("Ilidza", 4, 75.5); // (3)   
    s1.DodajStan(stan); // (4) - dodaje kopiju stana   
    StambenaAgencija s2(s1); // (5)  
    Stan &ref = s2.DajNajveciStan(); // (6)  
    std::vector<std::pair<std::string, int>> stvari {{"Televizor", 700},      {"Frizider", 450}, {"Ormar", 300}}; // {naziv, cijena}  
    NamjesteniStan nstan("Vratnik", 2, 50, stvari); // (7)   
    s2.DodajNamjestenStan(nstan); // (8)  
    Stan &sref(nstan);   
    s2.DodajNamjestenStan("Bjelave", 3, 70, {{"Jacuzzi", 4450},      {"Ves masina", 500}}); // (9)  
    std::cout << "Cijena stana: " << ~stan; // (10)    // cijena se računa kao kvadratura * 1000  
    std::cout << "Cijena namjestenog stana: " << ~sref; // (11)       // cijena se računa kao kvadratura * 2000 + vrijednost stvari    
    StambenaAgencija s3; // (12) - s3 ima kapacitet od 50 stanova   
    s3 = s1 + s2; // (13) - s3 će sadržavati sve stanove iz s1 i iz s2   
    s1 += s2; // (14) - u s1 dodaje sve stanove iz s2   
    const StambenaAgencija &cs3(s3); // referenca na const    
    const Stan *moj_stan = cs3[1]; // (15) moj_stan je pokazivač   
    s1[0].PromijeniBrojSoba(3); // (16) označava renoviranje stana   
    s3.Prodaj(2); // (17) briše 2. stan iz kolekcije    
    std::cout << "Ukupna kvadratura za naselje: " << s2("Novo Sarajevo"); // (18)     
    std::ofstream dat("stanovi.txt");    dat << s3; // (19)     
    StambenaAgencija s4("stanovi.txt"); // (20) učitava iz datoteke    
    std::cout << s4; // daje isti ispis kao i std::cout << s3  
    return 0;   }
