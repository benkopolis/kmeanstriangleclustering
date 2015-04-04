#!/bin/bash

lines=0
for i in `find . -name \*.h -print -o -name \*.cpp -print -o -name \*.hpp -print` 
do 
	tmp=`wc -l $i | awk {'print $1'}` 
    echo "Tmp: $tmp"
    let lines=$tmp+$lines
done
echo "Total lines: $lines"
