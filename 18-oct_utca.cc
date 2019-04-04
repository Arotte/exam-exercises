#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <algorithm>

using namespace std;

struct Telek { int oldal; int hossz; char szin; int hazszam; };

int main () {
	vector<Telek> utca;
	
	//1 //FONTOS: EZ A HAZSZAM MEGALLAPITOS RESZ ELEG GECI. ATNEZNI JOBBAN, HATEKONYABB ALGORITMUST KIDOLGOZNI RA
	bool elso_paros, elso_paratlan = true;
	int utolso_hsz[2] = {0};
	Telek tk_buff;
	ifstream ifs("kerites.txt");
	while (ifs >> tk_buff.oldal) {
		if (elso_paros && tk_buff.oldal == 0) { tk_buff.hazszam = 2; utolso_hsz[0] = 2; }
		else if (elso_paratlan && tk_buff.oldal == 1) { tk_buff.hazszam = 1; utolso_hsz[1] = 1; }
		
		if (!elso_paros && tk_buff.oldal == 0) { tk_buff.hazszam = utolso_hsz[0] + 2; utolso_hsz[0] += 2; }
		else if (!elso_paratlan && tk_buff.oldal == 1) { tk_buff.hazszam = utolso_hsz[1]+2; utolso_hsz[1] += 2; }
		
		if (tk_buff.oldal == 0) { elso_paros = false; }
		else if (tk_buff.oldal == 1) { elso_paratlan = false; }
		
		ifs >> tk_buff.hossz >> tk_buff.szin;
		utca.push_back(tk_buff);
	}
	ifs.close();
	//FOR DEBUG:
	for(auto it = utca.begin(); it != utca.end(); ++it) { cout << it->oldal << " " << it->hossz << " " << it->szin<<" "<<it->hazszam << endl; }
	
	//2
	cout << "2. feladat" << endl << "Az utcaban osszesen " << utca.size() << " telket adtak el." << endl;
	
	//3
	string oldal_buff = utca.back().oldal ? "paratlan" : "paros" ;
	cout << "3. feladat" << endl << "Az uccso eladott telek a " << oldal_buff << " oldalon van." << endl << "Hazszama: " << utca.back().hazszam << endl;
	
	//4
	cout << "4.feladat" << endl;
	for (auto it = utca.begin(); it != utca.end(); ++it) {
		if ( (it+1)->szin == it->szin && (it+1)->oldal == 1  && (it->szin != '#' && it->szin != ':')) {
			cout << "A szomszedossal egyezik a kerites szine: " << it->hazszam << endl;
			break;	
		}	
	}
	
	//5 
	int hazszam_be;
	cout << "5. feladat" << endl << "Hazszam: ";
	cin >> hazszam_be;
	
	//5a,b //FONTI: TUTI VAN ENNEL EGYSZERUBB MODSZER, PL A VEKTOR OSZTALYNAK VALAMI JO KIS FIND FV.-E
	//FONTOS: WOAH, EBBOL A FELADATBOL ELEG GECISOKAT TANULTAM
	vector<Telek> egy_oldal;
	vector<Telek>::iterator hol;
	int oldal = hazszam_be%2 ? 1 : 0;
	for (auto it = utca.begin(); it != utca.end(); ++it) if (it->oldal == oldal) egy_oldal.push_back(*it);
	for (auto it = egy_oldal.begin(); it != egy_oldal.end(); ++it) { if (it->hazszam == hazszam_be) {hol = it; break;} }
	
	cout << "A kerites szine/allapota: " << hol->szin << endl;
	cout << "Egy lehetseges szin: ";
	for (char c = 'A'; c <= 'Z'; ++c) {
		if (c != hol->szin && c != (hol-1)->szin && c != (hol+1)->szin) {
			cout << c << endl;
			break;
		}
	}
	
	//6 //FONTOS EZ A FELADAT GECI SOK IDOT ELVETT. SZEP ALGORITMUST IGENYEL, SOK IDO.
	vector<Telek> paratlan_oldal;
	for (auto it = utca.begin(); it != utca.end(); ++it) { if (it->oldal == 1) paratlan_oldal.push_back(*it); }
	ofstream ofs("utcakep.txt");
	for (int sor = 0; sor < 2; ++sor) {
		for (auto telek = paratlan_oldal.begin(); telek != paratlan_oldal.end(); ++telek) {
			if (sor == 0) {
				for (int karakter = 0; karakter < telek->hossz; ++karakter)
					ofs << telek->szin;
			} else {
				int meddig;
				if ( (telek->hazszam)/10 < 1) { meddig = telek->hossz; //FONTOS: TUDD HOGY MI A FASZT CSINAL A % OPERATOR MERT EGY CSOMO IDOT ELBASZOL IGY!!
				} else if ( telek->hazszam/10 >= 1 && telek->hazszam/10 < 10) { meddig=telek->hossz-1;
				} else { meddig = telek->hossz-2; }
				
				for (int karakter = 0; karakter < meddig; ++karakter) {
					if (karakter == 0) ofs << telek->hazszam;
					else ofs << " ";
				}
			}
		}
		ofs << endl;
	}
 	ofs.close();
	
	return 0;	
}