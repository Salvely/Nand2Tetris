#ifndef __CODEGEN_HH__
#define __CODEGEN_HH__

#include <string>
#include <vector>
#include <unordered_map>
using std::string;
// generate the binaries
class CodeGen
{
private:
    std::vector<string> dest_table = {"", "M", "D", "MD", "A", "AM", "AD", "AMD"};
    std::vector<string> jump_table = {"", "JGT", "JEQ", "JGE", "JLT", "JNE", "JLE", "JMP"};
    std::unordered_map<string, int> comp_table_a0 = {{"0", 42}, {"1", 63}, {"-1", 58}, {"D", 12}, {"A", 48}, {"!D", 13}, {"!A", 49}, {"-D", 15}, {"-A", 51}, {"D+1", 31}, {"A+1", 55}, {"D-1", 14}, {"A-1", 50}, {"D+A", 2}, {"D-A", 19}, {"A-D", 7}, {"D&A", 0}, {"D|A", 21}};
    std::unordered_map<string, int> comp_table_a1 = {{"M", 48}, {"!M", 49}, {"-M", 51}, {"M+1", 55}, {"M-1", 50}, {"D+M", 2}, {"D-M", 19}, {"M-D", 7}, {"D&M", 0}, {"D|M", 21}};

public:
    /**  Returns the binary code of the dest mnemonic */
    string dest_bin(string dest);
    /** Returns the binary code of the comp mnemonic. */
    string comp_bin(string comp);
    /** Returns the binary code of the jump mnemonic */
    string jump_bin(string jump);
};

#endif