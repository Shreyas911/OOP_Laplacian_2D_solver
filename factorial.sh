# !/bin/bash

REGEX=^[+]?[0-9]+$

factorial=1

### ignore + sign in input
i=$(echo "$1"| grep -oE "[0-9]+$")

### This loop will not run for 0, so we directly have factorial = 1
while [ $i -gt 1 ]; do
	factorial=`expr $factorial \* $i`
	i=`expr $i - 1`
done

if [ $# = 1 ] && [[ $1 =~ $REGEX ]]; then
	echo "The factorial of the number $1 is $factorial"
else
	echo "ERROR: This script is supposed to find factorials. Please provide only one argument which is a whole number."
fi