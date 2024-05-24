//GENERICKA KLASA SKUP I PRIMJER PARC ZAD 4
#include <iostream>
#include <deque>
#include <vector>
#include <initializer_list>
#include <algorithm>
#include <string>

template<typename TipEl>
class Skup
{
  std::vector<TipEl> Vektor;
  template<typename Tip>
  bool PostojiLiDuplikat(Tip element) const
  {
    auto pom = std::find(Vektor.begin(), Vektor.end(), element);
    if(pom != Vektor.end()) return true;
    return false;
  }
public:
  Skup() {}

  Skup(std::initializer_list<TipEl> Lista)
  {
    for(auto i = Lista.begin(); i != Lista.end(); i++) {
      if(!PostojiLiDuplikat(*i))Vektor.push_back(*i);

    }
    std::sort(Vektor.begin(), Vektor.end(), [](TipEl x, TipEl y) {
      return x < y;
    });
  }

  int Velicina() const
  {
    return Vektor.size();
  }

  void Dodaj(TipEl element)
  {
    if(PostojiLiDuplikat(element)) return;
    Vektor.push_back(element);
    std::sort(Vektor.begin(), Vektor.end(), [](TipEl x, TipEl y) {
      return x < y;
    });
  }
  
  void Izbrisi(TipEl element)
  {
    for(auto i = Vektor.begin(); i != Vektor.end(); i++) {
      if(*i == element) {
        Vektor.erase(i);
        break;
      }
    }
  }
  
  void Ispisi() const
  {
    for(auto element : Vektor) std::cout<<element<<std::endl;
  }
  
  bool ImaLiGa(TipEl element) const{
    if(auto pom = std::find(Vektor.begin(), Vektor.end(), element) != Vektor.end()) return true;
    return false;
  }


};
int main ()
{
  Skup<std::string> skup{"a","b","a","a","b","d","c"};
  
  //skup.Izbrisi("a");
  skup.Dodaj("a");
  if(skup.ImaLiGa("a")) std::cout<<"TRUE"<<std::endl;
  skup.Ispisi();
  return 0;
}
