/* Solution for the <2013 May> Hungarian IT matura exam's 4th task */

#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <algorithm>

using namespace std;

bool kisebb(string str1, string str2) { return (str1 < str2); }

bool sok(string str) {
  int jah_int = 0;
  for (auto it = str.begin(); it != str.end(); ++it) {
    if (*it == '0') { ++jah_int; if(jah_int >= 18) return true;}
  }
  return false;
}

int main () {
  vector<string> db;

  //1
  string be;
  ifstream ifs("ip.txt");
  while(ifs >> be) {
    db.push_back(be);
  }
  ifs.close();

  //2
  cout << "2. feladat" << endl << "Az allomanyban " << db.size() << " adasor van" << endl;

  //3
  vector<string>::iterator legkisebb = min_element(db.begin(), db.end(), kisebb);
  cout << "3. feladat" << endl << "A legkisebb IP cim: " << *legkisebb << endl;

  //4
  int kimutatas[3] = {0};
  for (auto it = db.begin(); it != db.end(); ++it) {
    if (it->substr(0, 9) == "2001:0db8") ++kimutatas[0];
    else if (it->substr(0, 7) == "2001:0e") ++kimutatas[1];
    else if (it->substr(0, 2) == "fc" || it->substr(0, 2) == "fd") ++kimutatas[2];
  }
  cout << "4. feladat" << endl;
  cout << "Dok cim: " << kimutatas[0] << " darab" << endl;
  cout << "Glob cim: " << kimutatas[1] << " darab" << endl;
  cout << "Helyi cim: " << kimutatas[2] << " darab" << endl;

  //5
  ofstream ofs("sok.txt");
  for (auto it = db.begin(); it != db.end(); ++it) {
    if (sok(*it)) {
      ofs << distance(db.begin(), it)+1 << " " << *it << endl;
    }
  }
  ofs.close();

  //6
  int index = 0;
  cout << "Kerem a sorszamot: ";
  cin >> index; cout << endl << "Eredeti:     " << db[index] << endl << "Roviditett:  ";
  string modositott, buff = db[index];
  while (1) {
    bool changesInThisStep = false;
    modositott = buff;

    for (auto strIt = modositott.begin(); strIt != modositott.end(); ++strIt) {
      if( /*(distance(modositott.begin(), strIt) == 1 && *strIt == '0') ||*/
          (*(strIt-1) == ':' && *strIt == '0' && *(strIt+1) != ':')) {
            changesInThisStep = true;
            buff = modositott.substr(0,distance(modositott.begin(), strIt)) + modositott.substr(distance(modositott.begin(), strIt+1));
      }
    }

    if (!changesInThisStep) break;
  }
  cout << modositott << endl;

  //7
  while(1) {
    bool changesInThisStep = false;
    modositott = buff;

    for (auto strIt = modositott.begin(); strIt != modositott.end(); ++strIt) {
      if ((*strIt == ':' && *(strIt+1) == '0' && *(strIt+2) == ':') &&
          (*(strIt+3) == '0' && *(strIt+4) == ':')) {
            buff = modositott.substr(0,distance(modositott.begin(), strIt)) + ':' + modositott.substr(distance(modositott.begin(), strIt+4));
            changesInThisStep = true;
          } else if (*strIt == ':' && *(strIt+1) == ':' && *(strIt+2) == '0') {
            buff = modositott.substr(0,distance(modositott.begin(), strIt)) + modositott.substr(distance(modositott.begin(), strIt+3));;
            changesInThisStep = true;
          }
    }
    if (!changesInThisStep) break;
  }
  cout <</* "7. feladat" << endl << */"             "<<modositott;

  return 0;
}
