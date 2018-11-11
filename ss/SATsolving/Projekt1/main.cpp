#include <iostream>
#include <fstream>
#include <string>
#include <limits>
#include <sstream>
//#include "fileExtraction.h"
#include <algorithm>
//#include "cnf.h"
#include <vector>
#include <iterator>
#include <numeric>


std::string oneOnEach (int zeilen, int spalten);
//std::string oneOnEachS (int zeilen, int spalten);
int zeilenSpalten (std::string);
char setVariables (std::string);
std::string sameB(int, int);
std::string sameW(int, int);

using namespace std;

struct arra{string *clause;};
int cl = 0;

int main(int argc, char *argv[])
{
    char filename[128];
    string line;
    ifstream file;
    int fileLength;
    int zeilenZahlI;
    int spaltenZahlI;
    string variablesFix;
    string belegung;


    // Dateinamen einlesen
    cout << "Which puzzle would you like to be solved?" << endl;
    cin.getline(filename, 127);

    // Datei öffnen
    file.open(filename, ios_base::in|ios_base::out);
    if (!file) // Datei konnte nicht geöffnet werden
    {
        cout << "File couldn't be read." << endl;
    }
    else
    {
        int l=1;
        // Anzahl der Zeichen um nötige Zahl der Variablen zu ermitteln
        string ZS[1] ;
        if (getline(file,line))
        {
            ZS[0]=line;
        }
        zeilenZahlI = zeilenSpalten(ZS[0]);
        spaltenZahlI = zeilenSpalten(ZS[0]);
        fileLength = zeilenZahlI * spaltenZahlI;
        cout << zeilenZahlI << " Zeilen" << endl;
        cout << spaltenZahlI << " Spalten" << endl;
        string linear[fileLength];
        while (getline(file,line))
        {
            linear[l]=line;
            l++;
        }

        //linear[1] = linear[1].erase(0,x);
        for (int i= 0; i< zeilenZahlI; i++)
        {
            belegung = belegung + ' ' + linear[i];
        }

        cout << " csd" << belegung.length()<<endl;
        // Belegungen in String speichern
        for (int i = 1; i<=belegung.length(); i++)
        {
                switch (belegung[i])
                {
                    case 'B' :
                        {
                            variablesFix = variablesFix + to_string(i) + " 0" + '\n';
                            cl++;
                            break;
                        }
                    case 'W' :
                        {
                            variablesFix = variablesFix + to_string(-i) + " 0" + '\n';
                            cl++;
                            break;
                        }
                    default :
                        {
                            variablesFix = variablesFix;
                            break;
                        }
                }
        }

    }
    // nur zwei schwarze Felder
    string oneOnEachS;
    oneOnEachS = oneOnEach(zeilenZahlI,spaltenZahlI);
    // nur zwei weiße Felder
    /*string z;
    z = oneOnEachS(fileLength,spaltenZahlI); */
    // N/2 schwarze pro Zeile
    string sameBlack;
    sameBlack = sameB(spaltenZahlI,zeilenZahlI);
    // N/2 weiße pro Zeile
    string sameWhite;
    sameWhite = sameW(spaltenZahlI,zeilenZahlI);
    // Hilfsdatei um Arrays durch for-Schleife in die Datei holen zu können und vor den anderen Klausel platzieren zu können.
    /*fstream fh;
    fh.open("hilfsdatei.txt",ios::in&&ios::out&&ios::trunc);
    for (int i=0; i<3;i++)
    {
        fh << x;
        fh << z;
    }
    fh.flush();
    //fh.close();
    // Hilfsdatei mit Lesefunktion öffnen und CNF-Datei öffnen
    char c; */
    ofstream f;
    //fh.open("hilfsdatei.txt",ios::in);
    f.open("/Users/bg/Desktop/ss/SATsolving/Projekt1/formular.cnf",std::ifstream::out|std::ifstream::trunc);
    // Header für CNF file
    f << 'p' << " cnf " << fileLength << ' ' << cl << endl;
    // Zeilen aus Hilfsdatei holen
    /*while (fh.get(c)) {
        f.put(c);
      } */
       // Klauseln holen
      cout <<"Open : "<<f.is_open()<<endl;;
    f << oneOnEachS;
    f << sameBlack;
    f << sameWhite;
    f << variablesFix;
    f.flush();
    f.close();
    // Picosat starten
    system("picosat /Users/bg/Desktop/ss/SATsolving/Projekt1/formular.cnf");
    return 0;
}
// 1 = schwarz 0 = weiß
// oneOnEach gibt die CNF aus, die prüft, dass max. 2 einer Farbe nebeneinander sind
string oneOnEach (int zeilen, int spalten)
{
    cout << "zeilen: " << zeilen << endl;
    struct arra conj;
    conj.clause = new string[2];
    string clause="" ;
    int pos = 0;

    for (int i=1; i<=zeilen; i++)
    {
        pos++;
        while ( (pos + 2) <= i*zeilen)
        {
           clause = clause + to_string(-pos) + ' ' + to_string(-(pos+1)) + ' ' + to_string(-(pos+2)) + " 0" + '\n';
           clause = clause + to_string(pos) + ' ' + to_string((pos+1)) + ' ' + to_string((pos+2)) + " 0" + '\n';
           cl = 2 + cl;
           pos++;
        }
        pos++;
    }

    int j = 0;
    for (int i= spalten-1; i>=0; i--)
    {
        j++;
        pos = j ;
        while (pos <= ( (spalten*zeilen) - (2*zeilen) ))
        {
           clause = clause + to_string(-pos) + ' ' + to_string(-(pos+zeilen)) + ' ' + to_string(-(pos+2*zeilen)) + " 0" + '\n';
           clause = clause + to_string(pos) + ' ' + to_string((pos+zeilen)) + ' ' + to_string((pos+2*zeilen)) + " 0" + '\n';
           cl = 2 + cl;
           pos = pos + zeilen;
        }


        /*
        // erstes Feld
        if (i==1)
        {
            conj.clause[0] = conj.clause[0] + to_string(-i) + ' ' + to_string(-(i+1)) + ' ' + to_string(-(i+2)) + " 0" + '\n';
            conj.clause[1] = conj.clause[1] + to_string(-i) + ' ' + to_string(-(i+spalten)) + ' ' + to_string(-(i+spalten*2)) + " 0" + '\n';

        }
        else
        {
            // erste Spalte, außer letztes Feld in erster Spalte
            if (((i%spalten) == 1) && i<=(zeichen - (spalten*2)))
            {
                conj.clause[0] = conj.clause[0] + to_string(-i) + ' ' + to_string(-(i+1)) + ' ' + to_string(-(i+2)) + " 0" + '\n';
                conj.clause[1] = conj.clause[1] + to_string(-i) + ' ' + to_string(-(i+spalten)) + ' ' + to_string(-(i+spalten*2)) + " 0" + '\n';
            }
            else
            {
                // erste Zeile und eine der letzten 2 Spalten
                if (i<=spalten && ((i%spalten)==0 || (i%spalten==(spalten-1))))
                {
                    conj.clause[1] = conj.clause[1] + to_string(-i) + ' ' + to_string(-(i+spalten)) + ' ' + to_string(-(i+spalten*2)) + " 0" + '\n';
                }
                else
                {
                    // Rest erste Spalte
                    if (i<=spalten)
                    {
                    conj.clause[0] = conj.clause[0] + to_string(-i) + ' ' + to_string(-(i+1)) + ' ' + to_string(-(i+2)) + " 0" + '\n';
                    conj.clause[1] = conj.clause[1] + to_string(-i) + ' ' + to_string(-(i+spalten)) + ' ' + to_string(-(i+spalten*2)) + " 0" + '\n';
                    }
                    else
                    {
                        // Feld das in letzten 2 Spalten und letzen 2 Zeilen liegt
                        if(((i%spalten)==0 || (i%spalten==(spalten-1))) && i>(zeichen-(spalten*2)))
                        {

                        }
                        else
                        {
                            // Feld das im Rest der letzten 2 Zeilen liegt.
                            if(i>(zeichen-(spalten*2)))
                            {
                                conj.clause[0] = conj.clause[0] + to_string(-i) + ' ' + to_string(-(i+1)) + ' ' + to_string(-(i+2)) + " 0" + '\n';
                            }
                            else
                            {
                                // Feld das im Rest der letzten 2 Spalten liegt.
                                if((i%spalten)==0 || (i%spalten)==(spalten-1))
                                {
                                    conj.clause[1] = conj.clause[1] + to_string(-i) + ' ' + to_string(-(i+spalten)) + ' ' + to_string(-(i+spalten*2)) + " 0" + '\n';
                                }
                                else
                                {
                                    // Restliche Felder
                                    conj.clause[0] = conj.clause[0] + to_string(-i) + ' ' + to_string(-(i+1)) + ' ' + to_string(-(i+2)) + " 0" + '\n';
                                    conj.clause[1] = conj.clause[1] + to_string(-i) + ' ' + to_string(-(i+spalten)) + ' ' + to_string(-(i+spalten*2)) + " 0" + '\n';
                                }
                            }
                        }
                    }
                }
            }
        } */
    }
    return clause;
}
/*
string oneOnEachS (int spalten)
{
    cout << "zeichen: " << zeichen << endl;
    struct arra conj;
    conj.clause = new string[2];
    clause ="";
    for (int i=1; i+2<=spalten; i++)
    {
        clause = clause + + to_string(-i) + ' ' + to_string(-(i+1)) + ' ' + to_string(-(i+2)) + " 0" + '\n';
        clause = clause + + to_string(i) + ' ' + to_string((i+1)) + ' ' + to_string((i+2)) + " 0" + '\n';

        // erstes Feld
        if (i==1)
        {
            conj.clause[0] = conj.clause[0] + to_string(i) + ' ' + to_string(i+1) + ' ' + to_string(i+2) + " 0" + '\n';
            conj.clause[1] = conj.clause[1] + to_string(i) + ' ' + to_string(i+spalten) + ' ' + to_string(i+spalten*2) + " 0" + '\n';

        }
        else
        {
            // erste Spalte, außer letztes Feld in erster Spalte
            if (((i%spalten) == 1) && i<=(zeichen - (spalten*2)))
            {
                conj.clause[0] = conj.clause[0] + to_string(i) + ' ' + to_string(i+1) + ' ' + to_string(i+2) + " 0" + '\n';
                conj.clause[1] = conj.clause[1] + to_string(i) + ' ' + to_string(i+spalten) + ' ' + to_string(i+spalten*2) + " 0" + '\n';
            }
            else
            {
                // erste Zeile und eine der letzten 2 Spalten
                if (i<=spalten && ((i%spalten)==0 || (i%spalten==(spalten-1))))
                {
                    conj.clause[1] = conj.clause[1] + to_string(i) + ' ' + to_string(i+spalten) + ' ' + to_string(i+spalten*2) + " 0" + '\n';
                }
                else
                {
                    // Rest erste Spalte
                    if (i<=spalten)
                    {
                    conj.clause[0] = conj.clause[0] + to_string(i) + ' ' + to_string(i+1) + ' ' + to_string(i+2) + " 0" + '\n';
                    conj.clause[1] = conj.clause[1] + to_string(i) + ' ' + to_string(i+spalten) + ' ' + to_string(i+spalten*2) + " 0" + '\n';
                    }
                    else
                    {
                        // Feld das in letzten 2 Spalten und letzen 2 Zeilen liegt
                        if(((i%spalten)==0 || (i%spalten==(spalten-1))) && i>(zeichen-(spalten*2)))
                        {

                        }
                        else
                        {
                            // Feld das im Rest der letzten 2 Zeilen liegt.
                            if(i>(zeichen-(spalten*2)))
                            {
                                conj.clause[0] = conj.clause[0] + to_string(i) + ' ' + to_string(i+1) + ' ' + to_string(i+2) + " 0" + '\n';
                            }
                            else
                            {
                                // Feld das im Rest der letzten 2 Spalten liegt.
                                if((i%spalten)==0 || (i%spalten)==(spalten-1))
                                {
                                    conj.clause[1] = conj.clause[1] + to_string(i) + ' ' + to_string(i+spalten) + ' ' + to_string(i+spalten*2) + " 0" + '\n';
                                }
                                else
                                {
                                    // Restliche Felder
                                    conj.clause[0] = conj.clause[0] + to_string(i) + ' ' + to_string(i+1) + ' ' + to_string(i+2) + " 0" + '\n';
                                    conj.clause[1] = conj.clause[1] + to_string(i) + ' ' + to_string(i+spalten) + ' ' + to_string(i+spalten*2) + " 0" + '\n';
                                }
                            }
                        }
                    }
                }
            }
        }
    }
    return clause;
} */
string sameB(int n, int zeilen)
{
    int k= (n/2)+1;
    string clause ="";

    for (int l=0; l<zeilen; l++)
    {
        int s = l*n;
        vector<string> selected;
        vector<bool> selector(n);
        fill(selector.begin(), selector.begin() + k, true);
        do {
             for (int i = 0; i < n; i++) {
              int m = i+1+s;
              if (selector[i]) {
                    selected.push_back(to_string(m));
              }
             }
             //     combinations.push_back(selected);
             for(std::vector<std::string>::const_iterator i = selected.begin(); i != selected.end(); i++)
             {
                 clause = clause + *i + ' ';
             }
             selected.clear();
             clause = clause + " 0" + '\n';
             cl++;
         }
         while (prev_permutation(selector.begin(), selector.end()));
    // print integers and permute bitmask
    }
    return clause;
}
string sameW(int n, int zeilen)
{
    int k= (n/2)+1;
    string clause = "";

    for (int j=0; j<zeilen; j++)
    {
        int s = j*n;
        vector<string> selected;
        vector<bool> selector(n);
        fill(selector.begin(), selector.begin() + k, true);
        do {
             for (int i = 0; i < n; i++) {
                int m = i+1+s;
              if (selector[i]) {
                    selected.push_back(to_string(-m));
              }
             }
             //     combinations.push_back(selected);
             for(std::vector<std::string>::const_iterator i = selected.begin(); i != selected.end(); i++)
             {
                 clause = clause + *i + ' ';
             }
             selected.clear();
             clause = clause + " 0" + '\n';
             cl++;
         }
         while (prev_permutation(selector.begin(), selector.end()));
    // print integers and permute bitmask
    }
    return clause;
}

int zeilenSpalten (std::string a)
{
    std::stringstream parser;
    parser << a;
    int anzahl;
    while(!(parser>>anzahl))
    {
        if(parser.eof()) throw std::invalid_argument("Zahlen fehlen");
        parser.clear();
        parser.ignore(1);
    }

    return anzahl;
}







