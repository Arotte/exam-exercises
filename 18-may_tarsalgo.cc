#include<iostream>
#include<fstream>
#include<string>

#include<vector>
#include<algorithm> //std::sort

using namespace std;

struct IdoPont {
    int ora, perc, hanyan;
    void update(int o, int p, int h) { ora = o; perc = p; hanyan = h; }
    IdoPont& operator=(IdoPont& other) { ora = other.ora; perc = other.perc; hanyan = other.hanyan; return *this;}
    IdoPont(): ora(-1), perc(-1), hanyan(-1) {}
    int percben() { return (ora*60 + perc); }
};

struct Esemeny {
    int id;
    IdoPont ip;
    string ir;
};

struct Athaladas {
    int id = 0;
    int mcount = 0;
    Athaladas(int id_, int mcount_): id(id_), mcount(mcount_) {}
};

bool bigger(Athaladas ath1, Athaladas ath2) { return(ath1.id<ath2.id); }

int diffP(IdoPont ip1, IdoPont ip2) {
        return (ip1.percben() - ip2.percben());
}

class Tarsalgo {
public:
    vector<Esemeny> esemenyek;
    int mLek = 0;

    //1.feladat
    void beolvas(string fajl) {
        ifstream fin(fajl);

        Esemeny esbe;
        while(fin >> esbe.ip.ora
                  >> esbe.ip.perc
                  >> esbe.id
                  >> esbe.ir)
        {
            esemenyek.push_back(esbe);
        }
        fin.close();
    }

    //2.feladat
    void elsoutolso() {
        cout << "2. feladat:" << endl
             << "Elso belepo ID: " << esemenyek[0].id << endl
             << "Utolso belepo ID: " << esemenyek[esemenyek.size()-1].id << endl;
    }

    //3.feladat
    void athaladasok(string outFile) {
        vector<Athaladas> athCounts;

        for(vector<Esemeny>::iterator esit = esemenyek.begin(); esit != esemenyek.end(); ++esit) {
            bool isFound = false;
            for(vector<Athaladas>::iterator it = athCounts.begin(); it != athCounts.end(); ++it) {
                if (it->id == esit->id) {
                    ++(it->mcount);
                    isFound = true;
                    break;
                }
            }
            if(!isFound) {
                Athaladas ath(esit->id, 1);
                athCounts.push_back(ath);
            }
        }

        sort(athCounts.begin(), athCounts.end(), bigger);

        ofstream ofs(outFile);
        for(vector<Athaladas>::iterator it = athCounts.begin(); it != athCounts.end(); ++it)
            ofs << it->id << " " << it->mcount << endl;
        ofs.close();
    }

    //4. feladat
    void vegenbent() {
        vector<int> bent;
        for (vector<Esemeny>::iterator esit = esemenyek.begin(); esit != esemenyek.end(); ++esit)
            if (esit->ir == "be")
                bent.push_back(esit->id);
            else
                bent.erase(find(bent.begin(), bent.end(), esit->id));
       cout << "4. feladat:" << endl << "A meres zarasakor meg bent tartozkodok:" << endl;
       for (auto it = bent.begin(); it != bent.end(); ++it) // auto = vector<int>::iterator
            cout << *it << " ";
    }

    //5.feladat
    void legtobben() {
        vector<int> bent;
        IdoPont ipLegtobben, ipMost;
        for (auto esit = esemenyek.begin(); esit != esemenyek.end(); ++esit) {
            if(esit->ir == "be") {
                bent.push_back(esit->id);
                ipMost.update(esit->ip.ora, esit->ip.perc, ++ipMost.hanyan);
                ipLegtobben = ipMost.hanyan > ipLegtobben.hanyan ? ipMost : ipLegtobben;
            } else {
                bent.erase(find(bent.begin(), bent.end(), esit->id));
                ipMost.update(esit->ip.ora, esit->ip.perc, --ipMost.hanyan);
            }
        }
        cout << endl << "5. feladat:" << endl
             << "A legtobben ekkor voltak bent: "
             << ipLegtobben.ora << ":" << ipLegtobben.perc << endl;
    }

    //6.feladat
    void lekerdez() {
        cout << "6. feladat:" << endl;
        cout << "Adjon meg egy ID-t: ";
        cin >> mLek;
    }

    //7.feladat
    void mikorbent() {
        cout << endl << "7. feladat:" << endl
             << "Az adott szemely eddig volt bent: " << endl;
        IdoPont ipBe, ipKi, ipkie;
        int mennyit = 0; bool isBent = false;
        for (auto it = esemenyek.begin(); it != esemenyek.end(); ++it) {
            if (it->id == mLek) {
                if (it->ir == "be") {
                    ipBe.update(it->ip.ora, it->ip.perc, 0);
                    cout << ipBe.ora << ":" << ipBe.perc << "-";
                } else {
                    ipKi.update(it->ip.ora, it->ip.perc, 0);
                }
            }
            if(ipKi.ora != ipkie.ora || ipKi.perc != ipkie.perc) {
                cout << ipKi.ora << ":" << ipKi.perc << endl;
                mennyit += diffP(ipKi, ipBe);
            } else {
                IdoPont vege; vege.update(15,0,0);
                mennyit += diffP(ipKi, ipBe);
                isBent = true;
            }
            ipkie = ipKi;
        }

        if(isBent)
            cout << endl << "A csavo meg bent volt a megfigyeles vegen." << endl;

        cout << "Bent toltott percek: " << mennyit << endl;
        cout << endl;
    }

    //8.feladat

};

int main() {
    Tarsalgo ta;

    //1.feladat
    ta.beolvas("ajto.txt");

    //2.feladat
    ta.elsoutolso();

    //3.feladat
    ta.athaladasok("athaladas.txt");

    //4.feladat
    ta.vegenbent();

    //5.feladat
    ta.legtobben();

    //6.feladat
    ta.lekerdez();

    //7.feladat
    ta.mikorbent();

    return 0;
}
