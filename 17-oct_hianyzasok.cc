#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <algorithm>

using namespace std;

struct Tanulo {
	string vnev, knev, hianyzasok;
	int hianyzas_count = 0;
};
struct TanuloStr {string nev = " "; int h = 0;};

struct NapiHianyzas {
	int honap, nap;
	string melyiknap;
	vector<Tanulo> tanulok;
};

int igazolt, igazolatlan = 0;

//4 FONTOS: EZT AZ ALGORITMUST ERDMES LENNE FEJBOL TUDNI
string hetnapja(int honap, int nap) {
	string napnev[] = {"vasarnap", "hetfo", "kedd", "szerda", "csutortok", "pentek", "szombat"};
	int napszam[] = {0, 31, 59, 90, 120, 151, 181, 212, 243, 273, 304, 335};
	int napsorszam = (napszam[honap-1]+nap) % 7;
	string hetnapja = napnev[napsorszam];
	return hetnapja;
}
bool how (TanuloStr t1, TanuloStr t2) {return (t1.h > t2.h);}

int main() {
	vector<NapiHianyzas> db;

	//1 //	gecoo ez nagyon sok idot elvettt // EGY KIBASZOTT ORAT VETT IGYENYBE EZ A FELADAT!!
	ifstream ifs("naplo.txt");
	NapiHianyzas nh;
	string be_str;
	ifs >> be_str;
	ifs >> nh.honap >> nh.nap;
	while (ifs >> be_str) {
		if (be_str == "#") {
			db.push_back(nh);
			nh.tanulok.clear(); //FONTOS: NEM ART NEHA CLEARELNI A GLOBALISAN HASZNALT VEKTOROKAAAAT
			ifs >> nh.honap >> nh.nap;
			nh.melyiknap = hetnapja(nh.honap, nh.nap);
		} else {
			Tanulo to; to.vnev = be_str;
			ifs >> to.knev >> to.hianyzasok;
			//3-as feladathoz:
			for (auto it = to.hianyzasok.begin(); it != to.hianyzasok.end(); ++it) {
				if (*it == 'X') { ++igazolt; ++to.hianyzas_count;}
				else if (*it == 'I') {++igazolatlan; ++to.hianyzas_count;}
			}
			nh.tanulok.push_back(to);
		}
	}
	db.push_back(nh);
	//for (auto it = db.begin(); it != db.end(); ++it) { cout << (it->tanulok).back().vnev <<endl; }
	ifs.close();

	//2
	int hiany = 0;
	for (auto it = db.begin(); it != db.end(); ++it) { hiany += (it->tanulok).size(); }
	cout << "2. feladat" << endl << "Hianyzast rogzito sorok szama: " << hiany <<endl;

	//3
	cout << "3. feladat" << endl << "Igazolt: " << igazolt << endl << "Igazolatlan: " << igazolatlan << endl;

	//5
	int datum[2] = {0};
	cout << "5.feladat" << endl << "Datum: ";
	cin >> datum[0] >> datum[1];
	cout << "Het napja: " << hetnapja(datum[0], datum[1]) << endl;

	//6
	string napbe; int sorszambe, geci = 0;
	cout << "6.feladat" << endl << "Nap Sorszam : "; cin >> napbe >> sorszambe; cout << endl;
	for (auto it = db.begin(); it != db.end(); ++it) {
		if (it->melyiknap == napbe ) {
			for (auto tanIt = (it->tanulok).begin(); tanIt != (it->tanulok).end(); ++tanIt) {
					if ((tanIt->hianyzasok)[sorszambe-1] == 'I' || (tanIt->hianyzasok)[sorszambe-1] == 'X') ++geci;
			}
		}
	}
	cout << "Ekkor osszesen " << geci << " hianyzas tortent." << endl;

	//7 //FONTI: EDDIG KB 120 PERC!!!!!!
	vector<TanuloStr> kimutatas;
	TanuloStr start;
	start.nev = db[0].tanulok[0].vnev + " " + db[0].tanulok[0].knev;
	start.h = db[0].tanulok[0].hianyzas_count;
	kimutatas.push_back(start);
	for (auto it = db.begin()+1; it != db.end(); ++it) {
		for (auto itit = (it->tanulok).begin(); itit != (it->tanulok).end(); ++itit) {
			bool noShitFound = false;
			for (auto kimIt = kimutatas.begin(); kimIt != kimutatas.end(); ++kimIt) {
				if (kimIt->nev == (itit->vnev + " " + itit->knev) ) {
					kimIt->h += itit->hianyzas_count;
					break;
				} else if (kimIt == kimutatas.end()-1) {
					noShitFound = true;
					start.nev = itit->vnev + " " + itit->knev;
					start.h = itit->hianyzas_count;
					break;
				}
			}
			if (noShitFound) {
				kimutatas.push_back(start);
			}
		}
	}
	sort(kimutatas.begin(), kimutatas.end(), how);
	cout << "7.feladat" << endl << "Legtobbet hianyzott gecik: " << endl << kimutatas.begin()->nev << endl;
	for (auto kimIt = kimutatas.begin()+1; kimIt != kimutatas.end(); ++kimIt) { if (kimIt->h == kimutatas.begin()->h) cout << kimIt->nev << endl;}

	return 0;
}
