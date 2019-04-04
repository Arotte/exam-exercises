/* Solution for the <2015 October> Hungarian IT matura exam's 4th task */

#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <algorithm>

#include <stdlib.h>
#include <time.h>

using namespace std;

bool penzfeldobas() { return (rand()%2); }

int main () {
  srand (time(NULL));
  cout << "1. feladat" << endl << "Penzfeldobas eredmeny: " << (penzfeldobas() ? "Fej" : "Iras") << endl;

  //2
  char tipp;
  char kiserlet = penzfeldobas() ? 'F' : 'I';
  cout << "2. feladat" << endl << "Mi a tippe? (F/I) = "; cin >> tipp;
  cout << "Tipp: " << tipp << ", Kiserlet: " << kiserlet << endl << (tipp == kiserlet ? "On eltalalta" : "Nem talalt!") << endl;

  //3
  char be;
  char elozo_harom[3] = {' '};
  int kimutatas[3] = {0}; //0: osszes, 1:fej, 2:iras
  int egymas_utan_ket_fej = 0;
  int tiszafej_szamok[2] = {0}; //0: mostani, 1:legnagyobb
  int tiszafej_startok[2] = {-1}; //0:mostani, 1:legnagyobb
  int fffi = 0; int ffff = 0;
  char negydobasok[1000][4];

  ifstream ifs("kiserlet.txt");
  while (ifs >> be) {
    ++kimutatas[0];
    if (be == 'F') {
      ++kimutatas[1];
      ++tiszafej_szamok[0];
      if (elozo_harom[2] == 'I') //I-rol F-re
        tiszafej_startok[0] = kimutatas[0];
    }
    else if (be == 'I') {
      ++kimutatas[2];
      if (elozo_harom[0] == 'I' && elozo_harom[1] == 'F' && elozo_harom[2] == 'F') ++egymas_utan_ket_fej;
      if (elozo_harom[2] == 'F') { //F-rol I-re
        if (tiszafej_szamok[0] > tiszafej_szamok[1]) {
          tiszafej_szamok[1] = tiszafej_szamok[0];
          tiszafej_startok[1] = tiszafej_startok[0];
        }
      }
      tiszafej_szamok[0] = 0; tiszafej_startok[0] = -1;
    }

    if (kimutatas[0]%4 == 0 && kimutatas[0] < 4001) {
      negydobasok[kimutatas[0]/4 - 1][3] = be;
      negydobasok[kimutatas[0]/4 - 1][2] = elozo_harom[2];
      negydobasok[kimutatas[0]/4 - 1][1] = elozo_harom[1];
      negydobasok[kimutatas[0]/4 - 1][0] = elozo_harom[0];
      if ( be == 'F' && elozo_harom[0] == 'F' && elozo_harom[1] == 'F' && elozo_harom[2] == 'I') ++fffi;
      if ( be == 'F' && elozo_harom[0] == 'F' && elozo_harom[1] == 'F' && elozo_harom[2] == 'F') ++ffff;
    }
    elozo_harom[0] = elozo_harom[1];
    elozo_harom[1] = elozo_harom[2];
    elozo_harom[2] = be;
  }
  ifs.close();
  cout << "3.feladat" << endl << "A kiserlet " << kimutatas[0] << " dobasbol allt." << endl;
  //4
  cout.precision(2);
  cout << "4. feladat" << endl << "A kiserlet soran a fej relativ gyakorisaga " << fixed <<(double) 100*kimutatas[1]/kimutatas[0] << "% volt." << endl;

  //5
  cout << "5. feladat" << endl << "A kiserlet soran pontosan " << egymas_utan_ket_fej << " alkalommal dobtak ket fejet egymas utan" << endl;

  //6
  cout << "6. feladat" << endl << "A leghosszabb tisztafej sorozat " << tiszafej_szamok[1] << " tagbol allt es a(z) " << tiszafej_startok[1] << ". sorban kezdodik" << endl;

  //7
  ofstream ofs("dobasok.txt");
  ofs << "FFFF: " << ffff << " FFFI: " << fffi << endl;
  for (int i = 0; i<1000; ++i) {
    for (int charI = 0; charI<4; ++charI) {
      ofs << negydobasok[i][charI];
    }
    ofs << " ";
  }
  ofs.close();

  return 0;
}
