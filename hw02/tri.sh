# !/bin/bash

# Print the pyramid of numbers
for ((i = 1; i<=5;i++)); do
	for ((j = 1; j<=$((5-$i));j++)); do
		echo -n " " 
	done
	for  ((j = 1; j<=$i;j++)); do
		echo -n "$i "
	done
	echo 
done
# Print the pyramid of dots
for ((i = 1; i<=5;i++)); do
	for ((j = 1; j<=$((5-$i));j++)); do
		echo -n " " 
	done
	for  ((j = 1; j<=$i;j++)); do
		echo -n ". "
	done
	echo 
done


