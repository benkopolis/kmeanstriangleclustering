#! /bin/bash

files=`find . -name \*ut.hpp -print -o -name \*ut.cpp -print -o -name \*ui.hpp -print`
array=[]
split=[]
IFS='\n' read -a array <<< "$files"
for path in `find . -name \*ut.hpp -print -o -name \*ut.cpp -print -o -name \*ut.h -print`
do
    IFS='/' read -a split <<< "$path" 
    echo "SRC: $path"
    if [ ! -d "src/test/${split[3]}" ]; then
        mkdir src/test/${split[3]} 
    fi
    mv $path src/test/${split[3]}/${split[5]}
done

echo "Done."
 
