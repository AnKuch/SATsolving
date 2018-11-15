
/*/////////////////////////////////////////////////
////                Gruppe KuGo             ////
////   Andrea Kuchar          Bob Godar    ////
////      10389540             10708175   ////
/////////////////////////////////////////////*/





#include "clsol.h" 

using namespace std;

struct arra{string *clause;};
int cl = 0;


std::vector<int> clsol(string filename,string dir)
{
    string line;
    ifstream file;
    int fileLength = 0;
    int zeilenZahlI = 0;
    int spaltenZahlI = 0;
    string variablesFix;
    string belegung;
    cl = 0;

    // Puzzel öffnen
    file.open(filename, ios_base::in|ios_base::out);
    if (!file) // Datei konnte nicht geöffnet werden
    {
        cout << "File couldn't be read." << endl;
		std::vector<int> er(1);
		er[0] = 0;
		return er;
    }
    else
    {
		
        // Extrahierung der Zeilen und Spaltenlänge
        string ZS[1] ;
        if (getline(file,line))
        {
            ZS[0]=line;
        }
        zeilenZahlI = zeilenSpalten(ZS[0]);
        spaltenZahlI = zeilenSpalten(ZS[0]);
        fileLength = zeilenZahlI * spaltenZahlI;
		file.close();
		
		
		// Belegungen in String speichern
		// 1 = Schwarz und 0 = Weiß
		belegung = getInput(filename,fileLength);
        for (int i = 0; i<belegung.length(); i++)
        {     
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
	
	
    // maximal zwei benachbarte Felder mit gleicher Farbe 
    string oneOnEachS;
    oneOnEachS = oneOnEach(zeilenZahlI,spaltenZahlI);


    // Zeile/2 schwarze und weiße Belegungen pro Zeile
    string sameR;
    sameR = sameRo(spaltenZahlI,zeilenZahlI);
	
	
    // Spalte/2 schwarze und weiße Belegungen pro Spalte
    string sameC;
    sameC = sameCo(spaltenZahlI,zeilenZahlI);


    //  Öffnung und Leerheitsüberprüfung der Textdateien OutPico.txt (-> Output von Picosat) und
	//  formular.cnf in DIMACS-KNF Format 
    ofstream f;
	ofstream op;
	string dirOutput = dir + "/OutPico.txt" ;
	op.open(dirOutput,std::ifstream::out|std::ifstream::trunc);
	op.close();
	dir = dir + "/formular.cnf";
    f.open(dir,std::ifstream::out|std::ifstream::trunc);
    
	// Header für formular.cnf
    
	f << 'p' << " cnf " << fileLength << ' ' << cl << endl;
	
	// Klauseln holen und in formular.cnf schreiben
	
	f << variablesFix;  
    f << oneOnEachS;
    f << sameR;
    f << sameC;
    f.close();
    
	
	// Picosat starten
	dir = "picosat -o "+ dirOutput +" " + dir;
    system(dir.c_str());
	
	
	// Belegung von Picosat aus OutPico.txt auslesen und in dem Vektor vpd speichern
	string PicoBel = getInput(dirOutput,fileLength);
	std::vector<int>vpb(fileLength+3) ; 
	int j = 0 ;
	fill(vpb.begin(), vpb.end(), 1);
	vpb[fileLength+1] = spaltenZahlI;
	vpb[fileLength+2]= zeilenZahlI;
    for (int i = 0; i<PicoBel.length(); i++)
        {       
                switch (PicoBel[i])
                {
                    case '-' :
                        {   
							 vpb[j] = 0;
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
    
    return vpb;
}


// oneOnEach gibt die KNF aus, die erzwingt und prüft, dass es max. 2 farbgleiche Felder benachbart sind
string oneOnEach (int zeilen, int spalten)
{
    struct arra conj;
    conj.clause = new string[2];
    string clause="" ;
    int pos = 0;
    
	
	// Zeilen KNF
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
    
	
	// Spalten KNF
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


// sameR gibt die KNF aus, die erzwingt und prüft, dass max. Spalten/2 farbgleiche Felder in einer Zeile existieren 
string sameRo(int n, int zeilen)
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
		
		// do-While Schleife erstellt  (zeilen! / ((zeilen-k)! * k!)) k-elementige Permutationen für eine Zeile, d.h. ohne Wiederholungen 
        do {
             for (int i = 0; i < n; i++) {
                int m = i+1+s;
		
			  // selector[i] stellt sicher, dass nur k-elementige Permutationen vorkommen können
                 if (selector[i]) {
                    selectedB.push_back(to_string(m));
					 selectedW.push_back(to_string(-m));
              }
             }
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
		 // prev_permutation() gibt einen lexikalisch immer kleiner werdenden selector aus
		 // z.B. bei einer Zeilenlänge von 4 : selector = 1100 (vor der ersten Iteration) und selector = 1010 (nach der zweiten Iteration) 
    } 
	clause = clauseW + clauseB ;
    return clause;
}


// sameR gibt die KNF aus, die erzwingt und prüft, dass max. Zeilen/2 farbgleiche Felder in einer Spalte existieren 
// Bis auf den Iterationtausch von n und spalten ist sameCo identisch zu sameRo
string sameCo(int n, int zeilen)
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
    }
	clause = clauseW + clauseB ;
    return clause;
}


// Extrahiert die Spalten-und Zeilenlänge
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


// File-to-String Funktion 
std::string getInput(string fn, int fl) {
	
    string linear[fl]; 
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







