/* Solution for the <2012 May> Hungarian IT matura exam's 4th task */

#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <algorithm>

using namespace std;

struct Fuvar { int nap; int sorszam; int km; };

bool bigger (Fuvar f1, Fuvar f2) { return (f1.nap < f2.nap); }
bool bigger2 (Fuvar f1, Fuvar f2) { return (f1.sorszam < f2.sorszam); }
bool bigger3 (int i1, int i2) { return (i1 < i2); }
int dijazas (int km) {
  if (km == 1 || km ==2) return 500;
  else if (km >= 3 && km <= 5) return 700;
  else if (km >= 6 && km <= 10) return 900;
  else if (km >= 11 && km <= 20) return 1400;
  else if (km >= 21 && km <= 30) return 2000;
  else return 0;
}

int main() {
  vector<Fuvar> db;

  //1
  int be;
  ifstream ifs("tavok.txt");
  while (ifs >> be) {
    Fuvar fv;
    fv.nap = be;
    ifs >> fv.sorszam;
    ifs >> fv.km;
    db.push_back(fv);
  }
  ifs.close();

  sort(db.begin(), db.end(), bigger);
  vector<Fuvar>::iterator tempIt = db.begin();
  for (auto it = db.begin(); it != db.end(); ++it) {
    if ( (it+1)->nap != it->nap) {
      sort (tempIt, it+1, bigger2);
      tempIt = it+1;
    }
  }
  cout << "2.feladat:" << endl << "Legelso ut: " << db.front().km << endl;
  cout << "3. feladat: " << endl << "Utolso ut: " << db.back().km << endl;

  //4
  cout << "4. feladat" << endl;
  for (auto it = db.begin(); it != db.end(); ++it)
    if ((it->nap)+2 == (it+1)->nap) { cout << "A " << (it->nap)+1 << ". napon nem dolgozott" << endl; }

  //5
  cout << "5. feladat" << endl;
  int kimutatas[7] = {0}; int max[2] = {0};
  for (auto it = db.begin(); it != db.end(); ++it)
    if (it->km > kimutatas[(it->nap)-1]) kimutatas[(it->nap)-1] = it->km;
  for (int i = 0; i < 7; ++i) { if (kimutatas[i] > max[0]) {max[0] = kimutatas[i]; max[1] = i+1; } }
  cout << "A legtobb ut a het " << max[1] << ". napjan volt" << endl;

  //6
  cout << "6. feladat" << endl;
  int kim[7] = {0};
  for (auto it = db.begin(); it != db.end(); ++it) { kim[(it->nap)-1] += it->km; }
  for (int i=0; i<7; ++i) cout << i+1 << ". nap: " << kim[i] << " km." << endl;

  //7
  int bebe;
  cout << "7. feladat" << endl << "Adjon meg egy tavot: "; cin >> bebe; cout << endl << "Ber: " << dijazas(bebe) << endl;

  //8
  int osszesMoney = 0;
  ofstream ofs2("dijazas.txt");
  for (auto it = db.begin(); it != db.end(); ++it) {
    ofs2 << it->nap << ". nap " << it->sorszam << ". ut: " << dijazas(it->km) << " Ft" <<endl;
    osszesMoney +=  dijazas(it->km);
  }
  ofs2.close();

  //9
  cout << "9.feladat" << endl << "Heti money: " << osszesMoney << endl;

  return 0;
}
