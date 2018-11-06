#include <iostream>
#include <fstream>
#include <string>
#include <limits>
#include <sstream>
#include "fileExtraction.h"
using namespace std;

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

