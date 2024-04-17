#!/usr/bin/env bash
test_files=`ls test/*/*T.xml`
output_files=`ls output/*/*T.xml`
for file in $test_files
do
  output_file=`echo $file|sed -E 's_test_output_g'`
  diff -u --color $file $output_file
done