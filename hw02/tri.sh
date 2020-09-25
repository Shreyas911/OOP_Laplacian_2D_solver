# !/bin/bash

# Print the first pyramid of numbers
for i in `seq 1 5`; do
	for ((j = 1; j<=$((5-$i));j++)); do
		echo -n " " 
	done
	for j in `seq $i`; do
		echo -n "$i "
	done
	echo 
done
# Print the second pyramid of dots
for i in `seq 1 5`; do
	for ((j = 1; j<=$((5-$i));j++)); do
		echo -n " " 
	done
	for j in `seq $i`; do
		echo -n ". "
	done
	echo 
done


