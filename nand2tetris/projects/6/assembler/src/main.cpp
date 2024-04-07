#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include "parser.hh"
using std::cerr;
using std::cin;
using std::cout;
using std::endl;
using std::ifstream;
using std::ofstream;
using std::string;

int main(int argc, char *argv[])
{
    Parser par(argv[1], argv[2]);
    // read the program and translate it
    par.parse();
    return 0;
}