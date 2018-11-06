#include <iostream>
#include <fstream>
#include <string>
#include <limits>
#include <sstream>
#include "fileExtraction.h"

using namespace std;


int main(int argc, char *argv[])
{
    char filename[128];
    string line;
    ifstream file;
    string inhalt;
    int fileLength;
    int variable[fileLength];
    int x1;
    int x2;

    // Dateinamen einlesen
    cout << "Welches Puzzle soll eingelesen werden?" << endl;
    cin.getline(filename, 127);

    // Datei öffnen
    file.open(filename, ios_base::in|ios_base::out);
    if (!file) // Datei konnte nicht geöffnet werden
    {
        cout << "Datei konnte nicht geöffnet werden." << endl;
    }
    else
    {
        string linear[200];
        int l=1;
        // Anzahl der Zeichen um nötige Zahl der Variablen zu ermitteln
        while (getline(file,line))
        {
            inhalt = inhalt + line;
            fileLength = anzahlZeichen(inhalt);
            linear[l]=line;
            l++;
        }
        int zeilenZahlI = zeilenSpalten(linear[1]);
        cout << zeilenZahlI << " Zeilen" << endl;
        string zeile = to_string(zeilenZahlI);
        int x= zeile.length();
        linear[1] = linear[1].erase(0,x);
        int spaltenZahlI = zeilenSpalten(linear[1]);
        cout << spaltenZahlI << " Spalten" << endl;

    }
    return 0;
}



