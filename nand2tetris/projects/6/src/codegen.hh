#include <string>
using std::string;
// generate the binaries
class CodeGen
{
private:
public:
    /**  Returns the binary code of the dest mnemonic */
    string dest_bin();
    /** Returns the binary code of the comp mnemonic. */
    string comp_bin();
    /** Returns the binary code of the jump mnemonic */
    string jump_bin();
};