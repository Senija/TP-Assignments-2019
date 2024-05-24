#include <iostream>
#include <iomanip>
#include <stdexcept>
#include <new>


template <typename TipElemenata>
struct Matrica {
    int br_redova, br_kolona;
    TipElemenata **elementi = nullptr; // VEOMA BITNA INICIJALIZACIJA!
    char ime_matrice;
};

template <typename TipElemenata>
void UnistiMatricu(Matrica<TipElemenata> &mat)
{
    if(!mat.elementi) return;
    for(int i = 0; i < mat.br_redova; i++) delete[] mat.elementi[i];
    delete[] mat.elementi;
    mat.elementi = nullptr;
}

template <typename TipElemenata>
Matrica<TipElemenata> StvoriMatricu(int br_redova, int br_kolona,
                                    char ime = 0)
{
    Matrica<TipElemenata> mat;
    mat.br_redova = br_redova;
    mat.br_kolona = br_kolona;
    mat.ime_matrice = ime;
    mat.elementi = new TipElemenata*[br_redova] {};
    try {
        for(int i = 0; i < br_redova; i++)
            mat.elementi[i] = new TipElemenata[br_kolona];
    } catch(...) {
        UnistiMatricu(mat);
        throw;
    }
    return mat;
}

template <typename TipElemenata>
void UnesiMatricu(Matrica<TipElemenata> &mat)
{
    for(int i = 0; i < mat.br_redova; i++)
        for(int j = 0; j < mat.br_kolona; j++) {
            std::cout << mat.ime_matrice
                      << "(" << i + 1 << "," << j + 1 << ") = ";
            std::cin >> mat.elementi[i][j];
        }
}

template <typename TipElemenata>
Matrica<TipElemenata> ProduktMatrica(const Matrica<TipElemenata> &m1, const Matrica<TipElemenata> &m2)
{
    //if(m1.br_kolona != m1.br_redova || m2.br_kolona != m2.br_redova) throw std::domain_error (" ")
    if(m1.br_kolona != m2.br_redova) throw std::domain_error ("Matrice nisu saglasne za mnozenje");
    auto Pomnozena = StvoriMatricu<TipElemenata>(m1.br_redova, m2.br_kolona);
    for(int i = 0; i < m1.br_redova; i++) {
        for(int j = 0; j < m2.br_kolona; j++) {
            TipElemenata suma = TipElemenata();
            for(int k=0; k<m2.br_redova; k++) suma += m1.elementi[i][k] * m2.elementi[k][j];
            Pomnozena.elementi[i][j] = suma;
        }
    }
    return Pomnozena;
}

template <typename TipElemenata>
Matrica<TipElemenata> ZbirMatrica(const Matrica<TipElemenata> &m1,
                                  const Matrica<TipElemenata> &m2)
{
    if(m1.br_redova != m2.br_redova || m1.br_kolona != m2.br_kolona)
        throw std::domain_error("Matrice nemaju jednake dimenzije!");
    auto m3 = StvoriMatricu<TipElemenata>(m1.br_redova, m1.br_kolona);
    for(int i = 0; i < m1.br_redova; i++)
        for(int j = 0; j < m1.br_kolona; j++)
            m3.elementi[i][j] = m1.elementi[i][j] + m2.elementi[i][j];
    return m3;
}

template <typename TipElemenata>
void PomnoziSaSkalarom( Matrica<TipElemenata> &m, double skalar)
{

    for(int i = 0; i < m.br_redova; i++) {
        for(int j = 0; j < m.br_kolona; j++) {
            m.elementi[i][j] = m.elementi[i][j] * skalar;
        }
    }
}

template <typename TipElemenata>
void ZbirMatricaLvl2(Matrica<TipElemenata> &rez, const Matrica<TipElemenata> &sabrana)
{
    for(int i = 0; i<rez.br_redova; i++) {
        for(int j = 0; j<rez.br_kolona; j++) {
            rez.elementi[i][j] += sabrana.elementi[i][j];//nije plitko kopiranje jer se elementi kopiraju ne POK
        }
    }
}
template <typename TipElemenata>
void DubokoKopiranje(Matrica<TipElemenata> &prazna, const Matrica<TipElemenata> popunjena)
{
    for (int i=0; i < prazna.br_redova; i++ )
        for(int j = 0; j < prazna.br_kolona; j++)
            prazna.elementi[i][j] = popunjena.elementi[i][j];
}

template <typename TipElemenata>
Matrica<TipElemenata> MatricniHarmonijskiPolinom(const Matrica<TipElemenata> &m1, int n)
{
    if(m1.br_redova != m1.br_kolona) throw std::domain_error ("Matrica nije kvadratna");
    if(n < 0) throw std::domain_error ("Pogresan parametar n");
    auto MatPolinom = StvoriMatricu<TipElemenata>(m1.br_redova, m1.br_kolona);
    auto Pomocna = StvoriMatricu<TipElemenata>(m1.br_redova, m1.br_kolona);
    //auto Proizvod = StvoriMatricu<TipElemenata>(m1.br_redova, m1.br_kolona);
    DubokoKopiranje<TipElemenata>(MatPolinom, m1);
    DubokoKopiranje<TipElemenata>(Pomocna, m1);
    //DubokoKopiranje<TipElemenata>(Proizvod, m1);
    for(int i = 2; i <= n; i++) {
        auto Proizvod = ProduktMatrica<TipElemenata>(Pomocna, m1);
        DubokoKopiranje<TipElemenata>(Pomocna, Proizvod);
        PomnoziSaSkalarom<TipElemenata>(Proizvod, 1./i);
        ZbirMatricaLvl2<TipElemenata>(MatPolinom, Proizvod);
        UnistiMatricu<TipElemenata>(Proizvod);
    }
    UnistiMatricu(Pomocna);
    return MatPolinom;
}

template <typename TipElemenata>
void IspisiMatricu( Matrica<TipElemenata> mat, int sirina_ispisa, int preciznost = 6, bool treba_brisati = false)
{
    if(!mat.elementi) return;
    for(int i = 0; i < mat.br_redova; i++) {
        for(int j = 0; j < mat.br_kolona; j++)
            std::cout << std::setw(sirina_ispisa) <<std::setprecision(preciznost) << mat.elementi[i][j];
        std::cout << std::endl;
    }
    if(treba_brisati) {
        UnistiMatricu<TipElemenata>(mat);
        mat.elementi = nullptr;
    }
}

int main()
{

    Matrica<double> a;
    int m, n, eksponent;
    std::cout << "Unesi broj redova i kolona za matrice:\n";
    std::cin >> m >> n;
    std::cout << "Unesi stepen polinoma:\n";
    std::cin>>eksponent;
    try {
        a = StvoriMatricu<double>(m, n, 'A');
        std::cout << "Unesi matricu A:\n";
        UnesiMatricu(a);
        std::cout << "Matricni Harmonijski polinom\n";
        IspisiMatricu(MatricniHarmonijskiPolinom<double>(a, eksponent), 10, 6, true);
    } 
    catch(std::bad_alloc) {
        std::cout << "Nema dovoljno memorije!\n";
    }
    catch(std::domain_error e){
        std::cout<<e.what()<<std::endl;
    }
    UnistiMatricu(a);

    return 0;

}
