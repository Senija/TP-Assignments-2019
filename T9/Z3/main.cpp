#include <iostream>
#include <cmath>
class Vektor3d
{
	double koordinate[3];
	mutable int brojac_ispisa = 0;
public:
	void Postavi(double x, double y, double z)
	{
		koordinate[0] = x;
		koordinate[1] = y;
		koordinate[2] = z;
	}
	void Ocitaj(double &x, double &y, double &z) const
	{
		x = koordinate[0];
		y = koordinate[1];
		z = koordinate[2];
	}
	void Ispisi() const
	{
		brojac_ispisa++;
		std::cout<< "{"<< koordinate[0] << "," << koordinate[1] << "," << koordinate[2] <<"}";
	}
	int DajBrojIspisa() const{
		return brojac_ispisa;
	}
	double DajX() const
	{
		return koordinate[0];
	}
	double DajY() const
	{
		return koordinate[1];
	}
	double DajZ() const
	{
		return koordinate[2];
	}
	Vektor3d &PostaviX (double x)
	{
		koordinate[0] = x;
		return *this;
	}
	Vektor3d &PostaviY (double y)
	{
		koordinate[1] = y;
		return *this;
	}
	Vektor3d &PostaviZ (double z)
	{
		koordinate[2] = z;
		return *this;
	}
	double DajDuzinu() const
	{
		return std::sqrt( koordinate[0]*koordinate[0] + koordinate[1]*koordinate[1] + koordinate[2]*koordinate[2]);
	}
	Vektor3d &PomnoziSaSkalarom(double s)
	{
		koordinate[0] *= s;
		koordinate[1] *= s;
		koordinate[2] *= s;
		return *this;
	}
	Vektor3d &SaberiSa(const Vektor3d &v)
	{
		koordinate[0] += v.koordinate[0];
		koordinate[1] += v.koordinate[1];
		koordinate[2] += v.koordinate[2];
		return *this;
	}
	friend Vektor3d ZbirVektora(const Vektor3d &v1, const Vektor3d &v2);
};
Vektor3d ZbirVektora(const Vektor3d &v1, const Vektor3d &v2)
{
	Vektor3d v3;
	v3.koordinate[0] = v1.koordinate[0] + v2.koordinate[0];
	v3.koordinate[1] = v1.koordinate[1] + v2.koordinate[1];
	v3.koordinate[2] = v1.koordinate[2] + v2.koordinate[2];
	return v3;
}
int main ()
{
	// Vektor3d v1;
	// v1.Postavi(3, 4, 5);
	// v1.PostaviX(7);
	// v1.Ispisi();
	// Vektor3d v2;
	// v2.Postavi(2, 2, 2);
	// std::cout<<std::endl<<"|v1| = "<<v1.DajDuzinu()<<std::endl<< "|v2| = "<<v2.DajDuzinu();
	// auto v3 = ZbirVektora(v1, v2);
	// std::cout<<std::endl;
	// v3.Ispisi();
	return 0;
}
