#include "CodeWriter.hh"
#include "common.h"
#include <sstream>
#include <iostream>
#include <algorithm>

using std::ostringstream;
using std::endl;
using std::cerr;

CodeWriter::CodeWriter(string output_file) {
    output.open(output_file, std::ios_base::app);
    ret_count = 0;
    if_count = 0;
    function_name = "main";
}

CodeWriter::~CodeWriter() {
    close();
}

void CodeWriter::set_file_name(string filename) {
    this->filename = filename;
}

void CodeWriter::SP_decrease() {
    output << "@SP" << endl;
    output << "M=M-1" << endl;
}

void CodeWriter::SP_increase() {
    output << "@SP" << endl;
    output << "M=M+1" << endl;
}

void CodeWriter::ref_deref_pt(bool deref, const string &segment, int index) {
    output << "@" << segment << endl;
    if (segment == "SP") {
        output << "A=M" << endl;
    } else {
        if (index < 0)
            output << "A=M" << index << endl;
        else
            output << "A=M+" << index << endl;
    }
    if (deref)
        output << "D=M" << endl;
    else
        output << "M=D" << endl;
}

void CodeWriter::obtain_pt(const string &pointer, int offset) {
    output << "@" << pointer << endl;
    if (offset == 0) {
        output << "D=M" << endl;
    } else {
        if (offset > 0) {
            output << "D=M+" << offset << endl;
        } else {
            output << "D=M" << offset << endl;
        }
    }
}

void CodeWriter::reassign_pt(const string &pointer, int offset) {
    output << "@" << pointer << endl;
    if (offset == 0) {
        output << "M=D" << endl;
    } else {
        if (offset > 0) {
            output << "M=D+" << offset << endl;
        } else {
            output << "M=D" << offset << endl;
        }
    }
}

void CodeWriter::basic_push(string segment, int index) {
    if (segment == "SP" || segment == "constant") {
        // basic push D
        /**
         * *SP = D
         * SP = SP + 1
         */
        if (segment == "constant") {
            output << "@" << index << endl;
            output << "D=A" << endl;
        }
        ref_deref_pt(false);
        SP_increase();
    } else {
        // segment push from D
        if (segment == "static") {
            segment = filename + "." + std::to_string(index);
        }
        /**
         * *(segment + index) = D
         */
        ref_deref_pt(false, segment, index);
    }
}

void CodeWriter::basic_pop(string segment, int index) {
    if (segment == "SP") {
        // basic pop D
        /**
         * SP = SP - 1
         * D = *SP
         */
        SP_decrease();
        ref_deref_pt(true);
    } else {
        // segment pop to D
        if (segment == "static") {
            segment = filename + "." + std::to_string(index);
        }
        /**
         * D=*(segment+index)
         */
        ref_deref_pt(true, segment, index);
    }
}

void CodeWriter::write_branch(string condition) {
    output << "@branch_true" << if_count << endl;
    if (condition == "eq") {
        output << "D;JEQ" << endl;
    } else if (condition == "gt") {
        output << "D;JGT" << endl;
    } else if (condition == "lt") {
        output << "D;JLT" << endl;
    } else {
        std::cerr << "Illegal command: " << condition << endl;
        exit(1);
    }
    output << "(branch_false" << if_count << ")" << endl;
    output << "D=0" << endl;
    output << "@end_branch" << if_count << endl;
    output << "0;JMP" << endl;
    output << "(branch_true" << if_count << ")" << endl;
    output << "D=-1" << endl;
    output << "(end_branch" << if_count << ")" << endl;
    if_count += 1;
}

void CodeWriter::write_arithmetic(string command) {
    if (std::find(binary_command.begin(), binary_command.end(), command) != binary_command.end()) {
        /**
         *      SP = SP - 1
         *      D = *SP
         *      SP = SP - 1
         *      *SP = D op (*SP)
         *      SP = SP + 1
         */
        basic_pop();
        SP_decrease();
        output << "@SP" << endl;
        output << "A=M" << endl;
        if (command == "add") {
            output << "M=D+M" << endl;
        } else if (command == "sub") {
            output << "M=M-D" << endl;
        } else if (command == "and") {
            output << "M=D&M" << endl;
        } else if (command == "or") {
            output << "M=D|M" << endl;
        } else {
            cerr << "Illegal Command: " << command << endl;
            exit(1);
        }
        SP_increase();
    } else if (std::find(uary_command.begin(), uary_command.end(), command) != uary_command.end()) {
        /**
         *      SP = SP - 1
         *      D = *SP
         *      *SP = op D
         *      SP = SP + 1
         */
        SP_decrease();
        ref_deref_pt(true);
        output << "@SP" << endl;
        output << "A=M" << endl;
        output << "M=";
        if (command == "neg") {
            output << "-D" << endl;
        } else if (command == "not") {
            output << "!D" << endl;
        } else {
            cerr << "Illegal command: " << command << endl;
            exit(1);
        }
        SP_increase();
    } else if (std::find(condition_command.begin(), condition_command.end(), command) != condition_command.end()) {
        /**
        *       binary subtraction first
         *      SP = SP - 1
         *      D = *SP
         *      if(D op 0)
         *          *SP = -1
         *      else
         *          *SP = 0
         *      end
         *      SP = SP + 1
        */
        write_arithmetic("sub");
        basic_pop();
        write_branch(command);
        basic_push();
    } else {
        std::cerr << "Illegal Command: " << command << std::endl;
        exit(1);
    }
}

void CodeWriter::write_push_pop(c_type type, string segment, int index) {
    /**
     * Push segment index
     *      D = *(segment + i)
     *      push D
     *
     * pop segment index
     *      pop D
     *      *(segment + i) = D
     */
    if (type == C_PUSH) {
        basic_push(segment, index);
    } else {
        basic_pop(segment, index);
    }
}

void CodeWriter::write_init() {
    /**
     * SP = 256
     * Call Sys.init
     */
    output << "@256" << endl;
    output << "D=A" << endl;
    reassign_pt();
    write_call("Sys.init", 0);
}

void CodeWriter::write_label(string label) {
    /**
     * (function_name$label)
     */
    output << "(" << function_name << "$" << label << ")" << endl;
}

void CodeWriter::write_goto(string label) {
    /**
     * @function_name$label
     * JMP
     */
    output << "@" << function_name << "$" << label << endl;
    output << "0;JMP" << endl;
}

void CodeWriter::write_if(string label) {
    /**
     * Pop D
     * @function_name$label
     * JNE
     */
    basic_pop();
    output << "@" << function_name << "$" << label << endl;
    output << "JNE" << endl;
    exit(1);
}

void CodeWriter::write_call(string function_name, int arg_num) {
    /**
     * return_address的label是function_name$ret.i),i为第i个return编号
     * push return-address // (Using the label declared below)
        push LCL // Save LCL of the calling function
        push ARG // Save ARG of the calling function
        push THIS // Save THIS of the calling function
        push THAT // Save THAT of the calling function
        ARG = SP-n-5 // Reposition ARG (n ¼ number of args.)
        LCL = SP // Reposition LCL
        goto f // Transfer control
        (return-address) // Declare a label for the return-address
     */
    // push return address
    string return_addr = "@" + function_name + "$ret." + std::to_string(ret_count);
    reassign_pt(return_addr);
    basic_push();
    // push LCL
    reassign_pt("LCL");
    basic_push();
    // push ARG
    reassign_pt("ARG");
    basic_push();
    // push THIS
    reassign_pt("THIS");
    basic_push();
    // push that
    reassign_pt("THAT");
    basic_push();
    int offset = -(arg_num + 5);
    obtain_pt("SP", offset);
    reassign_pt("ARG");
    obtain_pt();
    reassign_pt("LCL");
    write_goto(function_name);
    output << "(" << return_addr << ")" << endl;
    ret_count += 1;
}

void CodeWriter::write_return() {
    /**
     *  FRAME = LCL // FRAME is a temporary variable
        RET = *(FRAME-5) // Put the return-address in a temp. var.
        *ARG = pop() // Reposition the return value for the caller
        SP = ARG+1 // Restore SP of the caller
        THAT = *(FRAME-1) // Restore THAT of the caller
        THIS = *(FRAME-2) // Restore THIS of the caller
        ARG = *(FRAME-3) // Restore ARG of the caller
        LCL = *(FRAME-4) // Restore LCL of the caller
        goto RET // Goto return-address (in the caller’s code)
     */
    ref_deref_pt(true, "LCL", -5);
    output << "@temp" << endl;
    output << "M=D" << endl;
    basic_pop();
    ref_deref_pt(false, "ARG");
    obtain_pt("ARG", 1);
    reassign_pt("SP");
    ref_deref_pt(true, "LCL", -1);
    reassign_pt("THAT");
    ref_deref_pt(true, "LCL", -2);
    reassign_pt("THIS");
    ref_deref_pt(true, "LCL", -3);
    reassign_pt("ARG");
    ref_deref_pt(true, "LCL", -4);
    reassign_pt("LCL");
    output << "@temp" << endl;
    output << "0;JMP" << endl;
}

void CodeWriter::write_function(string function_name, int local_num) {
    /**
     * (function_name)
     * push 0(local_num times)
     */
    this->function_name = function_name;
    output << "(" << function_name << ")" << endl;
    output << "@0" << endl;
    output << "D=A" << endl;
    for (int i = 0; i < local_num; i++) {
        basic_push();
    }
}

void CodeWriter::close() {
    output.close();
}