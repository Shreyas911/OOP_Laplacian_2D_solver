# !/bin/bash
REGEX=^[-]?[0-9]+$

if [ $# = 2 ] && [[ $1 =~ $REGEX ]] ; then
	echo "The sum of the numbers $1 and $2 is $(( $1 + $2 ))"
else
	echo "ERROR: This script is supposed to add two integers, please provide two command line arguments that are integers."
fi

