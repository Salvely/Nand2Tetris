#include "Parser.hh"
#include "CodeWriter.hh"
#include <iostream>
#include <string>
#include <filesystem>

using std::string;
using recursive_directory_iterator = std::filesystem::recursive_directory_iterator;

int main(int argc, char *argv[]) {
    if (argc != 3) {
        std::cerr << "Usage: ./translator [input file/directory] [output.asm]" << std::endl;
        exit(1);
    }
    // judge if the input is a directory
    if(string(argv[1]).find(".vm") == string::npos) {
        // for each file in the directory, parse them and write to the output file
        for (const auto& dirEntry : recursive_directory_iterator(argv[1])) {
            std::cout << "log: Parsing " << dirEntry.path() << std::endl;
            string filename = dirEntry.path().string();
            Parser par(filename,argv[2]);
            par.compile();
        }
    }
    else {
        // parse the .vm file and write to the output file
        std::cout << "log: Parsing " << argv[1] << std::endl;
        Parser par(argv[1],argv[2]);
        par.compile();
    }
    return 0;
}