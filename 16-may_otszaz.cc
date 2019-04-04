/* Solution for the <2016 May> Hungarian IT matura exam's 4th task */

#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <algorithm>

using namespace std;

int ertek(int darabszam) {
  int ar = 0;
  if (darabszam >= 3) {
    ar += 950;
    for (int i=0; i<darabszam-2; ++i) ar += 400;
  }
  else if (darabszam == 2) ar += 950;
  else ar += 500;

  return ar;
}

void kimutatas(vector<string>& vasarlas,
               vector<string>& arucikkek,
               vector<int>& darabszamok)
{
  for (auto it = vasarlas.begin(); it != vasarlas.end(); ++it) {
    vector<string>::iterator strit = find(arucikkek.begin(), arucikkek.end(), *it);
    if (strit == arucikkek.end()) {
      arucikkek.push_back(*it);
      darabszamok.push_back(0);
      ++(darabszamok.back());
    } else {
      darabszamok[distance(arucikkek.begin(), strit)] += 1;
    }
  }
}

int main () {
  vector<vector<string>> db;
  int fizetesek = 0;

  //1-2
  string be;
  vector<string> bekosar;
  ifstream ifs("penztar.txt");
  while (getline(ifs, be)) {
    //cout << be << endl;
    if (be == "F") {
      ++fizetesek;
      db.push_back(bekosar);
      bekosar.clear();
    } else {
      bekosar.push_back(be);
    }
  }
  ifs.close();
  cout << "2. feladat: " << endl << "A penztarnal fizettek: " << fizetesek << endl;

  //3
  cout << "3. feladat: " << endl << "Az elso vasarlo " << db[0].size() << " arucikket vasarolt." << endl;

  //4
  int sorszam, darabszam;
  string arucikk = "";
  string bbe = "";

  cout << "4. feladat: " << endl << "Basszaon ide egy vasarlas sorszamot: ";
  getline(cin, bbe);
  sorszam = stoi(bbe);
  cout << endl << "Basszaon ide egy arucikk nevet:\n";
  getline(cin, arucikk);
  cout << endl << "Basszaon ide egy vasarolt darabszamot: ";
  getline(cin, bbe);
  darabszam = stoi(bbe);

  //5
  int elso = -1;
  int masodik = 0;
  int mennyi = 0;

  cout << "5. feladat: " << endl;
  for (auto it = db.begin(); it != db.end(); ++it) {
    vector<string>::iterator strit = find(it->begin(), it->end(), arucikk);
    if (strit != it->end()) {
      ++mennyi;
      if (elso == -1) { elso = distance(db.begin(), it) + 1; }
      else { masodik = distance(db.begin(), it) + 1; }
    }
  }
  cout << "Az elso vasarlas szorszama: " << elso << endl
       << "Az utolso vasarlas sorszama: " << masodik << endl
       << "Ennyiszer vettek belole: " << mennyi << endl;

  //6
  cout << "6. feladat" << endl
       << darabszam << " vetelekor fizetendo: "
       << ertek(darabszam) << endl;

  //7
  vector<string> vasarlas = db[sorszam-1];
  vector<string> arucikkek;
  vector<int> darabszamok;
  kimutatas(vasarlas, arucikkek, darabszamok);
  for (auto it = arucikkek.begin(); it != arucikkek.end(); ++it) {
    cout << darabszamok[distance(arucikkek.begin(), it)]
         << " db " << *it << endl;
  }

  //8
  ofstream ofs("osszegek.txt");
  for (auto it = db.begin(); it != db.end(); ++it) {
    ofs << distance(db.begin(), it) + 1 << ": ";
    vector<int> dbs;
    vector<string> auck;
    kimutatas(*it, auck, dbs);
    int money = 0;

    for (auto itt = dbs.begin(); itt != dbs.end(); ++itt) money += ertek(*itt);
    ofs << money << endl;
  }
  ofs.close();

  return 0;
}
