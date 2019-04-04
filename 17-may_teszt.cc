#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <algorithm>

using namespace std;

string helyes;

struct Gyerek {
	string kod;
	string valaszok;
	int pontszam;
};

bool smallerFunct(Gyerek gy1, Gyerek gy2) { return (gy1.pontszam > gy2.pontszam); }

int main() {
	vector<Gyerek> db;

	//1
	fstream fin("forrasok/valaszok.txt");
	string be;
	Gyerek gybe;
	fin >> helyes;
	while (fin >> be) {
		gybe.kod = be;
		fin >> be;
		gybe.valaszok = be;
		db.push_back(gybe);

	}
	fin.close();

	//2
	cout << endl << "A versenyen " << db.size() << " versenzo indult." << endl;

	//3
	string azbe;
	string azbe_valasz;
	cout << "1. feladat:"<< endl<<"A versenyzo azonositoja = ";
	cin >> azbe;
	for (auto it = db.begin(); it != db.end(); ++it){
		if (it->kod == azbe) {
			cout << endl << "A versenyzo valasza: " << it->valaszok << endl;
			azbe_valasz = it->valaszok;
		}
	}

	//4
	cout << "4. feladat:"<< endl << helyes << " (helyes valasz)" << endl;
	for(int i = 0; i < 14; ++i) {
		if (helyes[i] == azbe_valasz[i]) {
			cout << "+";
		} else {
			cout << " ";
		}
	}
	cout << "(a versenzo valaszai)" << endl;

	//5-6
	int feladat = 0;
	int jogyerekek = 0;
	ofstream ofs("pontok.txt");
	cout << "5. feladat" << endl << "A feladat sorszama = ";
	cin >> feladat;
	cout << endl;
	for (auto it = db.begin(); it != db.end(); ++it) {
		if (it->valaszok[feladat-1] == helyes[feladat-1]) {
			++jogyerekek;
		}

		int pontszam = 0;
		for (int i = 0; i < 14; ++i) {
			if (helyes[i] == it->valaszok[i]) {
				if (i >= 0 && i <= 4) { //3pont
					pontszam += 3;
				} else if (i >= 5 && i <=9) { //4pont
					pontszam += 4;
				} else if (i >= 10 && i <=12) { //5pont
					pontszam += 5;
				} else if (i == 13) { //6pont
					pontszam += 6;
				}
			}
		}
		it->pontszam = pontszam;
		ofs << it->kod << " " << pontszam << endl;
	} //db scan end
	ofs.close();
	double szex = 100*(jogyerekek/db.size());
	cout << "A feladatra " << jogyerekek << " fo, a versenyzok " << szex << " %-a adott helyes valaszt." << endl;

	//7
	sort (db.begin(), db.end(), smallerFunct);
	int tro = 1;
	for (int i = 0; i < 500; ++i) {
		cout << tro << ". dij (" << db[i].pontszam << "pont): " << db[i].kod << endl;
		if (tro == 3) break;
		if (db[i].pontszam > db[i+1].pontszam) ++tro;
	}

	return 0;
}
