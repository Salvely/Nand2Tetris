- [x] 逐行读取程序并输出到一个文件
- [ ] 在逐行读取的过程中去除空行，空格，注释行
- [ ] 逐条翻译指令(不含 symbols 版本)，翻译时使用一个行数标记`n`来实现行数记录
- [ ] symbols
  - [ ] predefined symbols
    - [ ] 设置一个符号表，将预定义的符号的值放在表中
    - [ ] 在翻译指令的过程中，判断是否为预定义的符号，如果是则将其转译为符号表中的内容
  - [ ] label(`(label)`)
    - [ ] 两遍扫描，第一遍记录 label 定义的位置，将其填入符号表中
    - [ ] 第二遍将所有的 label 替换为符号表中的值
  - [ ] variable(`@variable`)
    - [ ] 设置一个变量计数值，从 16 开始
    - [ ] 每遇到一个变量，查看其是否在符号表中存在
      - [ ] 如果不存在，将计数值标记为它的地址，添加到符号表中，将其值替换为该值，计数值+1
      - [ ] 如果存在，将该值替换为符号表中的地址值
