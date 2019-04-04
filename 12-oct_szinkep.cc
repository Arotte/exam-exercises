/* Solution for the <2012 October> Hungarian IT matura exam's 4th task */

#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>
#include <string>
#include <stdlib.h> //abs

using namespace std;

int MAGASSAG = 50;
int SZELESSEG = 50;

class Pixel {
public:
  int r,g,b;
  bool operator==(const Pixel &p2) {
    return ( this->r == p2.r && this->g == p2.g &&  this->b == p2.b);
  }
  bool operator!=(const Pixel &p2) {
    return ( this->r != p2.r || this->g != p2.g ||  this->b != p2.b );
  }
};

int main () {
  vector<vector<Pixel>> kep;

  cout << "1. feladat" << endl << "Kep beolvasasa" << endl;
  ifstream ifs("kep.txt");
  Pixel px;
  vector<Pixel> sor;
  for (int i = 0; i < MAGASSAG; ++i) {
    for (int j = 0; j < SZELESSEG; ++j) {
      ifs >> px.r >> px.g >> px.b;
      sor.push_back(px);
    }
    kep.push_back(sor);
    sor.clear();
  }
  ifs.close();

  //2
  Pixel rgb_be;
  bool megtalalt = false;
  cout << "2. feladat" << endl << "Bassz ide egy kodot (r g b) = ";
  cin >> rgb_be.r >> rgb_be.g  >> rgb_be.b;

  for (auto it = kep.begin(); it != kep.end(); ++it) {
    vector<Pixel>::iterator vanekod = find(it->begin(), it->end(), rgb_be);
    if (vanekod != it->end()) {
      cout << "Jap, letezik" << endl;
      break;
    } else if (vanekod == it->end() && it == kep.end()-1) {
      cout << "Nope, nem letezik" << endl;
    }
  }

  //3
  Pixel kerdeses_szin = kep[34][7];
  int sorban_hanyszor = 0;
  int oszlopban_hanyszor = 0;
  for (int i = 0; i < 50; ++i) {
    if (kep[34][i] == kerdeses_szin) ++sorban_hanyszor;
    if (kep[i][7] == kerdeses_szin) ++oszlopban_hanyszor;
  }
  cout << "3. feladat" << endl << "Oszlopban: " << oszlopban_hanyszor << " Sorban: " << sorban_hanyszor << endl;

  //4
  Pixel voros = {255, 0, 0};
  Pixel zold = {0, 255, 0};
  Pixel kek = {0, 0, 255};
  int elofordulas[3] = {0};
  for (int i = 0; i < MAGASSAG; ++i) {
    for (int j = 0; j < SZELESSEG; ++j) {
      if (kep[i][j] == voros) ++elofordulas[0];
      if (kep[i][j] == zold) ++elofordulas[1];
      if (kep[i][j] == kek) ++elofordulas[2];
    }
  }
  int leg[2] = {0};
  for (int i = 0; i < 3; ++i) { if (elofordulas[i] > leg[0]) { leg[0] = elofordulas[i]; leg[1] = i; } }
  cout << "4. feladat" << endl << "Egyik legtobbet elofordulo szin: ";
  if (leg[1] == 2) cout << "Kek" << endl;
  else if  (leg[1] == 1) cout << "Zold" << endl;
  else if (leg[1] == 0) cout << "Voros" << endl;

  //5
  cout << "5. feladat" << endl << "3 keppont szelssegu keret letrehozasa" << endl;
  for (int i = 0; i < MAGASSAG; ++i) {
    for (int j = 0; j < SZELESSEG; ++j) {
      if (i == 0 || i == 1 || i == 2) { kep[i][j] = {0,0,0}; }
      if (j == 0 || j == 1 || j == 2) { kep[i][j] = {0,0,0}; }
    }
  }

  //6
  cout << "6.feladat" << endl << "Keretes kep fajlba irasa..." << endl;
  ofstream ofs("keretes.txt");
  for (int i = 0; i < MAGASSAG; ++i) {
    for (int j = 0; j < SZELESSEG; ++j) {
      ofs << kep[i][j].r << " " << kep[i][j].g << " " << kep[i][j].b << endl;
    }
  }
  ofs.close();

  //7
  int kezd[2] = {0};
  int veg[2] = {0};
  bool kezdet_megvan = false;
  bool veg_megvan = false;
  Pixel sarga = {255, 255, 0};
  for (int i = 0; i < MAGASSAG; ++i) {
    for (int j = 0; j < SZELESSEG; ++j) {
      if ( kep[i][j] == sarga &&
           kep[i][j+1] == sarga &&
           kep[i+1][j] == sarga &&
           kep[i+1][j+1] == sarga) { kezd[0] = i+1; kezd[1] = j+1; kezdet_megvan = true; break; }
    }
    if (kezdet_megvan) {
      for (int i = kezd[0]-1; i < MAGASSAG; ++i) {
        for (int j = kezd[1]-1; j < SZELESSEG; ++j) {
          if ( kep[i][j] == sarga &&
               kep[i][j+1] != sarga &&
               kep[i+1][j] != sarga &&
               kep[i+1][j+1] != sarga) {  veg[0] = i+1; veg[1] = j+1; veg_megvan = true; break; }
        }
        if (veg_megvan) break;
      }
    }
    if (veg_megvan && kezdet_megvan) break;
  }
  cout << "7. feladat" << endl << "A sarga teglalap" << endl << "Kezdete: " << kezd[0] << ", " << kezd[1] << endl << "Vege: " << veg[0] << ", " << veg[1] << endl;
  cout << "Keppontok szama: " << abs((veg[1]-kezd[1]+1)*(veg[0]-kezd[0]+1)) << endl;

  return 0;
}
