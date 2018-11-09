#include <iostream>
#include <fstream>
#include <string>
#include <limits>
#include <sstream>
#include "fileExtraction.h"
//#include "cnf.h"

struct arra oneOnEachB (int zeichen, int spalten);
struct arra oneOnEachW (int zeichen, int spalten);
int zeilenSpalten (std::string);
char setVariables (std::string);
struct arra same(int zeilen, std::string var[]);

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
                            variablesFix = variablesFix + ' ' + to_string(i);
                            break;
                        }
                    case 'W' :
                        {
                            variablesFix = variablesFix + ' ' + to_string(-i);
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
    struct arra x;
    x = oneOnEachB(fileLength,spaltenZahlI);
    cout << x.clause[0] << endl;
    struct arra y;
    y = same(zeilenZahlI,linear);
    cout << y.clause[2] << endl;
    struct arra z;
    z = oneOnEachW(fileLength,spaltenZahlI);
    fstream f;
    f.open("formular.cnf", ios::out);
    f << 'p' << " cnf " << fileLength << ' ' << 200 << endl;
    for (int i=0; i<=3;i++)
    {
        f<< y.clause[i];
        f<< x.clause[i];
        f << z.clause[i];
        /*for (int j=0; j<=sizeof(x);j++)
        {
            f<< x.clause[j] << j << " zu x " << endl;
            for (int m=0; m<=sizeof(z);m++)
            {
                f << z.clause[m] << m << " zu z " << endl;
            }
        }*/
    }
    f.close();
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
            conj.clause[0] = conj.clause[0] + ' ' + to_string(-i) + ' ' + to_string(-(i+1)) + ' ' + to_string(-(i+2)) + " 0" + '\n';
            conj.clause[1] = conj.clause[1] + ' ' + to_string(-i) + ' ' + to_string(-(i+spalten)) + ' ' + to_string(-(i+spalten*2)) + " 0" + '\n';

        }
        else
        {
            // erste Spalte, außer letztes Feld in erster Spalte
            if (((i%spalten) == 1) && i<=(zeichen - (spalten*2)))
            {
                conj.clause[0] = conj.clause[0] + ' ' + to_string(-i) + ' ' + to_string(-(i+1)) + ' ' + to_string(-(i+2)) + " 0" + '\n';
                conj.clause[1] = conj.clause[1] + ' ' + to_string(-i) + ' ' + to_string(-(i+spalten)) + ' ' + to_string(-(i+spalten*2)) + " 0" + '\n';
            }
            else
            {
                // erste Zeile und eine der letzten 2 Spalten
                if (i<=spalten && ((i%spalten)==0 || (i%spalten==(spalten-1))))
                {
                    conj.clause[1] = conj.clause[1] + ' ' + to_string(-i) + ' ' + to_string(-(i+spalten)) + ' ' + to_string(-(i+spalten*2)) + " 0" + '\n';
                }
                else
                {
                    // Rest erste Spalte
                    if (i<=spalten)
                    {
                    conj.clause[0] = conj.clause[0] + ' ' + to_string(-i) + ' ' + to_string(-(i+1)) + ' ' + to_string(-(i+2)) + " 0" + '\n';
                    conj.clause[1] = conj.clause[1] + ' ' + to_string(-i) + ' ' + to_string(-(i+spalten)) + ' ' + to_string(-(i+spalten*2)) + " 0" + '\n';
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
                                conj.clause[0] = conj.clause[0] + ' ' + to_string(-i) + ' ' + to_string(-(i+1)) + ' ' + to_string(-(i+2)) + " 0" + '\n';
                            }
                            else
                            {
                                // Feld das im Rest der letzten 2 Spalten liegt.
                                if((i%spalten)==0 || (i%spalten)==(spalten-1))
                                {
                                    conj.clause[1] = conj.clause[1] + ' ' + to_string(-i) + ' ' + to_string(-(i+spalten)) + ' ' + to_string(-(i+spalten*2)) + " 0" + '\n';
                                }
                                else
                                {
                                    // Restliche Felder
                                    conj.clause[0] = conj.clause[0] + ' ' + to_string(-i) + ' ' + to_string(-(i+1)) + ' ' + to_string(-(i+2)) + " 0" + '\n';
                                    conj.clause[1] = conj.clause[1] + ' ' + to_string(-i) + ' ' + to_string(-(i+spalten)) + ' ' + to_string(-(i+spalten*2)) + " 0" + '\n';
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
            conj.clause[0] = conj.clause[0] + ' ' + to_string(i) + ' ' + to_string(i+1) + ' ' + to_string(i+2) + " 0" + '\n';
            conj.clause[1] = conj.clause[1] + ' ' + to_string(i) + ' ' + to_string(i+spalten) + ' ' + to_string(i+spalten*2) + " 0" + '\n';

        }
        else
        {
            // erste Spalte, außer letztes Feld in erster Spalte
            if (((i%spalten) == 1) && i<=(zeichen - (spalten*2)))
            {
                conj.clause[0] = conj.clause[0] + ' ' + to_string(i) + ' ' + to_string(i+1) + ' ' + to_string(i+2) + " 0" + '\n';
                conj.clause[1] = conj.clause[1] + ' ' + to_string(i) + ' ' + to_string(i+spalten) + ' ' + to_string(i+spalten*2) + " 0" + '\n';
            }
            else
            {
                // erste Zeile und eine der letzten 2 Spalten
                if (i<=spalten && ((i%spalten)==0 || (i%spalten==(spalten-1))))
                {
                    conj.clause[1] = conj.clause[1] + ' ' + to_string(i) + ' ' + to_string(i+spalten) + ' ' + to_string(i+spalten*2) + " 0" + '\n';
                }
                else
                {
                    // Rest erste Spalte
                    if (i<=spalten)
                    {
                    conj.clause[0] = conj.clause[0] + ' ' + to_string(i) + ' ' + to_string(i+1) + ' ' + to_string(i+2) + " 0" + '\n';
                    conj.clause[1] = conj.clause[1] + ' ' + to_string(i) + ' ' + to_string(i+spalten) + ' ' + to_string(i+spalten*2) + " 0" + '\n';
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
                                conj.clause[0] = conj.clause[0] + ' ' + to_string(i) + ' ' + to_string(i+1) + ' ' + to_string(i+2) + " 0" + '\n';
                            }
                            else
                            {
                                // Feld das im Rest der letzten 2 Spalten liegt.
                                if((i%spalten)==0 || (i%spalten)==(spalten-1))
                                {
                                    conj.clause[1] = conj.clause[1] + ' ' + to_string(i) + ' ' + to_string(i+spalten) + ' ' + to_string(i+spalten*2) + " 0" + '\n';
                                }
                                else
                                {
                                    // Restliche Felder
                                    conj.clause[0] = conj.clause[0] + ' ' + to_string(i) + ' ' + to_string(i+1) + ' ' + to_string(i+2) + " 0" + '\n';
                                    conj.clause[1] = conj.clause[1] + ' ' + to_string(i) + ' ' + to_string(i+spalten) + ' ' + to_string(i+spalten*2) + " 0" + '\n';
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
struct arra same(int zeilen, string var[])
{
    struct arra conj;
    conj.clause = new string[3] ;
    int pos =0; // Aktuelle Gesamtposition
    for (int i = 2; i<=zeilen; i++)
    {   int sppos = 0 ; // Spaltenzähler für ?


            for (int j = 0; j< var[i].length(); j++)
            {
                pos++;
                bool flag = false ;
                switch (var[i][j])
                {
                    case '?' :
                        {
                            sppos++;
                            conj.clause[0] = conj.clause[0] + ' '+ to_string(pos)   ;
                            conj.clause[1] = conj.clause[1] + ' '+ to_string(-(pos)) ;
                            if (sppos%3 ==0 ) {
                                flag = true;
                                conj.clause[0] = conj.clause[0] + " 0" + '\n' ;
                                conj.clause[1] = conj.clause[1] + " 0" + '\n' ;
                            }
                            break;
                        }
                    case 'B' :
                        {
                             conj.clause[2] = conj.clause[2] + ' ' +to_string(pos) + " 0" + '\n' ;
                             break;
                        }
                    case 'W' :
                        {
                             conj.clause[2] = conj.clause[2] + ' ' +to_string(-(pos)) + " 0" + '\n' ;
                             break;
                        }
                    default : break;
                }
               if ((j+1 == var[i].length()) && (!flag)) {
                  conj.clause[0] = conj.clause[0] + " 0" + '\n' ;
                  conj.clause[1] = conj.clause[1] + " 0" + '\n' ;
               }
            }
    }
    return conj;


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





