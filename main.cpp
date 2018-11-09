#include <iostream>
#include <fstream>
#include <string>
#include <limits>
#include <sstream>
#include "fileExtraction.h"
//#include "cnf.h"

struct arra oneOnEach (int zeichen, int spalten);
int zeilenSpalten (std::string);
char setVariables (std::string);
struct arra same(int zeilen, std::string var[]);

using namespace std ;
struct arra{string  *clause ;};

int main(int argc, char *argv[])
{
    char filename[128];
    string line;
    ifstream file;
    int fileLength;
    int zeilenZahlI;
    int spaltenZahlI;
    char variable[100][100][3];
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
        cout << spaltenZahlI << " Spalten" << endl;
        fileLength = zeilenZahlI * spaltenZahlI;
        // Belegungen Charvariablen zuweisen
       /* for (int i = 2; i<=zeilenZahlI; i++)
        {
            for (int j = 1; j<= linear[i].length(); j++)
            {
                switch (linear[i][j])
                {
                    case '?' :
                        {
                            variable[i-1][j][0] = 1;
                            variable[i-1][j][1] = 0;
                            variable[i-1][j][2] = 0;
                        }
                    case 'B' :
                        {
                            variable[i-1][j][0] = 0;
                            variable[i-1][j][1] = 1;
                            variable[i-1][j][2] = 0;
                        }
                    case 'W' :
                        {
                            variable[i-1][j][0] = 0;
                            variable[i-1][j][1] = 0;
                            variable[i-1][j][2] = 1;
                        }
                }

            }
        } */

    }
    struct arra x;
    x = oneOnEach(fileLength,spaltenZahlI);
    cout << x.clause[0] << endl;
    struct arra y;
    y = same(zeilenZahlI,linear) ;
    cout << y.clause[2] << endl;
    return 0;
}
// 1 = schwarz 0 = weiß
struct arra oneOnEach (int zeichen, int spalten)
{
    struct arra conj;
    conj.clause = new string[4] ;
    for (int i=1; i<=zeichen; i++)
    {
        if (i!=1)
        {
            if (i<zeichen)
            {
                conj.clause[0] = conj.clause[0] + ' ' + to_string(-i) + ' ' + to_string(-(i+1)) + ' ' + to_string(-(i+2)) + '\n';
                conj.clause[1] = conj.clause[1] + ' ' + to_string(-i) + ' ' + to_string(-(i+1)) + ' ' + to_string(-(i-1)) + '\n';
                conj.clause[2] = conj.clause[2] + ' ' + to_string(-i) + ' ' + to_string(-(i+spalten)) + ' ' + to_string(-(i+spalten)) + '\n';
                conj.clause[3] = conj.clause[3] + ' ' + to_string(-i) + ' ' + to_string(-(i+spalten)) + ' ' + to_string(-(i-spalten)) + '\n';
            }
            else
            {
                conj.clause[1] = conj.clause[1] + ' ' + to_string(-i) + ' ' + to_string(-(i+1)) + ' ' + to_string(-(i-1)) + '\n';
                conj.clause[3] = conj.clause[3] + ' ' + to_string(-i) + ' ' + to_string(-(i+spalten)) + ' ' + to_string(-(i-spalten)) + '\n';
            }
        }
        else
        {
            conj.clause[0] = conj.clause[0] + ' ' + to_string(-i) + ' ' + to_string(-(i+1)) + ' ' + to_string(-(i+2)) + '\n';
            conj.clause[2] = conj.clause[2] + ' ' + to_string(-i) + ' ' + to_string(-(i+spalten)) + ' ' + to_string(-(i+spalten)) + '\n';
        }
    }
    return conj;
}

struct arra same(int zeilen, string var[]) {
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
                                conj.clause[0] = conj.clause[0] + '\n' ;
                                conj.clause[1] = conj.clause[1] + '\n' ;
                            }
                            break;
                        }
                    case 'B' :
                        {
                             conj.clause[2] = conj.clause[2] + ' ' +to_string(pos) + '\n' ;
                             break;
                        }
                    case 'W' :
                        {
                             conj.clause[2] = conj.clause[2] + ' ' +to_string(-(pos)) + '\n' ;
                             break;
                        }
                    default : break;
                }
               if ((j+1 == var[i].length()) && (!flag)) {
                  conj.clause[0] = conj.clause[0] + '\n' ;
                  conj.clause[1] = conj.clause[1] + '\n' ;
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





