//
// Created by legion on 2024/4/16.
//
#include <iostream>
#include <boost/filesystem.hpp>
#include "JackTokenizer.h"
#include "CompilationEngine.h"

using namespace boost::filesystem;
using std::cout;
using std::endl;
using std::cerr;

int main(int argc, char *argv[]) {
    // read the filename/directory name from the command line
    if (argc != 2) {
        cout << "Usage: ./Jack_Analyzer.exe [filename]/[directory_name]" << endl;
        exit(1);
    }
    path p{argv[1]};
    if (exists(p)) {
        string input_filename;
        if (is_directory(p)) {
            recursive_directory_iterator iter(p);
            for (auto &dir_Entry: iter) {
                if (!dir_Entry.is_directory() && dir_Entry.path().string().find(".jack") != string::npos) {
                    cout << "Parsing: " << dir_Entry.path().string() << endl;
                    input_filename = dir_Entry.path().string();
                    JackTokenizer tokenizer(input_filename);
                    tokenizer.compile();
                }
            }
        } else {
            cout << "Parsing: " << p.string() << endl;
            input_filename = p.string();
            JackTokenizer tokenizer(input_filename);
            tokenizer.compile();
        }
    } else {
        cerr << "Path " << argv[1] << " does not exists." << endl;
        exit(1);
    }

    return 0;
}
