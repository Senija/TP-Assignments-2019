//TP 2018/2019: Ispit 3, Zadatak 3
#include <iostream>
template <typename TipElemenata>
struct Cvor {
    TipElemenata element;
    Cvor *veza;
};
template<typename Tip>
class Stek{
    Cvor<Tip> *vrh;
    public:
    Stek(Stek<Tip> &s) = delete;
    Stek(Stek<Tip> &&s) = delete;
    Stek &operator =(Stack<Tip>) = delete;
    Stek ():vrh(nullptr){
        
    }
    ~Stek(){
        for(auto i = vrh; i != nullptr;){
            auto pom = vrh;
            vrh = pom->veza;
            delete pom;
            i = vrh;
        }
    }
    
    void top(Tip element){
        auto novi = new Cvor<Tip>{element, vrh};
        vrh = novi;
    }
    
    void pop(){
        auto pomoc = vrh;
        vrh = pomoc->veza;
        delete pomoc;
    }
    
    bool empty(){
        return vrh;
    }
    
    int size(){
        int br = 0;
        for(auto i = vrh; i != nullptr; i = i->veza){
            br++;
        }
        return br;
    }
};
int main ()
{
    std::cout<<"----- AT 1 -----"<<std::endl;
    
    // AT 1: Provjera da li je struktura ispravno definirana
    {
        std::cout<<sizeof(Cvor<int>);  // Mora ispisati 8

        std::cout<<" "<<sizeof(Stek<int>);  // Mora ispisati 4
    }

    std::cout<<std::endl<<"----- AT 2 -----"<<std::endl;

    // AT 2: Provjera bacanja izuzetka za top
    {
        Stek<int> s;
        try
        {
            std::cout<<s.top();
            std::cout<<"Nije bacen izuzetak!";
        }
        catch(std::domain_error e)
        {
            std::cout<<e.what();
        }
        catch(...)
        {
            std::cout<<"Nije tacan tip izuzetka!";
        }
    }

    std::cout<<std::endl<<"----- AT 3 -----"<<std::endl;
    
    // AT 3: Provjera bacanja izuzetka za pop
    {
        Stek<int> s;
        try
        {
            s.pop();
            std::cout<<"Nije bacen izuzetak!";
        }
        catch(std::domain_error e)
        {
            std::cout<<e.what();
        }
        catch(...)
        {
            std::cout<<"Nije tacan tip izuzetka!";
        }
    }

    std::cout<<std::endl<<"----- AT 4 -----"<<std::endl;
    
    // AT 4: Provjera da li su Cvor i Stek genericke strukture podataka
    {
        Stek<std::string> s;
        s.push(" TP :)");
        s.push(" cu");
        s.push("Poloziti");
        while(!s.empty())
        {
            std::cout<<s.top();
            s.pop();
        }
    }

    std::cout<<std::endl<<"----- AT 5 -----"<<std::endl;
    
    // AT 5: Test ispravnog brisanja i unosa elemenata
    {
        Stek<int> s;
        s.push(1);
        s.push(2);
        s.push(3);
        s.pop();
        s.pop();
        s.push(9);
        s.push(8);

        while(!s.empty())
        {
            std::cout<<s.top()<<" ";
            s.pop();
        }
    }
    return 0;
}
