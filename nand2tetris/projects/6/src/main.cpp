#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include "parse.hh"
using std::cerr;
using std::cin;
using std::cout;
using std::endl;
using std::ifstream;
using std::ofstream;
using std::string;

string compile(string);

int main(int argc, char *argv[])
{
    // open one file for read
    ifstream input(argv[1]);

    // open one file for write
    ofstream output(argv[2]);
    // read the program and translate it
    string line;
    while (std::getline(input, line))
    {
        output << line << endl;
    }
    return 0;
}

string compile(string)
{
}