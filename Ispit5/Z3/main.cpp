//TP 2018/2019: Ispit 5, Zadatak 3
#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
bool JeLiPOlindrom( std::string rijec){
    for(int i = 0; i < rijec.length(); i++){
        if(rijec[i] >= 'A' && rijec[i] <='Z'){
            rijec[i] = char(tolower(rijec[i]));
        }
    }
    std::string rijec2 = rijec;
    std::reverse(rijec.begin(), rijec.end());
    return rijec == rijec2;
}
std::vector<std::string> IzdvojiPalindromskeRijeci(const std::string &s){
    std::vector<std::string> novi;
    for(int i = 0; i < s.length(); i++){
        if((s[i] >='A' && s[i] <= 'Z')  || (s[i] >='a' && s[i] <= 'z') ){
            auto poc = i;
            while((s[i] >='A' && s[i] <= 'Z')  || (s[i] >='a' && s[i] <= 'z')){
                i++;
                //if(i == s.length() - 1) break;
            }
            auto kraj = i;
            std::string rijec = s.substr(poc, kraj - poc);
            if(JeLiPOlindrom(rijec) && rijec.length() >= 2){
                novi.push_back(rijec);
            }
        }
        else continue;
    }
    return novi;
}

int main ()
{

    
    std::string rec;
    std::cout<<"Unesite string: ";
    std::getline(std::cin, rec);
    auto v = IzdvojiPalindromskeRijeci(rec);
    for(std::string x : v) std::cout<<x<<std::endl;
	return 0;
}