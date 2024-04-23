//
// Created by legion on 2024/4/16.
//
#include <iostream>
#include <boost/filesystem.hpp>
#include "JackTokenizer.h"
#include "CompilationEngine.h"
#include "CodeGen.h"

using namespace boost::filesystem;
using std::cout;
using std::endl;
using std::cerr;

int compile_file(string filename);

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
                    compile_file(dir_Entry.path().string());
                }
            }
        } else {
            compile_file(p.string());
        }
    } else {
        cerr << "Path " << argv[1] << " does not exists." << endl;
        exit(1);
    }

    return 0;
}

/**
 * tokenize and compile the file
 * @param filename
 * @return if compilation success
 */
int compile_file(string filename) {
    cerr << "Parsing: " << filename << endl;
    string input_filename = filename;
    JackTokenizer tokenizer(input_filename);
    tokenizer.compile();

    // pass the output of tokenizer as the input of compilation engine
    string engine_input_filename = tokenizer.get_output_filename();
    string engine_output_filename = engine_input_filename;
    size_t index = engine_output_filename.find("T.xml");
    engine_output_filename.replace(index, 5, ".xml");
    CompilationEngine engine(engine_input_filename, engine_output_filename);
    engine.compile_class();

//     pass the output of compilation engine as the input of the next stage
    string codegen_input_filename = engine.get_output_filename();
    string codegen_output_filename = codegen_input_filename;
    index = codegen_output_filename.find(".xml");
    codegen_output_filename.replace(index, 4, ".vm");
    CodeGen cg(codegen_input_filename, codegen_output_filename);
    cg.generate_class();

    return 0;
}
