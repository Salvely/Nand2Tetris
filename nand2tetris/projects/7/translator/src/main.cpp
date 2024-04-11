#include "Parser.hh"
#include <iostream>
#include <string>
#include <boost/filesystem.hpp>

using std::string;
using namespace boost::filesystem;

int main(int argc, char *argv[]) {
    if (argc != 3) {
        std::cerr << "Usage: ./translator [input file/directory] [output.asm]" << std::endl;
        exit(1);
    }
    // judge if the input is a directory
    if (string(argv[1]).find(".vm") == string::npos) {
        path p{argv[1]};
        // for each file in the directory, parse them and write to the output file
        for (auto &dir_Entry: boost::filesystem::recursive_directory_iterator(p)) {
            if (!dir_Entry.is_directory() && dir_Entry.path().filename().string().find(".vm") != string::npos) {
                std::cout << "log: Parsing " << dir_Entry.path().string() << std::endl;
                string filename = dir_Entry.path().string();
                Parser par(filename, argv[2]);
                par.compile();
            }
        }
    } else {
        // parse the .vm file and write to the output file
        std::cout << "log: Parsing " << argv[1] << std::endl;
        Parser par(argv[1], argv[2]);
        par.compile();
    }
    return 0;
}