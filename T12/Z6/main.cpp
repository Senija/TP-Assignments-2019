#include <iostream>
#include <iomanip>
#include <cstring>
#include <stdexcept>
#include <new>
#include <string>
#include <sstream>
template <typename TipEl>
class Matrica
{
	int br_redova, br_kolona;
	TipEl **elementi;
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
	Matrica(int br_redova, int br_kolona, char ime = 0);
	Matrica(const Matrica &m);
	Matrica(Matrica &&m);
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
					}
					else s.push_back('}');
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
	TipEl **elementi = new TipEl*[br_redova] {};
	try {
		for(int i = 0; i < br_redova; i++) elementi[i] = new TipEl[br_kolona];
	} catch(...) {
		DealocirajMemoriju(elementi, br_redova);
		throw;
	}
	return elementi;
}
template <typename TipEl>
void Matrica<TipEl>::DealocirajMemoriju(TipEl **elementi, int br_redova)
{
	for(int i = 0; i < br_redova; i++) delete[] elementi[i];
	delete[] elementi;
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
int main()
{
	// AT3 Testiranje operatora () i izuzetka u slučaju neispravnog indeksa
	try {
		Matrica<int> a(2, 3, 'a');
		a(0,0) = 1;
		a(0,1) = 2;
		a(0,2) = 3;
		a(1,0) = 4;
		a(1,1) = 5;
		a(1,2) = 7;
		Matrica<int> b(2, 3, 'b');
		b(0,0) = 1;
		b(0,1) = 2;
		b(0,2) = 3;
		b(1,0) = 4;
		b(1,1) = 5;
		b(1,2) = 6;
	} catch(std::bad_alloc) {
		std::cout << "Nema dovoljno memorije!\n";
	} catch(std::domain_error e) {
		std::cout << e.what();
	} catch(std::range_error e) {
		std::cout << e.what();
	}
	return 0;
}
