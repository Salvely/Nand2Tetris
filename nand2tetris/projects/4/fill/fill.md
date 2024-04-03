Fill 的 C 语言循环如下：

```c
while(true) {
    // listen to keyboard
    key = getkey();
    address = screen起始地址
    // render the screen
    for(int row = 0; row < 256; row++) {
        // offset = 0
        for(int col = 0; col < 32; col++) {
            if(key != 0)
                RAM[address+col]=-1
            else
                RAM[address+col]=0
            // offset=offset+1
        }
        address = address + 32
    }
}
```

转化为 HACK 指令如下：

```hack
    @SCREEN // get the address of screen
    D=A
    @address
    M=D // set the current address

(LISTEN)
    @KBD
    D=M // get the keyboard
    @key
    M=D // store the value in key variable
    
    @row
    M=0 // initialize row

(OUTER)
    @256
    D=A
    @row
    D=M-D
    @OUTER_END
    D;JGE

    // set the offset
    @offset
    M=0
    
    @col
    M=0
(INNER)
    @32
    D=A
    @col
    D=M-D
    @INNER_END
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
    @offset
    A=D+M // calculate address + offset
    M=-1

    @END_IF_ELSE
    0;JMP
(WHITE)
    @address
    D=M // calculate address
    @offset
    A=D+M // calculate address + offset
    M=0
(END_IF_ELSE)
    @1
    D=A
    // increment the offset
    @offset
    M=M+D

    @col
    M=M+1

    @INNER
    0;JMP
(INNER_END)
    @32
    D=A
    // increment the address
    @address
    M=M+D

    @row
    M=M+1

    @OUTER
    0;JMP 
(OUTER_END)

    @LISTEN
    0;JMP
```

这搞得太复杂了，应该是：
```c
while(true) {
    // listen to keyboard
    key = getkey();
    address = screen起始地址
    // render the screen
    for(int i = 0; i < 8192; i++) {
        if(key != 0)
            RAM[address+i]=-1
        else
            RAM[address+i]=0
    }
}
```

写为hack指令应该是:
```hack
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
```