#include <iostream>
#include <fstream>
#include <string>
#include <limits>
#include <sstream>
#include "fileExtraction.h"

int zeilenSpalten (string a)
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

int anzahlZeichen (string a)
{
    int x = a.length();
    int iCount	= 0;
	for (int i = 0; i < x; i++)
		if(a[i] != ' ') iCount++;
    return iCount;
}
