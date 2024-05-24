#include <iostream>
#include <vector>
#include <stdexcept>
#include <initializer_list>

template <typename TipEl>
class SimetricnaMatrica
{
    std::vector<std::vector<TipEl>> Simetricna_mat;
    template<typename Tip2>
    bool DaLiJeGrbava(Tip2 VektorVektora) const
    {
        //NULLVEKTOR
        if(VektorVektora.size() == 0) return true;
        //bool grbava;
        int i = 0;
        for(auto red = VektorVektora.begin(); red < VektorVektora.end(); red++) {
            if(red->size() != i+ 1) {
                return false;
            }
            i++;
        }
        return true;
    }

    template<typename Tip3>
    class Omotac
    {
        int red;
        std::vector<std::vector<Tip3>> &OmotacOkoSimetricneM;

    public:
        Omotac(SimetricnaMatrica<Tip3> &SM, int red): red(red), OmotacOkoSimetricneM(SM.Simetricna_mat)
        {
        }

        Tip3 & operator [](int kolona)
        {
            if(kolona > red) return OmotacOkoSimetricneM[kolona][red];
            else return OmotacOkoSimetricneM[red][kolona];
        }

        Tip3 operator [](int kolona) const
        {
            if(kolona > red) return OmotacOkoSimetricneM[kolona][red];
            else return OmotacOkoSimetricneM[red][kolona];
        }
    };


    template<typename Tip4>
    class ConstOmotac
    {
        int red;
        const std::vector<std::vector<Tip4>> &OmotacOkoSimetricneM;

    public:
        ConstOmotac(const SimetricnaMatrica<Tip4> &SM, int red): red(red), OmotacOkoSimetricneM(SM.Simetricna_mat)
        {
        }

        // Tip3 & operator [](int kolona)
        // {
        //     if(kolona > red) return OmotacOkoSimetricneM[kolona][red];
        //     else return OmotacOkoSimetricneM[red][kolona];
        // }

        Tip4 operator [](int kolona) const
        {
            if(kolona > red) return OmotacOkoSimetricneM[kolona][red];
            else return OmotacOkoSimetricneM[red][kolona];
        }
    };



public:
    SimetricnaMatrica()
    {
    }

    template<typename Tip1>
    SimetricnaMatrica(const SimetricnaMatrica<Tip1> &SM)  // PROVJERA ZA KOMPATIBILNOST
    {
        Simetricna_mat.resize(SM.size());
        for(int i = 0; i < SM.size(); i++) {
            Simetricna_mat.at(i).resize(SM.at(i));
            for(int j = 0; j < SM.at(i).size(); j++) {
                Simetricna_mat.at(i).at(j) = SM.at(i).at(j);
            }
        }
    }

    SimetricnaMatrica(const std::vector<std::vector<TipEl>> &VektorVektora)
    {
        if(!DaLiJeGrbava(VektorVektora)) throw std::logic_error ("Nekorektna forma simetricne matrice");
        Simetricna_mat.resize(VektorVektora.size());
        for(int i = 0; i < VektorVektora.size(); i++) {
            Simetricna_mat.at(i).resize(VektorVektora.at(i).size());
            for(int j = 0; j <VektorVektora.at(i).size(); j++) {
                Simetricna_mat.at(i).at(j) = VektorVektora.at(i).at(j);
            }
        }
    }

    SimetricnaMatrica(std::initializer_list<std::initializer_list<TipEl>> ListaSimMatrice)
    {
        if(!DaLiJeGrbava(ListaSimMatrice)) throw std::logic_error ("Nekorektna forma simetricne matrice");
        Simetricna_mat.resize(ListaSimMatrice.size());
        auto red = ListaSimMatrice.begin();
        for(auto i = 0; i < ListaSimMatrice.size(); i++) {
            Simetricna_mat.at(i).resize(red->size());
            auto element = red->begin();
            for(int j = 0; j < red->size(); j++) {
                Simetricna_mat.at(i).at(j) = *element;
                element++;
            }
            red++;
        }

    }

    SimetricnaMatrica(int n)
    {
        if(n < 0) throw std::domain_error ("Neispravna dimenzija");
        Simetricna_mat.resize(n); // zasto kaze n puta n
        for(int i = 0; i < n; i++) {
            Simetricna_mat.at(i).red(n);
        }
    }

    int DajDimenziju() const
    {
        return Simetricna_mat.size();
    }

    bool operator !() const
    {
        if(Simetricna_mat.size() == 0) return true;
        for(int i = 0; i < Simetricna_mat.size(); i++) {
            for(int j = 0; j < Simetricna_mat.at(i).size(); i++) {
                if(Simetricna_mat.at(i).at(j) != 0) return false;
            }
        }
        return true;
    }

    ConstOmotac<TipEl> operator [](int red) const
    {
        return ConstOmotac<TipEl>(*this, red);

    }

    Omotac<TipEl> operator [](int red)
    {
        return Omotac<TipEl>(*this, red);
    }

    //SimetricnaMatrica &operator += (const SimetricnaMatrica &SM);

};
// template <typename Tip>
// SimetricnaMatrica<Tip>& SimetricnaMatrica<Tip>::operator += (const SimetricnaMatrica &SM)
// {
//     if(!DaLiJeGrbava(SM.Simetricna_mat)) throw std::domain_error ("Matrice nisu saglasne za trazenu operaciju");
//     if(Simetricna_mat.size() != SM.Simetricna_mat.size()) throw std::domain_error ("Matrice nisu saglasne za trazenu operaciju");
//     if(Simetricna_mat.size() != 0) {
//         std::vector<std::vector<decltype(Simetricna_mat[0][0] + SM.Simetricna_mat[0][0])>> pomocni;
//         pomocni.resize(Simetricna_mat.size());
//         for(int i = 0; i < Simetricna_mat.size(); i++) {
//             pomocni[i].resize(Simetricna_mat.at[i].size());
//             for(int j = 0; j < Simetricna_mat[i].size(); j++) {
//                 pomocni[i][j] = Simetricna_mat.at(i).at(j) + SM.Simetricna_mat.at(i).at(j);
//             }
//         }
        
//         //Simetricna_mat = pomocni;
//         return *this;
//     }
// }
// template<typename >
// template <typename TipEl>
// bool SimetricnaMatrica<TipEl> ::operator !(const SimetricnaMatrica<TipEl> &SM)
// {
//     if(SM.size() == 0) return true;
//     for(int i = 0; i < SM.size(); i++) {
//         for(int j = 0; j < SM.at(i).size(); i++) {
//             if(SM.at(i).at(j) != 0) return false;
//         }
//     }
//     return true;
// }

int main ()
{
    // const SimetricnaMatrica<double> m({{1}, {2, 3}, {4, 5, 6}});
    // //m[0][1] = 10;
    // std::cout<<m[0][1];
    
    std::vector<int> a{1,2,3,4};
    std::vector<double> b{2.2, 3.3, 4.4, 5.5};
    // for(int i = 0; i < b.size(); i++){
    //     static_cast<double>(a) = b[i];
    // }
    // static_cast<double>(a);
    // for(int i = 0; i < a.size(); i++){
    //     static_cast<double>(a[i]);
    //     a[i] = b[i];
    // }
    
    // a = b;
    // std::cout<<a[0];
    return 0;
}
