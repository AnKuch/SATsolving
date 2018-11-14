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

#include "clsol.h" 

using namespace std;

struct arra{string *clause;};
int cl = 0;

std::vector<int> clsol(string filename,string dir)
{
   // char filename[128];
    string line;
    ifstream file;
    int fileLength;
    int zeilenZahlI;
    int spaltenZahlI;
    string variablesFix;
    string belegung;


    // Dateinamen einlesen
   // cout << "Which puzzle would you like to be solved?" << endl;
    //cin.getline(filename, 127);

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
		file.close();
		belegung = getInput(filename,fileLength);

        cout << " csd" << belegung.length()<<endl;
        // Belegungen in String speichern
        for (int i = 0; i<belegung.length(); i++)
        {       cout << " csd" << belegung[i]<<endl;
                switch (belegung[i])
                {
                    case 'B' :
                        {
                            variablesFix = variablesFix + to_string(i+1) + " 0" + '\n';
                            cl++;
                            break;
                        }
                    case 'W' :
                        {
                            variablesFix = variablesFix + to_string(-(i+1)) + " 0" + '\n';
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
    sameBlack = sameR(spaltenZahlI,zeilenZahlI);
    // N/2 weiße pro Zeile
    string sameWhite;
    sameWhite = sameC(spaltenZahlI,zeilenZahlI);
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
	ofstream op;
    //fh.open("hilfsdatei.txt",ios::in);
	string dirOutput = dir + "/OutPico.txt" ;
	op.open(dirOutput,std::ifstream::out|std::ifstream::trunc);
	op.close();
	dir = dir + "/formular.cnf";
    f.open(dir,std::ifstream::out|std::ifstream::trunc);
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
    f.close();
    // Picosat starten
	dir = "picosat -o "+ dirOutput +" " + dir;
	cout <<"dir : "<<dir.c_str()<<endl;
    system(dir.c_str());
	
	
	string PicoBel = getInput(dirOutput,fileLength);
	std::vector<int>vpb(fileLength+3) ; 
	int j = 0 ;
	fill(vpb.begin(), vpb.end(), 1);
	vpb[fileLength+1] = spaltenZahlI;
	cout <<"ff : "<<spaltenZahlI<<endl;
	vpb[fileLength+2]= zeilenZahlI;
    for (int i = 0; i<PicoBel.length(); i++)
        {       
			    cout<<"Picobel i "<< j<<endl;
                switch (PicoBel[i])
                {
                    case '-' :
                        {   
							 vpb[j] = 0;
							 cout<<"pb "<<j<<endl;
                            break;
                        }
					 case ' ' : 
					     {
						     j++;
							 break;
					     }	
                    default :
                        {   
                            break;
                        }
                }
        }
	cout <<"ff : "<<vpb[2]<<endl;

    return vpb;
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

    }
    return clause;
}

string sameR(int n, int zeilen)
{
    int k= (n/2)+1;
	string clause="";
    string clauseB ="";
    string clauseW ="";
    for (int l=0; l<zeilen; l++)
    {
        int s = l*n;
        vector<string> selectedB;
		vector<string> selectedW;
        vector<bool> selector(n);
        fill(selector.begin(), selector.begin() + k, true);
        do {
             for (int i = 0; i < n; i++) {
              int m = i+1+s;
              if (selector[i]) {
                    selectedB.push_back(to_string(m));
					 selectedW.push_back(to_string(-m));
              }
             }
             //     combinations.push_back(selected);
             for(std::vector<std::string>::const_iterator i = selectedB.begin(); i != selectedB.end(); i++)
             {
                 clauseB = clauseB + *i + ' ';
             }
			 
		     for(std::vector<std::string>::const_iterator i = selectedW.begin(); i != selectedW.end(); i++)
             {
                 clauseW = clauseW + *i + ' ';
             }
			  
			  selectedW.clear();
             clauseW = clauseW + " 0" + '\n';
             selectedB.clear();
             clauseB = clauseB + " 0" + '\n';
             cl = cl + 2;
         }
         while (prev_permutation(selector.begin(), selector.end()));
    // print integers and permute bitmask
    } 
	clause = clauseW + clauseB ;
    return clause;
}
string sameC(int n, int zeilen)
{
    int k = (zeilen/2)+1;
    string clause = "";
	string clauseB ="";
    string clauseW ="";
	
    for (int j=0; j<n; j++)
    {
        vector<string> selectedB;
		vector<string> selectedW;
        vector<bool> selector(n);
        fill(selector.begin(), selector.begin() + k, true);
        do {
             for (int i = 0; i < zeilen; i++) {
				 int s = i*zeilen;
                int m = (j+1)+s;
              if (selector[i]) {
				     selectedB.push_back(to_string(m));
                    selectedW.push_back(to_string(-m));
              }
             }
             //     combinations.push_back(selected);
             for(std::vector<std::string>::const_iterator i = selectedB.begin(); i != selectedB.end(); i++)
             {
                 clauseB = clauseB + *i + ' ';
             }
             for(std::vector<std::string>::const_iterator i = selectedW.begin(); i != selectedW.end(); i++)
             {
                 clauseW = clauseW + *i + ' ';
             }
			  
			  selectedW.clear();
             clauseW = clauseW + " 0" + '\n';
             selectedB.clear();
             clauseB = clauseB + " 0" + '\n';
             cl = cl + 2;
         }
         while (prev_permutation(selector.begin(), selector.end()));
    // print integers and permute bitmask
    }
	clause = clauseW + clauseB ;
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
std::string getInput(string fn, int fl) {
    string linear[fl]; 
	//std::vector<String>  belegung;
	string belegung;
	int nLines = 0  ;
	ifstream file ;
	string line;

	
	file.open(fn, ios_base::in|ios_base::out);
	while (getline(file,line))
	{
	   linear[nLines]=line;
	   nLines++;
	}
	 for (int i= 1; i< nLines; i++)
	{   
	   belegung = belegung + linear[i];
	} 
	
	return belegung;
}







