/* Solution for the <2016 October> Hungarian IT matura exam's 4th task */

#include<iostream>
#include<fstream>
#include<vector>
#include<string>
#include<algorithm>

using namespace std;

struct Idopont { int o, p, mp = 0; };
struct Hivas { Idopont start, end; };

//1
int mpbe(Idopont ip) { return(3600*ip.o + 60*ip.p + ip.mp); }

int hivashossz(Hivas hv) { return (mpbe(hv.end) - mpbe(hv.start)); }
bool ipbele(Hivas hv, Idopont ip) { return (mpbe(hv.start) <= mpbe(ip) && mpbe(hv.end) >= mpbe(ip) ); }

int main() {
	vector<Hivas> ipk;

	//2
	Hivas be;
	ifstream ifs("hivas.txt");
	while (ifs >> be.start.o) {
		ifs >> be.start.p >> be.start.mp
			>> be.end.o >> be.end.p >> be.end.mp;
		ipk.push_back(be);
	}
	ifs.close();

	//3
	cout << "3.feladat" << endl;
	int kimutatas[24] = {0};
	for (auto it = ipk.begin(); it != ipk.end(); ++it)
		++kimutatas[it->start.o];
	for (int i = 0; i < 24; ++i)
		if (kimutatas[i] != 0) cout << i << " ora " << kimutatas[i] << " hivas" << endl;

	//4
	cout << "4.feladat" << endl;
	Hivas leghosszab = {{0,0,0} , {0,0,0}};
	int sor = 0;
	for (auto it = ipk.begin(); it != ipk.end(); ++it) {
		if (hivashossz(*it) > hivashossz(leghosszab)) {
			leghosszab = *it;
			sor = distance(ipk.begin(), it) + 1;
		}
	}
	cout << "Leghosszab ideig hivasban levo telefonalo "
			 << hivashossz(leghosszab)
			 << " masodpercig volt hivasban es a "
			 << sor << " sorban van." << endl;

	//5
	cout << "5. feladat" << endl;
	Idopont ipbe;
	cout << "Idopont (ora, perc, masodperc): ";
	cin >> ipbe.o >> ipbe.p >> ipbe.mp;


	return 0;
}
