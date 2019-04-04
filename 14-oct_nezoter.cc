/* Solution for the <2014 Oct> Hungarian IT matura exam's 4th task */

#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <algorithm>

using namespace std;


int ar(int kat) { //5
  if (kat == 1) return 5000;
  else if (kat == 2) return 4000;
  else if (kat == 3) return 3000;
  else if (kat == 4) return 2000;
  else if (kat == 5) return 1500;
  else return 0;
}

int main() {
  int befogadokepesseg = 15*20;
  int sorok = 15;
  int szekek = 20;
  int eladott_jegyek = 0; //3
  int arkat_kimutatas[5] = {0}; //4
  int osszes_bevetel = 0; //5
  int egyedulallo_helyek = 0; //6
  vector<string> foglaltsag;
  vector<string> arkat;
  vector<string> szabad_arkat;

  //1
  string be;
  ifstream ifs("foglaltsag.txt");
  while (ifs >> be) { foglaltsag.push_back(be); }
  ifs.close();
  ifstream ifs2("kategoria.txt");
  while (ifs2 >> be) { arkat.push_back(be); }
  ifs2.close();

  //2 eddig 12p
  int sor = 0; int szek = 0; bool foglalt = false;
  cout << "2. feladat" << endl << "Sor = "; cin >> sor;
  cout << "Szek = "; cin >> szek;
  if ( foglaltsag[sor-1][szek-1] == 'x' ) foglalt = true;
  cout << "A szek " << (foglalt ? "foglalt" : "szabad") << endl;

  //3
  for (int i_sor = 0; i_sor < sorok; ++i_sor) {
    string szabad_arkat_sor; //7
    for (int i_szek = 0; i_szek < szekek; ++ i_szek) {
      if ( foglaltsag[i_sor][i_szek] == 'x' ) {
         szabad_arkat_sor += 'x'; //7
         ++eladott_jegyek;
         ++arkat_kimutatas[ (arkat[i_sor][i_szek]-'0')-1 ]; //4
         //6:
         if (i_szek > 1) {
          if ( foglaltsag[i_sor][i_szek-1] == 'o' && foglaltsag[i_sor][i_szek-2] == 'x') ++egyedulallo_helyek;
          if (i_szek == 18)
           if ( foglaltsag[i_sor][19] == 'o' ) ++egyedulallo_helyek;
         }
         else if (i_szek == 1)
          if ( foglaltsag[i_sor][0] == 'o' ) ++egyedulallo_helyek;

      } else if (foglaltsag[i_sor][i_szek] == 'o') { //7
        szabad_arkat_sor += arkat[i_sor][i_szek];
      }
    }
    szabad_arkat.push_back(szabad_arkat_sor);
  }
  cout << "3. feladat" << endl << "Eddig " << eladott_jegyek << " jegyet adtak el, s ez a nezoter " << 100*eladott_jegyek/befogadokepesseg << "%-a." << endl;

  //4
  int temp = *max_element(arkat_kimutatas, arkat_kimutatas+5);
  int melyik_arkat = 0;
  for (int i = 0; i <5; ++i) if (arkat_kimutatas[i] == temp) {melyik_arkat = i+1;}
  cout << "4. feladat" << endl << "A legtobb jegyet a " << melyik_arkat<< " kategoriaban adtak el" << endl;

  //5
  for (int i = 0; i <5; ++i)
    osszes_bevetel += arkat_kimutatas[i]*(ar(i+1));
  cout << "5. feladat" << endl << "Az osszes arbevetel: " << osszes_bevetel << " Ft" << endl;

  //6
  cout << "6.feladat" << endl << "Osszesen " << egyedulallo_helyek << " egyedulallo ures hely van" << endl;

  //7
  ofstream ofs("szabad.txt");
  for (auto it = szabad_arkat.begin(); it != szabad_arkat.end(); ++it) {
    ofs << *it << endl;
  }
  ofs.close();

  return 0;
}
