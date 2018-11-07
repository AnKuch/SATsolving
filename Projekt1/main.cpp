#include <iostream>
#include <fstream>
#include <string>
#include <limits>
#include <sstream>
#include "fileExtraction.h"
#include "cnf.h"

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
    string x[8] = *oneOnEach(fileLength,spaltenZahlI);
    cout << x[0] << endl;
    return 0;
}



