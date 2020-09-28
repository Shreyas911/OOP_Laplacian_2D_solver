# !/bin/bash

### To check if we have whole numbers as input
REGEX=^[+]?[0-9]+$

### Initialize factorial
factorial=1

### ignore + sign befor the numbers in input
i=$(echo "$1"| grep -oE "[0-9]+$")

if [ $# = 1 ] && [[ $1 =~ $REGEX ]]; then

	### This loop will not run for 0, so we directly have factorial = 1
	while [ $i -gt 1 ]; do
		factorial=`expr $factorial \* $i`
		i=`expr $i - 1`
	done

	### Print the value of factorial
	echo "The factorial of the number $1 is $factorial"

else
	### Print error message
	echo "ERROR: This script is supposed to find factorials. Please provide only one argument which is a whole number."
fi