# Project 7

## Specification

### Arithmetic and Logical Commands

## Implementation

### Standard VM Mapping on the Hack Platform

- RAM[0] `SP` Stack pointer: points to the next topmost location in the stack;
- RAM[1] `LCL` Points to the base of the current VM function’s local segment;
- RAM[2] `ARG` Points to the base of the current VM function’s argument segment;
- RAM[3] `THIS` Points to the base of the current this segment
  (within the heap);
- RAM[4] `THAT` Points to the base of the current that segment
  (within the heap);
- RAM[5–12] Holds the contents of the `temp` segment;
- RAM[13–15] `R13-R15` Can be used by the VM implementation as general purpose registers.
- RAM[16–255] `Static` variables, symbols as `XXX.j` (of all the VM functions in the VM program)
- RAM[256–2047] `Stack`
  **- RAM[2048–16483] `Heap` (used to store** objects and arrays)
- RAM[16384–24575] `Memory` mapped I/O

### Analysis

目前的指令有2种类型：

1. 算数/逻辑指令，只有单个操作命令，如`add`
2. 访存指令，分为`push/pop [type] [value]`，其中`type`有7种

### Design

实现过程:

1. 使用Parser读出每条指令，并拆解出每条指令的不同组成部分
2. 对于算术逻辑指令，在CodeWriter中将其翻译为汇编，并写入输出文件
3. 对于各个访存指令，在CodeWriter中将其翻译为汇编，并写入输出文件

### Todo

- [x] 程序框架搭好
- [ ] 分析所有算术逻辑指令所对应的汇编语句
    - 一元算数逻辑运算
        - add
        - sub
        - and
        - or
    - 二元算数逻辑运算
        - neg
        - not
    - 条件码设置指令
        - eq
        - gt
        - lt
- [ ] 分析所有访存指令所对应的汇编语句
    - [ ] argument
      ```vm
        push/pop argument i
      ```
    - [ ] local
      ```vm
        push/pop local i
      ```
    - [ ] static
      ```vm
        push/pop static i
      ```
    - [ ] constant
      ```vm
        push/pop constant i
      ```
    - [ ] this/that
      ```vm
        push/pop this/that i
      ```
    - [ ] pointer
      ```vm
        push/pop pointer i
      ```
    - [ ] temp
      ```vm
        push/pop temp i
      ```  

- [ ] 分析分支跳转指令所对应的汇编语句
    - label [name]
    - goto [label-name]
    - if-goto [label-name]
- [ ] 分析function语句所对应的汇编语句
    - function f [local_num]
- [ ] 分析call语句所对应的汇编语句
    - call f [arg_num]
- [ ] 分析return语句所对应的汇编语句
    - return
- [ ] 抽象出所有基本操作，并实现他们
- [ ] 利用基本操作实现上述所有的指令翻译过程

## 测试

- [x] SimpleAdd
- [x] StackTest
- [ ] BasicTest
- [ ] PointerTest
- [ ] StaticTest
- [ ] BasicLoop
- [ ] FibonacciSeries
- [ ] FibonacciElement
- [ ] NestedCall
- [ ] SimpleFunction
- [ ] StaticsTest