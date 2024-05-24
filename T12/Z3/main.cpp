#include <iostream>
#include <vector>
#include <string>
enum Dani {Ponedjeljak, Utorak, Srijeda, Cetvrtak, Petak, Subota, Nedjelja};

std::ostream &operator <<(std::ostream &tok, Dani d)
{
	std::vector<std::string> dani{"Ponedjeljak", "Utorak", "Srijeda", "Cetvrtak", "Petak", "Subota", "Nedjelja"};
	tok<<dani[d];
	return tok;
}

Dani &operator++(Dani &d)
{
	return d = Dani((int(d) +1) % 7);
}

Dani operator ++(Dani &d, int)
{
	auto pomocna = d;
	++d;
	return pomocna;
}
int main ()
{
	//enum Dani {Ponedjeljak, Utorak, Srijeda, Cetvrtak, Petak, Subota, Nedjelja};
	// Dani d = Srijeda;
	// std::cout<<d;
	for(Dani d = Ponedjeljak; d <= Nedjelja; d++) {
		std::cout << d << std::endl;
		if(d == Nedjelja) break;
	}
	return 0;
}
