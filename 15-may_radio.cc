#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <algorithm>

using namespace std;

int UZENET_HOSSZ = 90;

struct Adas {
  int nap;
  int felado;
  string uzenet;
};

bool kisebb (Adas a1, Adas a2) { return (a1.nap > a2.nap); }

bool szame (string karaktersorozat) {
  bool valasz = true;
  for (auto strIt = karaktersorozat.begin(); strIt != karaktersorozat.end(); ++strIt) {
    if ( (*strIt) < '0' || (*strIt) > '9') valasz = false;
  }
  return valasz;
}

int main() {
  vector<Adas> adasok;

  //1
  string be;
  ifstream ifs("veetel.txt");
  while ( getline(ifs, be) ) {
    Adas adas_be;
    adas_be.nap = stoi(be.substr(0, be.find(' ')));
    adas_be.felado = stoi(be.substr(be.find(' ')+1));
    getline(ifs,be); //ezzel elbasztam sok idot: nem volt itt ez a line, ezert a kovi utemben az uzenetet akarta stringge konvertalni.
    adas_be.uzenet = be;
    adasok.push_back(adas_be);
  }
  ifs.close();

  //2
  cout << "2. feladat" << endl
       << "Az elso uzenetet a " << adasok[0].felado << " radioamator rogzitette" << endl
       << "Az uccsot a " << adasok.back().felado << " radioa. rogz." << endl;

  //3
  cout << "3. feladat" << endl;
  for (auto it = adasok.begin(); it != adasok.end(); ++it) {
    if ( (it->uzenet).find("farkas") != string::npos ) { //FONTOS: uj dolog: hogyan nezzuk meg, hogy egy string tartalmaz-e valami substr
      cout << "Nap: " << it->nap << " Felado: " << it->felado << endl;
    }
  }

  //4
  cout << "4.feladat" << endl;
  int kimutatas[11] = {0};
  for (auto it = adasok.begin(); it != adasok.end(); ++it) {
    kimutatas[it->nap-1] += 1;
  }
  for (int i=0; i<11; ++i) {
    cout << i+1 << ". nap: " << kimutatas[i] << " radioamator" << endl;
  }

  //5
  //FONTOS: modszer: ketto nagy henger, melyeket egymason gorgetunk; a hengerekek hosszaban stringek vannak; az egyik henger kisebb, a masik nagyobb
  cout << "5. feladat" << endl;
  sort(adasok.begin(), adasok.end(), kisebb);

  vector<string> helyreallitott;
  helyreallitott.push_back(adasok[0].uzenet);

  for (auto it = adasok.begin()+1; it != adasok.end(); ++it) {
    if (it->nap == (it-1)->nap) {
        for (int i = 0; i < UZENET_HOSSZ; ++i) {
          if (it->uzenet[i] != '#') {
            helyreallitott.back()[i] = it->uzenet[i];
          }
        }
      } else {
        helyreallitott.push_back(adasok[distance(adasok.begin(), it)+1].uzenet);
        continue;
      }
  }

  ofstream ofs("adaas.txt");
  for (auto strit = helyreallitott.begin(); strit != helyreallitott.end(); ++strit) {
    ofs << *strit << endl;
  }
  ofs.close();

  //6

  //7
  int nap_in = -1;
  int felado_in = -1;
  cout << "7. feladat" << endl;
  cout << "Nap: ";
  cin >> nap_in;
  cout << "Felado: ";
  cin >> felado_in;

  string vizsgalando;
  for (auto it = adasok.begin(); it != adasok.end(); ++it) {
    if (it->nap == nap_in && it->felado == felado_in) {
      vizsgalando = (it->uzenet).substr(0, 5);
      break;
    }
  }

  int farkaskak = 0;
  if (vizsgalando.find('/') == string::npos) {
    cout << endl << "Nincs ilyen feljegyzes." << endl;
  } else {
    size_t gg = vizsgalando.find('#');
    if ( gg != string::npos && vizsgalando[gg-1] != ' ' ) {
      cout << endl <<"Nincs informacio" << endl;
    } else {
      if (vizsgalando.find('/') == 2) {
        farkaskak = stoi(vizsgalando.substr(0,1)) + stoi(vizsgalando.substr(3,4));
        cout << endl << "Farkaskak: " << farkaskak;
      } else {
        farkaskak += vizsgalando[0] - '0';
        farkaskak += vizsgalando[2] - '0';
        cout << endl << "Farkaskak: " << farkaskak;
      }
    }
  }

  return 0;
}
