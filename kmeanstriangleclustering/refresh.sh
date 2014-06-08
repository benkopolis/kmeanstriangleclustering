#!/bin/bash

groups=(5 8 10 13 15 20 25)
iterations=(3 5 8 10 13)
data_sets=(`ls -1 data | grep tfidf- | awk '{gsub(/-/, " "); print $1.$2}'`)

echo "Groups: ${#groups[*]}"
echo "Iterations: ${#iterations[*]}"
echo "Data sets: ${#data_sets[*]}"

for data in ${data_sets[*]};
do
	echo $data
done;

cp clustering rel_clustering_test
chmod +x rel_clustering_test 
for data in ${data_sets[*]};
do
	for group in ${groups[*]};
	do
		for iteration in ${iterations[*]};
		do
			echo "rel_clustering_test -res data/${group}g${iteration}i-${data}-out.txt $iteration $group > logs/${group}g${iteration}i_${data}.log"
		done;
	done;
done;
	
