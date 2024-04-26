#!/bin/bash
dirs=$(ls -l | grep ^d | cut -d" " -f 12)
# $ ls ../../tools/OS
# Array.vm Keyboard.vm Math.vm Memory.vm Output.vm Screen.vm String.vm Sys.vm
for dir in $dirs; do
    cp ../../tools/OS/* $dir
done

jack_files=$(ls | grep .jack)
for file in $jack_files; do
    source=$(echo $file | cut -d'.' -f 1)
    test=$(echo "${source}Test")
    cp $file $test
done
