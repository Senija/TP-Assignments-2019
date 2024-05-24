//TP 2018/2019: Zadaća 5, Zadatak 5
#include <iostream>
#include <iomanip>
#include <cstring>
#include <stdexcept>
#include <new>
#include <string>
#include <sstream>
#include <fstream>
#include <algorithm>


// void kreirajDatotetkuZbii2()
// {
//     std::string ime = "matrica2.txt";
//     std::ofstream dat(ime);
//     dat << "1.4{2.54@3.7*-4.7";
//     dat.close();
// }
template <typename TipEl>
class Matrica
{
	int br_redova, br_kolona;
	TipEl **elementi = nullptr;
	char ime_matrice;
	static TipEl **AlocirajMemoriju(int br_redova, int br_kolona);
	static void DealocirajMemoriju(TipEl **elementi, int br_redova);
	void KopirajElemente(TipEl **elementi);
	void TestIndeksa(int red, int kolona) const
	{
		if(red > br_redova || kolona > br_kolona || red < 1 || kolona < 1) throw std::range_error ("Neispravan indeks");
	}
	template <typename T> std::string PretvoriUString(T x) const
	{
		std::ostringstream s;
		s << x;
		return s.str();
	}
public:
	Matrica(){}
	Matrica(int br_redova, int br_kolona, char ime = 0);
	Matrica(const Matrica &m);
	Matrica(Matrica &&m);
	Matrica(std::string naziv_datoteke, bool binarna);
	~Matrica()
	{
		DealocirajMemoriju(elementi, br_redova);
	}
	// int DajBrRedova() const
	// {
	// 	return br_redova;
	// }
	// int DajBrKolona() const
	// {
	// 	return br_kolona;
	// }
	Matrica &operator =(const Matrica &m);
	Matrica& operator +=( const Matrica &m2);
	Matrica& operator -=( const Matrica &m2);
	Matrica& operator *=(const Matrica &m2);
	Matrica& operator *=(double skalar);
	Matrica &operator =(Matrica &&m);
	operator std::string() const
	{
		std::string s= "{";
		for(auto i = 0; i != br_redova; i++) {
			s.push_back('{');
			for(auto j = 0; j != br_kolona; j++) {
				if(j == br_kolona - 1) {
					s += PretvoriUString(elementi[i][j]);
					if(i != br_redova -1) {
						s.push_back('}');
						s.push_back(',');
					} else s.push_back('}');
				} else {
					s += PretvoriUString(elementi[i][j]);
					s.push_back(',');
				}
			}
		}
		s.push_back('}');

		return s;
	}
	TipEl *operator [](int red) const
	{
		return elementi[red];
	}
	TipEl* &operator [](int red)
	{
		return elementi[red];
	}
	TipEl &operator ()(int red, int kolona)
	{
		try {
			TestIndeksa(red, kolona);
			return elementi[red-1][kolona-1];
		} catch(...) {
			throw;
		}
	}
	TipEl operator ()(int red, int kolona) const
	{
		try {
			TestIndeksa(red, kolona);
			return elementi[red-1][kolona-1];
		} catch(...) {
			throw;
		}
	}
	void SacuvajUTekstualnuDatoteku(std::string naziv_datoteke) const;
	void SacuvajUBinarnuDatoteku(std::string naziv_datoteke) const;
	void ObnoviIzTekstualneDatoteke(std::string naziv_datoteke);
	void ObnoviIzBinarneDatoteke(std::string naziv_datoteke);
	template <typename Tip4>
	friend std::istream& operator>>(std::istream &tok, Matrica<Tip4> &m);
	template <typename Tip3>
	friend std::ostream &operator<<(std::ostream &tok, const Matrica<Tip3> &m);
	template <typename Tip2>
	friend Matrica<Tip2> operator +(const Matrica<Tip2> &m1,const Matrica<Tip2> &m2);
	template <typename Tip5>
	friend Matrica<Tip5> operator -(const Matrica<Tip5> &m1,const Matrica<Tip5> &m2);
	template<typename Tip6>
	friend Matrica<Tip6> operator *(const Matrica<Tip6> &m1,const Matrica<Tip6> &m2);
	template<typename Tip7>
	friend Matrica<Tip7> operator *(const Matrica<Tip7> &m1, double skalar);
	template<typename Tip8>
	friend inline Matrica<Tip8> operator *(double skalar, const Matrica<Tip8> &m1);


};
template <typename TipEl>
TipEl ** Matrica<TipEl>::AlocirajMemoriju(int br_redova, int br_kolona)
{
	if(br_redova == 0 && br_kolona == 0) return nullptr;
	TipEl **elementi = new TipEl*[br_redova] {};
	try {
		for(int i = 0; i < br_redova; i++) elementi[i] = new TipEl[br_kolona] {};
	} catch(...) {
		DealocirajMemoriju(elementi, br_redova);
		throw;
	}
	return elementi;
}
template <typename TipEl>
void Matrica<TipEl>::DealocirajMemoriju(TipEl **elementi, int br_redova)
{
	for(int i = 0; i < br_redova; i++) {
		delete[] elementi[i];
		elementi[i] = nullptr;
	}
	delete[] elementi;
	elementi = nullptr;
}
template <typename TipEl>
Matrica<TipEl>::Matrica(int br_redova, int br_kolona, char ime) :
	br_redova(br_redova), br_kolona(br_kolona), ime_matrice(ime),
	elementi(AlocirajMemoriju(br_redova, br_kolona)) {}
template <typename TipEl>
void Matrica<TipEl>::KopirajElemente(TipEl **elementi)
{
	for(int i = 0; i < br_redova; i++)
		for(int j = 0; j < br_kolona; j++)
			Matrica::elementi[i][j] = elementi[i][j];
}
template <typename TipEl>
Matrica<TipEl>::Matrica(const Matrica<TipEl> &m) : br_redova(m.br_redova),
	br_kolona(m.br_kolona), ime_matrice(m.ime_matrice),
	elementi(AlocirajMemoriju(m.br_redova, m.br_kolona))
{
	KopirajElemente(m.elementi);
}
template <typename TipEl>
Matrica<TipEl>::Matrica(Matrica<TipEl> &&m) : br_redova(m.br_redova),
	br_kolona(m.br_kolona), elementi(m.elementi), ime_matrice(m.ime_matrice)
{
	m.br_redova = 0;
	m.elementi = nullptr;
}

template<typename TipEl>
Matrica<TipEl>::Matrica(std::string naziv_datoteke, bool binarna)
{
	if(!binarna) {
		std::ifstream ulazni_tok(naziv_datoteke);
		if(!ulazni_tok) throw std::logic_error ("Trazena datoteka ne postoji");
		int broj_kolona = 0;
		int broj_redova = 0;
		bool first = true;
		std::string red;
		while(std::getline(ulazni_tok, red)) {
			int br_zareza;
			ulazni_tok>>std::ws;
			broj_redova++;
			if(first) {
				broj_kolona = std::count(red.begin(), red.end(), ',');
				first = false;
			} else if(!first) {
				br_zareza = std::count(red.begin(), red.end(), ',');
				if(br_zareza != broj_kolona) throw std::logic_error ("Datoteka sadrzi besmislene podatke");
			}

		}
		ulazni_tok.close();
		ulazni_tok.open(naziv_datoteke);
		if(broj_kolona != 0) {
			broj_kolona += 1;
			elementi = AlocirajMemoriju(broj_redova, broj_kolona);
			for(int i = 0; i < broj_redova; i++) {
				for(int j = 0; j < broj_kolona; j++) {
					char znak;
					TipEl element;
					if(j != broj_kolona - 1) {
						ulazni_tok>>element>>znak>>std::ws;
						if(znak != ',') throw std::logic_error ("Datoteka sadrzi besmislene podatke");
						if(!ulazni_tok) {
							ulazni_tok.clear();
							DealocirajMemoriju(elementi, broj_redova);
							throw std::logic_error ("Datoteka sadrzi besmislene podatke");
						} else elementi[i][j] = element;
					} else {
						ulazni_tok>>element;
						if(!ulazni_tok || (ulazni_tok.peek() != '\n' && ulazni_tok.peek() != EOF)) {
							ulazni_tok.clear();
							DealocirajMemoriju(elementi, broj_redova);
							throw std::logic_error ("Datoteka sadrzi besmislene podatke");
						} else {
							ulazni_tok>>std::ws;
							elementi[i][j] = element;
						}
					}
				}
			}
			br_kolona = broj_kolona;
			br_redova = broj_redova;
			ulazni_tok.close();
		} else throw std::logic_error ("Datoteka sadrzi besmislene podatke");
	} else {
		std::ifstream ulazni_tok(naziv_datoteke, std::ios::binary);
		if(!ulazni_tok) throw std::logic_error ("Trazena datoteka ne postoji");
        Matrica pomocna(0,0);
		ulazni_tok.read(reinterpret_cast<char*>(&pomocna), sizeof pomocna);
		// try {
		// 	AlocirajMemoriju(br_redova, br_kolona);
		// } catch(...) {
		// 	throw;
		// }
        pomocna.elementi = AlocirajMemoriju(pomocna.br_redova, pomocna.br_kolona);
        for(int i = 0; i < pomocna.br_redova; i++) {
        	for(int j = 0; j < pomocna.br_kolona; j++)
			ulazni_tok.read(reinterpret_cast<char*>(&pomocna.elementi[i][j]), sizeof pomocna.elementi[i][j]);
            if(!ulazni_tok){
                DealocirajMemoriju(pomocna.elementi, pomocna.br_redova);
                throw std::logic_error("Problemi pri citanju datoteke");
            }
		}

        br_redova = pomocna.br_redova;
        br_kolona = pomocna.br_kolona;
        elementi = AlocirajMemoriju(br_redova, br_kolona);
        std::swap(elementi, pomocna.elementi);
	}
}
template <typename TipEl>
Matrica<TipEl> &Matrica<TipEl>::operator =(const Matrica<TipEl> &m)
{
	if(br_redova < m.br_redova || br_kolona < m.br_kolona) {
		TipEl **novi_prostor = AlocirajMemoriju(m.br_redova, m.br_kolona);
		DealocirajMemoriju(elementi, br_redova);
		elementi = novi_prostor;
	} else if(br_redova > m.br_redova)
		for(int i = m.br_redova; i < br_redova; i++) delete elementi[i];
	br_redova = m.br_redova;
	br_kolona = m.br_kolona;
	ime_matrice = m.ime_matrice;
	KopirajElemente(m.elementi);
	return *this;
}
template <typename TipEl>
Matrica<TipEl> &Matrica<TipEl>::operator =(Matrica<TipEl> &&m)
{
	std::swap(br_redova, m.br_redova);
	std::swap(br_kolona, m.br_kolona);
	std::swap(ime_matrice, m.ime_matrice);
	std::swap(elementi, m.elementi);
	return *this;
}
template <typename TipEl>
Matrica<TipEl>& Matrica<TipEl>::operator +=(const Matrica<TipEl> &m)
{

	if(br_redova != m.br_redova || br_kolona != m.br_kolona)
		throw std::domain_error("Matrice nemaju jednake dimenzije!");
	for(int i = 0; i < br_redova; i++)
		for(int j = 0; j < br_kolona; j++)
			elementi[i][j] += m.elementi[i][j];
	return *this;
}
template <typename TipEl>
Matrica<TipEl> &Matrica<TipEl>::operator -=(const Matrica<TipEl> &m)
{

	if(br_redova != m.br_redova || br_kolona != m.br_kolona)
		throw std::domain_error("Matrice nemaju jednake dimenzije!");
	for(int i = 0; i < br_redova; i++)
		for(int j = 0; j < br_kolona; j++)
			elementi[i][j] -= m.elementi[i][j];
	return *this;
}
template <typename TipEl>
Matrica<TipEl> &Matrica<TipEl>::operator *=(double skalar)
{

	for(int i = 0; i < br_redova; i++)
		for(int j = 0; j < br_kolona; j++)
			elementi[i][j] *= skalar;
	return *this;
}
template <typename TipEl>
Matrica<TipEl> &Matrica<TipEl>::operator *=(const Matrica<TipEl> &m)
{
	if(br_kolona != m.br_redova) throw std::domain_error("Matrice nisu saglasne za mnozenje");
	Matrica<TipEl> m3(br_redova, m.br_kolona);
	for(int i = 0; i < br_redova; i++) {
		for(int j = 0; j < m.br_kolona; j++) {
			double suma = 0;
			for(int k = 0; k < m.br_redova; k++) suma += elementi[i][k] * m.elementi[k][j];
			m3.elementi[i][j] = suma;
		}
	}
	*this = m3;
	return *this;
}
template <typename TipEl>
std::istream& operator>>(std::istream &tok, Matrica<TipEl> &m)
{
	for(int i = 0; i < m.br_redova; i++)
		for(int j = 0; j < m.br_kolona; j++) {
			std::cout << m.ime_matrice << "(" << i + 1 << "," << j + 1 << ") = ";
			tok>> m.elementi[i][j];
		}
	return tok;
}
template <typename TipEl>
std::ostream& operator<<(std::ostream &tok, const Matrica<TipEl> &m)
{
	int n = tok.width();
	for(int i = 0; i < m.br_redova; i++) {
		for(int j = 0; j < m.br_kolona; j++)
			tok << std::setw(n) << m.elementi[i][j];
		std::cout << std::endl;
	}
	return tok;
}
template <typename TipEl>
Matrica<TipEl> operator+(const Matrica<TipEl> &m1, const Matrica<TipEl> &m2)
{
	if(m1.br_redova != m2.br_redova || m1.br_kolona != m2.br_kolona)
		throw std::domain_error("Matrice nemaju jednake dimenzije!");
	Matrica<TipEl> m3(m1.br_redova, m1.br_kolona);
	for(int i = 0; i < m1.br_redova; i++)
		for(int j = 0; j < m1.br_kolona; j++)
			m3.elementi[i][j] = m1.elementi[i][j] + m2.elementi[i][j];
	return m3;
}
template<typename TipEl>
Matrica<TipEl> operator -(const Matrica<TipEl> &m1,const Matrica<TipEl> &m2)
{
	if(m1.br_redova != m2.br_redova || m1.br_kolona != m2.br_kolona)
		throw std::domain_error("Matrice nemaju jednake dimenzije!");
	Matrica<TipEl> m3(m1.br_redova, m1.br_kolona);
	for(int i = 0; i < m1.br_redova; i++)
		for(int j = 0; j < m1.br_kolona; j++)
			m3.elementi[i][j] = m1.elementi[i][j] - m2.elementi[i][j];
	return m3;
}
template<typename TipEl>
Matrica<TipEl> operator *(const Matrica<TipEl> &m1,const Matrica<TipEl> &m2)
{
	if(m1.br_kolona != m2.br_redova) throw std::domain_error("Matrice nisu saglasne za mnozenje");
	Matrica<TipEl> m3(m1.br_redova, m1.br_kolona);
	for(int i = 0; i < m1.br_redova; i++) {
		for(int j = 0; j < m2.br_kolona; j++) {
			double suma = 0;
			for(int k = 0; k < m2.br_redova; k++) suma += m1.elementi[i][k] * m2.elementi[k][j];
			m3.elementi[i][j] = suma;
		}
	}
	return m3;
}
template<typename TipEl>
Matrica<TipEl> operator *(const Matrica<TipEl> &m1, double skalar)
{
	Matrica<TipEl> m3(m1.br_redova, m1.br_kolona);
	for(int i = 0; i < m1.br_redova; i++) {
		for(int j = 0; j < m1.br_kolona; j++) {
			m3.elementi[i][j] = skalar * m1.elementi[i][j];
		}
	}
	return m3;
}
template<typename TipEl>
Matrica<TipEl> operator *(double skalar, const Matrica<TipEl> &m1)
{
	auto m3 = m1 * skalar;
	return m3;
}

template<typename TipEl>
void Matrica<TipEl>::SacuvajUTekstualnuDatoteku(std::string naziv_datoteke) const
{
	std::ofstream izlazni_tok(naziv_datoteke);
	if(!izlazni_tok) throw std::logic_error ("Problemi sa upisom u datoteku");
	for(int i = 0; i < br_redova; i++) {
		for(int j = 0; j< br_kolona; j++) {
			if(j != br_kolona - 1) izlazni_tok<<elementi[i][j]>>",";
			else izlazni_tok<<elementi[i][j];
			if(!izlazni_tok) throw std::logic_error ("Problemi sa upisom u datoteku");
		}
		izlazni_tok<<std::endl;
		if(!izlazni_tok) throw std::logic_error ("Problemi sa upisom u datoteku");
	}
	izlazni_tok.close();
}

template<typename TipEl>
void Matrica<TipEl>::SacuvajUBinarnuDatoteku(std::string naziv_datoteke) const
{
	std::ofstream izlazni_tok(naziv_datoteke, std::ios::binary);
	izlazni_tok.write(reinterpret_cast<const char*>(this), sizeof *this);
	for(int i = 0; i < br_redova; i++) {
		for(int j = 0; j < br_kolona; j++) {
			izlazni_tok.write(reinterpret_cast<char*>(&elementi[i][j]), sizeof (TipEl));
		}
	}

	if(!izlazni_tok) throw std::logic_error ("Problemi sa upisom u datoteku");
}

template<typename TipEl>
void Matrica<TipEl>::ObnoviIzTekstualneDatoteke(std::string naziv_datoteke)
{
	std::ifstream ulazni_tok(naziv_datoteke);
	if(!ulazni_tok) throw std::logic_error ("Trazena datoteka ne postoji");

	int broj_kolona = 0;
	int broj_redova = 0;
	bool first = true;
	std::string red;
	while(std::getline(ulazni_tok, red)) {
		int br_zareza;
		ulazni_tok>>std::ws;
		broj_redova++;
		if(first) {
			broj_kolona = std::count(red.begin(), red.end(), ',');
			first = false;
		} else if(!first) {
			br_zareza = std::count(red.begin(), red.end(), ',');
			if(br_zareza != broj_kolona) throw std::logic_error ("Datoteka sadrzi besmislene podatke");
		}

	}
	ulazni_tok.close();
	ulazni_tok.open(naziv_datoteke);
	broj_kolona += 1;
	TipEl **novi_prostor = AlocirajMemoriju(broj_redova, broj_kolona);
	// if(elementi != nullptr) {
	// 	DealocirajMemoriju(elementi, br_redova);
	// 	br_redova = 0;
	// 	br_kolona = 0;
	// 	ime_matrice = 0;
	// }
	//elementi = novi_prostor;
	for(int i = 0; i < broj_redova; i++) {
		for(int j = 0; j < broj_kolona; j++) {
			char znak;
			TipEl element;
			if(j != broj_kolona - 1) {
				ulazni_tok>>element>>znak>>std::ws;
				if(znak != ',') throw std::logic_error ("Datoteka sadrzi besmislene podatke");
				if(!ulazni_tok) {
					ulazni_tok.clear();
					DealocirajMemoriju(novi_prostor, broj_redova);
					throw std::logic_error ("Datoteka sadrzi besmislene podatke");
				} else novi_prostor[i][j] = element;
			} else {
				ulazni_tok>>element;
				if(!ulazni_tok || (ulazni_tok.peek() != '\n' && ulazni_tok.peek() != EOF)) {
					ulazni_tok.clear();
					DealocirajMemoriju(novi_prostor, broj_redova);
					throw std::logic_error ("Datoteka sadrzi besmislene podatke");
				} else {
					ulazni_tok>>std::ws;
					novi_prostor[i][j] = element;
				}
			}
		}
	}
	if(elementi != nullptr) {
		DealocirajMemoriju(elementi, br_redova);
		br_redova = 0;
		br_kolona = 0;
		ime_matrice = 0;
	}
	br_kolona = broj_kolona;
	br_redova = broj_redova;
	elementi = novi_prostor;
	ulazni_tok.close();

}

template<typename TipEl>
void Matrica<TipEl>::ObnoviIzBinarneDatoteke(std::string naziv_datoteke)
{
	std::ifstream ulazni_tok(naziv_datoteke, std::ios::binary);
	if(!ulazni_tok) throw std::logic_error ("Trazena datoteka ne postoji");
	Matrica pomocna(0,0);
	ulazni_tok.read(reinterpret_cast<char*>(&pomocna), sizeof pomocna);
	if(!ulazni_tok){
		DealocirajMemoriju(pomocna.elementi, pomocna.br_redova);
		throw std::logic_error ("Problemi pri citanju datoteke");
	}
	else{
		for(int i = 0; i < pomocna.br_redova; i++){
			for(int j = 0; j < pomocna.br_kolona; j++)
			ulazni_tok.read(reinterpret_cast<char*>(&pomocna.elementi[i][j]), sizeof pomocna.elementi[i][j]);
			if(!ulazni_tok){
				DealocirajMemoriju(pomocna.elementi, pomocna.br_redova);
				throw std::logic_error("Datoteka sadrzi besmislene podatke");
			}
		}
	}
	
	DealocirajMemoriju(elementi, br_redova);
	elementi = AlocirajMemoriju(pomocna.br_redova, pomocna.br_kolona);
	elementi = pomocna.elementi;
	pomocna.elementi = nullptr;
	
}
int main()
{

	//AT4 - testiranje konstruktora za učitavanje iz binarne datoteke
    
    try
    {
        Matrica<int> m0{2, 2};
        for (int i{0}; i < 2; i++)
            for (int j{0}; j < 2; j++)
                m0[i][j] = i + j;
        m0.SacuvajUBinarnuDatoteku("matrica1.DAT");
        Matrica<int> m1("matrica1.DAT", true);
        std::cout << std::setw(6) << m1;
    }
    catch (const std::logic_error& e)
    {
        std::cout << "Izuzetak: " << e.what() << std::endl;
    }
    
    std::cout << std::endl << std::endl;
    
    try
    {
        Matrica<double> m0{2, 2};
        for (int i{0}; i < 2; i++)
            for (int j{0}; j < 2; j++)
                m0[i][j] = i + j + 0.5;
        m0.SacuvajUBinarnuDatoteku("matrica2.DAT");
        Matrica<double> m1("matrica2.DAT", true);
        std::cout << std::setw(6) << m1;
    }
    catch (const std::logic_error& e)
    {
        std::cout << "Izuzetak: " << e.what() << std::endl;
    }


}