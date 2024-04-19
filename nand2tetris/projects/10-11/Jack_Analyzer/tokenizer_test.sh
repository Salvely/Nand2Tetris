#!/usr/bin/env bash
test_files=$(ls test/*/*T.xml)
#output_files=`ls output/*/*.xml`

echo "Comparing T.xml tokenizer files ..."

for file in $test_files; do
  output_file=$(echo $file | sed -E 's_test_output_g')
  diff -u --color $file $output_file >>test_result.txt
done

#echo "Comparing .xml Compilation engine generated files..."
#
#cd "../../../tools"
#
#TextComparer ./output/ArrayTest/Main.xml ./test/ArrayTest/*.xml
#
#TextComparer ./output/Square/Main.xml ./test/Square/Main.xml
#
#TextComparer ./output/Square/Square.xml ./test/Square/Square.xml
#
#TextComparer ./output/Square/SquareGame.xml ./test/Square/SquareGame.xml
#
#TextComparer ./output/ExpressionLessSquare/Main.xml ./test/ExpressionLessSquare/Main.xml
#
#TextComparer ./output/ExpressionLessSquare/Square.xml ./test/ExpressionLessSquare/Square.xml
#
#TextComparer ./output/ExpressionLessSquare/SquareGame.xml ./test/ExpressionLessSquare/SquareGame.xml
#
#cd -
