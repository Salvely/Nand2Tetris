C 语言版本如下：

```c
R2 = 0;
for(int i = 0; i < R0; i++) {
    R2 += R1;
}
```

x86_64 汇编语言格式如下：

```x86_64
    mov 0, R2;

    mov 0, i;

loop:
    cmpl i,R0;
    jle end
    addq r1,r2;
    addq 1,i;
    jmp loop;

end:
    ret
```
