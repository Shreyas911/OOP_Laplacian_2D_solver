# !/bin/bash


### Used to check if we have an integer expression, we emphasize that 1 = +1 = +1.00 i.e. all three are integers for us.
REGEX=^[+-]?[0-9]+$

### If number of arguments = 2 and both are integers then add them.
if [ $# = 2 ] && [[ $1 =~ $REGEX ]] && [[ "$2" =~ $REGEX ]] ; then
	echo "The sum of the numbers $1 and $2 is $(( $1 + $2 ))"
else
	echo "ERROR: This script is supposed to add two integers, please provide two command line arguments that are integers."
fi
