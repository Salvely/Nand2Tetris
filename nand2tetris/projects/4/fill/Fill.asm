// This file is part of www.nand2tetris.org
// and the book "The Elements of Computing Systems"
// by Nisan and Schocken, MIT Press.
// File name: projects/4/Fill.asm

// Runs an infinite loop that listens to the keyboard input. 
// When a key is pressed (any key), the program blackens the screen,
// i.e. writes "black" in every pixel. When no key is pressed, 
// the screen should be cleared.

    @SCREEN // get the address of screen
    D=A
    @address
    M=D // set the current address

(LISTEN)
    @KBD
    D=M // get the keyboard
    @key
    M=D // store the value in key variable
    
    @i
    M=0 // initialize i

(OUTER)
    @8192
    D=A
    @i
    D=M-D
    @OUTER_END
    D;JGE

    // get the key var
    @key
    D=M
    
    // judge if the key == 0
    @WHITE
    D;JEQ
(BLACK)
    @address
    D=M // calculate address
    @i
    A=D+M // calculate address + offset
    M=-1

    @END_IF_ELSE
    0;JMP
(WHITE)
    @address
    D=M // calculate address
    @i
    A=D+M // calculate address + offset
    M=0
(END_IF_ELSE)
    @1
    D=A

    @i
    M=M+1

    @OUTER
    0;JMP 
(OUTER_END)

    @LISTEN
    0;JMP