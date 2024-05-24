//TP 2018/2019: Tutorijal 8, Zadatak 1
#include <iostream>
#include <iomanip>
struct Vrijeme {
    int sati;
    int minute;
    int sekunde;
};

void TestirajVrijeme(Vrijeme v)
{
    if(v.sati < 0 || v.sati > 23 || v.minute < 0 || v.minute > 59 ||  v.sekunde < 0 || v.sekunde > 59) throw std::domain_error ("Neispravno vrijeme");
    return;
}
void IspisiVrijeme(Vrijeme v)
{
    try {
        TestirajVrijeme(v);
        std::cout<<std::setw(2)<<std::setfill('0')<<v.sati<<":"<<std::setw(2)<<std::setfill('0')<<v.minute<<":"<<std::setw(2)<<std::setfill('0')<<v.sekunde;
    } catch(...) {
        throw;
    }
}
Vrijeme SaberiVrijeme(Vrijeme v1, Vrijeme v2)
{
    try {
        TestirajVrijeme(v1);
        TestirajVrijeme(v2);
        Vrijeme sabrano;
        sabrano.sati = 0;
        sabrano.minute = 0;
        sabrano.sekunde = 0;
        sabrano.sekunde = v1.sekunde + v2.sekunde;
        sabrano.minute = sabrano.sekunde/60;
        if(sabrano.minute) sabrano.sekunde = sabrano.sekunde % 60;
        sabrano.minute += v1.minute + v2.minute;
        sabrano.sati = sabrano.minute/60;
        if(sabrano.sati) sabrano.minute = sabrano.minute % 60;
        sabrano.sati += v1.sati + v2.sati;
        if(sabrano.sati >= 24) sabrano.sati = sabrano.sati % 24;
        return sabrano;
    } catch(...) {
        throw;
    }

}
int main ()
{
    Vrijeme v1, v2;

    try {
        std::cout<<"Unesite prvo vrijeme (h m s): ";
        std::cin>>v1.sati>>v1.minute>>v1.sekunde;
        TestirajVrijeme(v1);
        std::cout<<"Unesite drugo vrijeme (h m s): ";
        std::cin>>v2.sati>>v2.minute>>v2.sekunde;
        TestirajVrijeme(v2);
        std::cout<<"Prvo vrijeme: ";
        IspisiVrijeme(v1);
        std::cout<<std::endl<<"Drugo vrijeme: ";
        IspisiVrijeme(v2);
        std::cout<<std::endl<<"Zbir vremena: ";
        IspisiVrijeme(SaberiVrijeme(v1, v2));
    } catch(std::domain_error izuzetak) {
        std::cout<<izuzetak.what()<<std::endl;
    }
    return 0;
}
