#!/bin/bash
for file1 in $(ls *.s); do
filename=$(basename -- "$file1")
filename="${filename%.*}"
if [ -f "$filename".cor ]; then
rm "$filename".cor &> /dev/null
fi
echo -ne "\033[0;31m"
./asm "$file1" 
echo -ne "\x1b[0m"
if [ -f "$filename".cor ]; then
md5 "$filename.cor" > res1
rm "$filename".cor
else
:>res1
fi
echo -ne "\x1b[32m"
./asm_orig $file1
echo -ne "\x1b[0m"
if [ -f "$filename".cor ]; then
md5 "$filename.cor" > res2
rm "$filename".cor
else
:>res2
fi
diff res1 res2 > res3
if [ -s res3 ]; then
echo "KO---------------------------------------------------$file1 differs from the original output"
else
echo "$file1 ok."
fi
echo ""
done

