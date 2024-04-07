#include "codegen.hh"
#include <bitset>
#include <string>

using std::string;

int find_elem(std::vector<string> &vec, string &elem)
{
    int i = 0;
    for (const string& item : vec)
    {
        if (elem == item)
        {
            return i;
        }
        i += 1;
    }
    return -1;
}

string CodeGen::dest_bin(string dest)
{
    int index = find_elem(dest_table, dest);
    return std::bitset<3>(index).to_string();
}

string CodeGen::comp_bin(string comp)
{
    char a = '0';
    if(comp.find('M') != string::npos) {
        a = '1';
    }
//    string comp_bits = comp.substr(1);
    int value;
    if (a == '0')
    {
        value = comp_table_a0[comp];
    }
    else
    {
        value = comp_table_a1[comp];
    }
    string a_bit{a};
    return a_bit + std::bitset<6>(value).to_string();
}

string CodeGen::jump_bin(string jump)
{
    int index = find_elem(jump_table, jump);
    return std::bitset<3>(index).to_string();
}
