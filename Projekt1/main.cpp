#include <iostream>
#include <fstream>
#include <string>
#include <limits>
#include <sstream>
#include "fileExtraction.h"
//#include "cnf.h"

std::string* oneOnEach (int,int);
int zeilenSpalten (std::string);
char setVariables (std::string);

using namespace std;


int main(int argc, char *argv[])
{
    char filename[128];
    string line;
    ifstream file;
    int fileLength;
    int zeilenZahlI;
    int spaltenZahlI;
    char variable[100][100][3];

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
        string linear[200];
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
        for (int i = 2; i<=zeilenZahlI; i++)
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
        }

    }
    string x=*oneOnEach(fileLength,spaltenZahlI);
    cout << x[4] << endl;
    return 0;
}
string* oneOnEach (int zeichen, int spalten)
{
    int a=zeichen*3;
    string* clause=new string[8];
    for (int i=1; i<=a; i++)
    {
        int x = i % 3;

        switch (x)
        {
        case 1: break;
        case 2:
            {
                if (i!=2)
                {
                    if (i<(a*3-2))
                    {
                        clause[0] = clause[0] + ' ' + to_string(-i) + ' ' + to_string(-(i+3)) + ' ' + to_string(-(i+6)) + '\n';
                        clause[1] = clause[1] + ' ' + to_string(-i) + ' ' + to_string(-(i+3)) + ' ' + to_string(-(i-3)) + '\n';
                        clause[2] = clause[2] + ' ' + to_string(-i) + ' ' + to_string(-(i+(spalten*3))) + ' ' + to_string(-(i+(spalten*6))) + '\n';
                        clause[3] = clause[3] + ' ' + to_string(-i) + ' ' + to_string(-(i+(spalten*3))) + ' ' + to_string(-(i-(spalten*3))) + '\n';
                        break;
                    }
                    else
                    {
                        clause[1] = clause[1] + ' ' + to_string(-i) + ' ' + to_string(-(i+3)) + ' ' + to_string(-(i-3)) + '\n';
                        clause[3] = clause[3] + ' ' + to_string(-i) + ' ' + to_string(-(i+(spalten*3))) + ' ' + to_string(-(i-(spalten*3))) + '\n';
                        break;
                    }
                }
                else
                {
                    clause[0] = clause[0] + ' ' + to_string(-i) + ' ' + to_string(-(i+3)) + ' ' + to_string(-(i+6)) + '\n';
                    clause[2] = clause[2] + ' ' + to_string(-i) + ' ' + to_string(-(i+(spalten*3))) + ' ' + to_string(-(i+(spalten*6))) + '\n';
                }
            }
        case 0:
            {
                if (i!=3)
                {
                    if (i<(a*3-2))
                    {
                        clause[4] = clause[4] + ' ' + to_string(-i) + ' ' + to_string(-(i+3)) + ' '  + to_string(-(i+6)) + '\n';
                        clause[5] = clause[5] + ' ' + to_string(-i) + ' ' + to_string(-(i+3)) + ' ' + to_string(-(i-3)) + '\n';
                        clause[6] = clause[6] + ' ' + to_string(-i) + ' ' + to_string(-(i+(spalten*3))) + ' ' + to_string(-(i+(spalten*6))) + '\n';
                        clause[7] = clause[7] + ' ' + to_string(-i) + ' ' + to_string(-(i+(spalten*3))) + ' ' + to_string(-(i-(spalten*3))) + '\n';
                        break;
                    }
            }
        }
    }
    cout << clause[1] << endl;
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





