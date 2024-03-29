files=$(find . -name "todos")
for file in $files; do
    mv $file $(echo $file | sed -e "s_todos_todos.md_g")
done
