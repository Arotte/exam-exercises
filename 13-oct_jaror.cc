/* Solution for the <2013 Oct> Hungarian IT matura exam's 4th task */

#include <fstream>
#include <iostream>
#include <vector>
#include <string>
#include <algorithm>

#include <stdlib.h> //abs

using namespace std;

struct Jarmu {
  int ora, perc, masodperc;
  string rendszam;
};

int ipdiff(int o1, int p1, int m1, int o2, int p2, int m2) {
  return ( abs((o1*3600 + 60*p1 + m1) - (o2*3600 + 60*p2 + m2)) );
}
int mp (int o, int p, int mp) { return (o*3600 + 60*p + mp); }

int main () {
  int munkaido[3] ={0};
  vector<Jarmu> jarmuvek;

  //1
  cout << "1.feladat" << endl << "Adatok beolvasasa" << endl;
  Jarmu jr;
  ifstream ifs("jarmu.txt");
  while (ifs >> jr.ora >> jr.perc >> jr.masodperc >> jr.rendszam) { jarmuvek.push_back(jr); }
  ifs.close();

  //2
  munkaido[0] = jarmuvek.back().ora - jarmuvek.front().ora;
  munkaido[1] = abs(jarmuvek.front().perc - jarmuvek.back().perc);
  munkaido[2] = abs(jarmuvek.back().masodperc - jarmuvek.front().masodperc);
  cout << "2. feladat" << endl << "Az ellenorzok legalabb" << munkaido[0] << " orat " << munkaido[1] << " percet " << munkaido[2] << " masodpercet dolgoztak" <<endl;

  //3
  for (auto it = jarmuvek.begin(); it != jarmuvek.end(); ++it) {
    if (it == jarmuvek.begin()) cout << it->ora << " ora : " << it->rendszam << endl;
    else if (it->ora != (it-1)->ora) cout << it->ora << " ora: " << it->rendszam << endl;
  }

  //4
  int kimutatas[4] = {0}; //0:busz, 1:kamion, 2:motor, 3: osszes tobbi
  for (auto it = jarmuvek.begin(); it != jarmuvek.end(); ++it) {
    if (it->rendszam[0] == 'B') ++kimutatas[0];
    else if (it->rendszam[0] == 'K') ++kimutatas[1];
    else if (it->rendszam[0] == 'M') ++kimutatas[2];
    else ++kimutatas[3];
  }
  cout << "4. feladat" << endl;
  cout << "Busz: " << kimutatas[0] << endl
       << "Kamion: " << kimutatas[1] << endl
       << "Motor: " << kimutatas[2] << endl
       << "Szemely: " << kimutatas[3] << endl;

  //5
  Jarmu leghosszabb_ipk[2];
  int leghosszabb_ip = 0;
  for (auto it = jarmuvek.begin()+1; it != jarmuvek.end(); ++it) {
    if ( ipdiff(it->ora, it->perc, it->masodperc, (it-1)->ora, (it-1)->perc, (it-1)->masodperc) > leghosszabb_ip ) {
      leghosszabb_ip = ipdiff(it->ora, it->perc, it->masodperc, (it-1)->ora, (it-1)->perc, (it-1)->masodperc);
      leghosszabb_ipk[0] = *it;
      leghosszabb_ipk[1] = *(it-1);
    }
  }
  cout << "5. feladat" << endl;
  cout << leghosszabb_ipk[1].ora << ":" << leghosszabb_ipk[1].perc << ":" << leghosszabb_ipk[1].masodperc << " - ";
  cout << leghosszabb_ipk[0].ora << ":" << leghosszabb_ipk[0].perc << ":" << leghosszabb_ipk[0].masodperc;

  //6 //FONTI: EZT AZ ALGORITMIST MEGTANULNI
  string rendszam_be;
  vector<string> lehetseges_rendszamok;
  cout << "6.feladat" << endl << "Basszon ide egy rendszamot: "; cin >> rendszam_be;
  for (auto it = jarmuvek.begin()+1; it != jarmuvek.end(); ++it) {
    for (int char_i = 0; char_i < 7; ++char_i) {
      if (rendszam_be[char_i] != '*') {
        if (it->rendszam[char_i] != rendszam_be[char_i]) {
          break;
        }
      }
      if (char_i == 6) lehetseges_rendszamok.push_back(it->rendszam);
    }
    continue;
  }
  cout << "Lehetseges rendszamok: " << endl;
  for (auto it = lehetseges_rendszamok.begin(); it != lehetseges_rendszamok.end(); ++it) {
    cout << *it << endl;
  }

  //7
  ofstream ofs("vizsgalt.txt");
  int elozo_vege = mp(jarmuvek.front().ora, jarmuvek.front().perc, jarmuvek.front().masodperc) + mp(0,5,0);
  ofs << 0 << jarmuvek.front().ora << " " << jarmuvek.front().perc << " " << jarmuvek.front().masodperc << " " << jarmuvek.front().rendszam << endl;
  for (auto it = jarmuvek.begin()+1; it != jarmuvek.end(); ++it) {
    if ( mp(it->ora, it->perc, it->masodperc) >= elozo_vege ) {
      if (it->ora < 10) ofs << 0 << it->ora << " ";
      else ofs << it->ora << " ";
      if (it->perc < 10) ofs << 0 << it->perc << " ";
      else ofs << it->perc << " ";
      if (it->masodperc < 10) ofs << 0 << it->masodperc << " ";
      else ofs << it->masodperc << " ";
      ofs << it->rendszam << endl;
      elozo_vege = mp(it->ora, it->perc, it->masodperc) + mp(0,5,0);
    }
  }
  ofs.close();

  return 0;
}
