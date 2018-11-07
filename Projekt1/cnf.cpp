#include <iostream>
#include <fstream>
#include <string>
#include <limits>
#include "cnf.h"

using namespace std;

string* oneOnEach (int zeichen, int spalten)
{
    int a=zeichen*3;
    string* clause=new string[8];
    for (int i=1; i<=a; i++)
    {
        switch (i%3)
        {
        case 0: break;

        case 1:
            {
                clause[0] = clause[0] + to_string(-i) + ' ' + to_string(-(i+3)) + ' ' to_string(-(i+6)) + '\n';
                clause[1] = clause[1] + to_string(-i) + ' ' + to_string(-(i+3)) + ' ' to_string(-(i-3)) + '\n';
                clause[2] = clause[2] + to_string(-i) + ' ' + to_string(-(i+(spalten*3))) + ' ' to_string(-(i+(spalten*6))) + '\n';
                clause[3] = clause[3] + to_string(-i) + ' ' + to_string(-(i+(spalten*3))) + ' ' to_string(-(i-(spalten*3))) + '\n';
            }
        case 2:
            {
                clause[4] = clause[4] + to_string(-i) + ' ' + to_string(-(i+3)) + ' ' to_string(-(i+6)) + '\n';
                clause[5] = clause[5] + to_string(-i) + ' ' + to_string(-(i+3)) + ' ' to_string(-(i-3)) + '\n';
                clause[6] = clause[6] + to_string(-i) + ' ' + to_string(-(i+(spalten*3)) + ' ' to_string(-(i+(spalten*6)) + '\n';
                clause[7] = clause[7] + to_string(-i) + ' ' + to_string(-(i+(spalten*3)) + ' ' to_string(-(i-(spalten*3)) + '\n';
            }
        }
    }
    return clause;
}
