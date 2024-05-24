//TP 2018/2019: Tutorijal 8, Zadatak 4
#include <iostream>
#include <map>
#include <string>
#include <algorithm>
std::string ZamijeniPremaRjecniku(std::string recenica, std::map<std::string, std::string> rjecnik)
{
    //std::string recenica = recenica1;
    for(auto i = rjecnik.begin(); i != rjecnik.end(); i++) {
        int BivsaPozicija = 0;
        while(recenica.find(i->first, BivsaPozicija) != std::string::npos) {
            int pozicija = recenica.find(i->first, BivsaPozicija);
            if(recenica.find(i->first) != std::string::npos) {
                std::string::iterator it = recenica.begin() + pozicija + (i->first).length();
                if((pozicija == 0 || recenica[pozicija-1] ==' ' )&& (recenica[pozicija+(i->first).length()]==' ' || it == recenica.end())) {
                    auto ubaci = recenica.erase(pozicija, (i->first).length());
                    recenica.insert(pozicija, i->second);
                    BivsaPozicija = pozicija + (i->second).length();

                } else
                    BivsaPozicija = pozicija + (i->first).length();
            }
        }
    }
    return recenica;
}
int main ()
{
    std::map<std::string, std::string> rjecnik {
        {"jabuka", "apple"},
        {"da", "yes"},
        {"kako", "how"},
        {"ne", "no"},
        {"majmun", "monkey"},
        {"mart", "ozujak"},
        {"maj", "svibanj"},
        {"jul", "srpanj"}
    };

    std::cout << ZamijeniPremaRjecniku("  kako   da   ne   ", rjecnik) << std::endl;
    return 0;
}
