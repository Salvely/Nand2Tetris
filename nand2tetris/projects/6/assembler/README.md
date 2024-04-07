main 函数中：
创建一个 parser 对象，传入两个文件名初始化

parser 中首先初始化中建立两个 fstream 对象，然后在 parse 中遵循如下逻辑：

```cpp
int addr_count = 16;
// initialize the symbol_table
symbol_table();
// first have a whole scan to determine the address of the labels
int line = 1;
while(hasNextCommand()) {
    advance();
    type = command_type();
    if(type == white_space) {
        continue;
    }
    else if(type == C_instruction || A_instruction) {
        line += 1；
    }
    else if(type == L_instruction) {
        symbol_table.add_entry({label,line});
    }
}

// then have a second scan to record the variable and instructions
fseek(file,SEEK_CUR,0);
while(hasNextCommand()) {
    advance();
    type = command_type();
    if(type == white_space) {
        continue;
    }
    else if(type == C_instruction) {
        dest = dest();
        comp = comp();
        jump = jump();
        string dest_bin = dest_bin();
        string comp_bin = comp_bin();
        string jump_bin = jump_bin();
        string command = dest+comp+jump; //或者其他顺序
        write_to_file(command);
    }
    else if(type == A_instruction) {
        // judge if @xxx is a decimal number or a variable
        if(xxx == decimal_number) {
            string command = 0+bin(decimal_number);
            write_to_file(command);
        }
        else {
            // serach the entry in the symbol_table
            if(symbol_table.contains(variable)) {
                address = symbol_table.get_address(varibale);
                string command = 0 + bin(address);
                write_to_file(command);
            }
            else {
               string command = 0 + bin(addr_count);
                symbol_table.add_Entry({variable,addr_count});
                addr_count += 1; 
                write_to_file(command);
            }
        }
    }
}
```
