//3.
#include <bits/stdc++.h>
using namespace std;

int main() {
	cout << "CILINDAR JE ISTO STO I STAZA!!!!!! Ako u tekstu ne pise staza vec cilindar....\n\n\n";
	int brojGlava;
	cout << "Broj glava: ";
	cin >> brojGlava;
	int stazaPoGlavi;
	cout << "Staza po glavi: ";
	cin >> stazaPoGlavi;

	int poc, kraj, sek;

	vector<pair<pair<int, int>, int>> stazeSektori;

	do {
		cout << "Pocetak i kraj staze: ";
		cin >> poc >> kraj;
		cout << "Broj sektora za stazu: ";
		cin >> sek;
		auto temp = make_pair(poc, kraj);
		stazeSektori.emplace_back(temp, sek);
		cout << endl;
	} while (kraj != stazaPoGlavi-1);

	int logickiSektor;
	cout << "\nLogicki sektor: ";
	cin >> logickiSektor;

	int sektorVel;
	cout << "\nVelicina sektora u bajtima: ";
	cin >> sektorVel;

	vector<int> zone;
	for (const auto &ss: stazeSektori) {
		zone.push_back((ss.first.second - ss.first.first + 1)* ss.second);
	}

	int ukupnoSektora = accumulate(zone.begin(), zone.end(), 0);

	const int GLAVA = logickiSektor / ukupnoSektora;
	const int OSTATAK = logickiSektor % ukupnoSektora;

	int zona = 0;
	int tempSuma = 0;

	for (; zona < zone.size(); zona++) {
		tempSuma += zone[zona];
		if (OSTATAK < tempSuma) break;
	}

//	zona++;
	const int ZONA = zona;

	int relativnaPoz = OSTATAK;

	zona--;

	for (; zona >= 0; zona--) relativnaPoz -= zone[zona];

	int nekaTemp1 = relativnaPoz / stazeSektori[ZONA].second;
	int nekaTemp2 = relativnaPoz % stazeSektori[ZONA].second;

	const int STAZA = stazeSektori[ZONA].first.first + nekaTemp1;
	const int SEKTOR = nekaTemp2;

	cout << "Glava: " << GLAVA << "\t Staza: " << STAZA << "\t Sektor: " << SEKTOR << endl << endl;

	cout << "Ukuni kapacitet u bajtima je: " << brojGlava * ukupnoSektora * sektorVel << endl << endl;
}
//2.
// #include <bits/stdc++.h>
// using namespace std;

// int main() {
// 	int p;
// 	vector<int> c;

// 	cout << "Pocetni cilindar: ";
// 	cin >> p;
	

// 	cout << "Cilindri [MOZE I RAZMAK I , IZMEDJU SVAKOG] [-1 ZA KRAJ]: ";
	
// 	int s = 0;

// 	c.push_back(p);
// 	for (;;) {
// 		int u;
// 		cin >> u;
// 		if (u < 0) break;
// 		if (cin.peek() == ',')
// 			cin.get();
// 		c.push_back(u);
// 	}

// 	for (int i = 1; i < c.size(); i++) {
// 		cout << "Trenutna pozicija: " << c[i-1] << endl;
// 		s += abs(c[i]-c[i-1]);
// 	}
// 	cout << "Trenutna pozicija: " << c[c.size() - 1] << endl << endl;
// 	cout << "\nRez: " << s << endl << endl;
// }
