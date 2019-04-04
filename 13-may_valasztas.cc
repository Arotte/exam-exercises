/* Solution for the <2013 May> Hungarian IT matura exam's 4th task */

#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <algorithm>

using namespace std;
bool bigger (int a, int b) { return (a<b); }

struct Jelolt {
  int valasztoKer, szavazatok;
  string nev[2], part;
};

int main() {
  vector<Jelolt> valasztas;

  //1
  ifstream ifs("szavazatok.txt");
  int be;
  while (ifs >> be) {
    Jelolt jl;
    jl.valasztoKer = be;
    ifs >> jl.szavazatok;
    ifs >> jl.nev[0];
    ifs >> jl.nev[1];
    ifs >> jl.part;
    valasztas.push_back(jl);
  }
  ifs.close();

  //2
  cout <<"2.feladat"<<endl << "A kepviselojelolti valasztason osszesen " << valasztas.size() << " emberke indult." << endl;

  //3
  string vezetek, uto;
  cout <<"3. feladat" << endl << "Bassz ide egy nevet te geci: ";
  cin >> vezetek >> uto;
  for (auto it = valasztas.begin(); it != valasztas.end(); ++it) {
    if (it->nev[0] == vezetek && it->nev[1] == uto) {
      cout << endl << "Ennyi szavazatot kapott " << vezetek << " " << uto << " : " << it->szavazatok << endl;
      break;
    } else if (it == valasztas.end()-1) {
      cout << "Noope" << endl;
    }
  }

  //4
  cout << "4. feladat" <<endl;
  int count = 0;
  for (auto it = valasztas.begin(); it != valasztas.end(); ++it)
    count += it->szavazatok;
  cout << "A valasztason " << count <<" emberke, a jogosultak ";
  cout.precision(2);
  cout << fixed << (double) 100*count/12345<<" %-a vett reszt." << endl;

  //5
  cout << "5. feladat" << endl;
  int kimutatas[5] = {0};
  for (auto it = valasztas.begin(); it != valasztas.end(); ++it) {
    if (it->part == "GYEP") ++kimutatas[0];
    else if (it->part == "HEP") ++kimutatas[1];
    else if (it->part == "TISZ") ++kimutatas[2];
    else if (it->part == "ZEP") ++kimutatas[3];
    else if (it->part == "-") ++kimutatas[4];
  }
  cout.precision(2);
  cout << "GYEP: " << fixed <<  (double) (100*kimutatas[0])/valasztas.size() << endl
       << "HEP: " << fixed << (double) (100*kimutatas[1])/valasztas.size() << endl
       << "TISZ: " << fixed << (double) (100*kimutatas[2])/valasztas.size() << endl
       << "ZEP: " << fixed << (double) (100*kimutatas[3])/valasztas.size() << endl
       << "FUGGETLEN: " << fixed << (double) (100*kimutatas[4])/valasztas.size() << endl;

  //6
  cout << "6. feladat" << endl;
  vector <int> temp;
  for (auto it = valasztas.begin(); it != valasztas.end(); ++it) { temp.push_back(it->szavazatok); }
  sort(temp.begin(), temp.end(), bigger);
  for (auto it = valasztas.begin(); it != valasztas.end(); ++it) {
    if (it->szavazatok == temp.back()) {
      cout << it->nev[0] << " " <<it->nev[1] << " ";
      if (it->part == "-") cout << "fuggetlen";
      else cout << it->part;
      cout << endl;
    }
  }

  Jelolt kerkimutatas[8];
  int kerki_int[8] = {0}; //todo: no need for this array
  for (auto it = valasztas.begin(); it != valasztas.end(); ++it) {
    if ( it->szavazatok >= kerki_int[it->valasztoKer-1] ){
      kerki_int[it->valasztoKer-1] = it->szavazatok;
      kerkimutatas[it->valasztoKer-1] = *it;
    }
  }
  ofstream ofs("kepviselok.txt");
  for (int i=0; i<8; ++i) {
    ofs << i+1 << " : "<< kerkimutatas[i].nev[0] << " " << kerkimutatas[i].nev[1];
    if (kerkimutatas[i].part == "-") ofs << " fuggetlen" << endl;
    else ofs <<" " <<kerkimutatas[i].part << endl;
  }
  ofs.close();

  return 0;
}
