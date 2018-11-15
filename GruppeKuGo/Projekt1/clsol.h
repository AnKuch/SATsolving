/*/////////////////////////////////////////////////
////                Gruppe KuGo             ////
////   Andrea Kuchar          Bob Godar    ////
////      10389540             10708175   ////
/////////////////////////////////////////////*/


#include <iostream>
#include <fstream>
#include <string>
#include <limits>
#include <sstream>
#include <algorithm>
#include <vector>
#include <iterator>
#include <numeric>

using namespace std;


std::vector<int> clsol(std::string filename,std::string dir);
std::string oneOnEach (int zeilen, int spalten);
int zeilenSpalten (std::string);
char setVariables (std::string);
std::string sameRo(int, int);
std::string sameCo(int, int);
std::string getInput(std::string filename, int fl);