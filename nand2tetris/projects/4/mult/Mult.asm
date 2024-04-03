// This file is part of www.nand2tetris.org
// and the book "The Elements of Computing Systems"
// by Nisan and Schocken, MIT Press.
// File name: projects/4/Mult.asm

// Multiplies R0 and R1 and stores the result in R2.
// (R0, R1, R2 refer to RAM[0], RAM[1], and RAM[2], respectively.)
// The algorithm is based on repetitive addition.

    @0
    D=A
    @R2
    M=D // RAM[2] = 0
    
    @0
    D=A
    @temp
    M=D // RAM[temp] = 0
    
(LOOP)
    
    @temp
    D=M // calculate i -> D
    @R0 // calculate RAM[0] -> M
    D=M-D // calculate RAM[0] - i -> M - D
    @END
    D;JLE // if <=, goto end

    
    @R1
    D=M // calculate RAM[1]
    @R2 // calculate RAM[2]
    M=M+D // RAM[2] = RAM[2] + RAM[1] 
    
    @temp // calculate i
    M=M+1 // i = i + 1
    
    @LOOP
    0;JMP // JMP (LOOP)
(END)
    @END
    0;JMP
