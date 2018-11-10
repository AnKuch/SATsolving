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


struct arra oneOnEachB (int zeichen, int spalten);
struct arra oneOnEachW (int zeichen, int spalten);
int zeilenSpalten (std::string);
char setVariables (std::string);
std::string sameB(int, int);
std::string sameW(int, int);

using namespace std;

struct arra{string *clause;};

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
    string linear[200];


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
        while (getline(file,line))
        {
            linear[l]=line;
            l++;
        }
        zeilenZahlI = zeilenSpalten(linear[1]);
        cout << zeilenZahlI << " Zeilen" << endl;
        string zeile = to_string(zeilenZahlI);
        int x= zeile.length();
        linear[1] = linear[1].erase(0,x);
        spaltenZahlI = zeilenSpalten(linear[1]);
        for (int i= 2; i<= zeilenZahlI+1; i++)
        {
            belegung = belegung + ' ' + linear[i];
        }
        cout << spaltenZahlI << " Spalten" << endl;
        fileLength = zeilenZahlI * spaltenZahlI;

        // Belegungen in String speichern
        for (int i = 1; i<=belegung.length(); i++)
        {
                switch (belegung[i])
                {
                    case 'B' :
                        {
                            variablesFix = variablesFix + to_string(i) + " 0" + '\n';
                            break;
                        }
                    case 'W' :
                        {
                            variablesFix = variablesFix + to_string(-i) + " 0" + '\n';
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
    struct arra x;
    x = oneOnEachB(fileLength,spaltenZahlI);
    // nur zwei weiße Felder
    struct arra z;
    z = oneOnEachW(fileLength,spaltenZahlI);
    // N/2 schwarze pro Zeile
    string sameBlack;
    sameBlack = sameB(spaltenZahlI,zeilenZahlI);
    // N/2 weiße pro Zeile
    string sameWhite;
    sameWhite = sameW(spaltenZahlI,zeilenZahlI);
    // Hilfsdatei um Arrays durch for-Schleife in die Datei holen zu können und vor den anderen Klausel platzieren zu können.
    fstream fh;
    fh.open("hilfsdatei.txt",ios::out);
    for (int i=0; i<=3;i++)
    {
        fh << x.clause[i];
        fh << z.clause[i];
    }
    fh.close();
    // Hilfsdatei mit Lesefunktion öffnen und CNF-Datei öffnen
    char c;
    fstream f;
    fh.open("hilfsdatei.txt",ios::in);
    f.open("formular.cnf", ios::out);
    // Header für CNF file
    f << 'p' << " cnf " << fileLength << ' ' << 200 << endl;
    // Zeilen aus Hilfsdatei holen
    while (fh.get(c)) {
        f.put(c);
      }
      // Restliche Klauseln holen
    f << sameBlack;
    f << sameWhite;
    f << variablesFix;
    f.close();
    // Picosat starten
    system("picosat -f formular.cnf");
    return 0;
}
// 1 = schwarz 0 = weiß
// oneOnEach gibt die CNF aus, die prüft, dass max. 2 einer Farbe nebeneinander sind
struct arra oneOnEachB (int zeichen, int spalten)
{
    cout << "zeichen: " << zeichen << endl;
    struct arra conj;
    conj.clause = new string[2];
    for (int i=1; i<=zeichen; i++)
    {
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
        }
    }
    return conj;
}
struct arra oneOnEachW (int zeichen, int spalten)
{
    cout << "zeichen: " << zeichen << endl;
    struct arra conj;
    conj.clause = new string[2];
    for (int i=1; i<=zeichen; i++)
    {
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
    return conj;
}
string sameB(int n, int zeilen)
{
    int k= (n/2)+1;
    string clause;

    for (int l=0; l<zeilen; l++)
    {
        int s = l*n;
        vector<string> selected;
        vector<bool> selector(8);
        fill(selector.begin(), selector.begin() + k, true);
        do {
             for (int i = 0; i < n; i++) {
              int m = i+1+s;
              if (selector[i]) {
                    selected.push_back(to_string(m));
              }
             }
             //     combinations.push_back(selected);
             for(std::vector<std::string>::const_iterator i = selected.begin(); i != selected.end(); ++i)
             {
                 clause = clause + *i + ' ';
             }
             selected.clear();
             clause = clause + " 0" + '\n';
         }
         while (prev_permutation(selector.begin(), selector.end()));
    // print integers and permute bitmask
    }
    return clause;
}
string sameW(int n, int zeilen)
{
    int k= (n/2)+1;
    string clause;

    for (int j=0; j<zeilen; j++)
    {
        int s = j*n;
        vector<string> selected;
        vector<bool> selector(8);
        fill(selector.begin(), selector.begin() + 5, true);
        do {
             for (int i = 0; i < 8; i++) {
                int m = i+1+s;
              if (selector[i]) {
                    selected.push_back(to_string(-m));
              }
             }
             //     combinations.push_back(selected);
             for(std::vector<std::string>::const_iterator i = selected.begin(); i != selected.end(); ++i)
             {
                 clause = clause + *i + ' ';
             }
             selected.clear();
             clause = clause + " 0" + '\n';
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
        if(parser.eof()) throw std::invalid_argument("Zeilenzahlen fehlen");
        parser.clear();
        parser.ignore(1);
    }

    return anzahl;
}





