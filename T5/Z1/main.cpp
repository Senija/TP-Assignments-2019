#include <iostream>
#include <cmath>

void IzbaciPrvuRijec(char* it1, char* it2, char* destinacija){
	 bool razmak=true;
	 int br_rijeci=0;
	while(it1 != it2){
		if(*it1==' '){
			
			razmak=true;
		}
		else if(*it1 != '0' && razmak){
			
			razmak=false;
			br_rijeci++;
			if(br_rijeci==2){
				while(it1 != it2){
					*destinacija++=*it1++;
				}
			}
		}
		if(it1==it2 || *it1=='\0') break;
		it1++;
	}
}

int main ()
{
	char recenica[1000];
	std::cout<<"Unesite recenicu: ";
	std::cin.getline(recenica, sizeof recenica);
	char BezPrveRijeci[1000]= {'\0'};
	IzbaciPrvuRijec(std::begin(recenica), std::end(recenica), std::begin(BezPrveRijeci));
	std::cout<<"Recenica bez prve rijeci glasi: "<<BezPrveRijeci<<std::endl;
	return 0;
}