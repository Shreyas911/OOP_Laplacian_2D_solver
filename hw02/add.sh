# !/bin/bash


### Used to check if we have an integer expression, we emphasize that 1 = +1 = +1.00 i.e. all three are integers for us.
REGEX=^[-+]?[0-9]+[\.]?0*$

### Remove decimal points and zeros at the end
i1=$(echo "$1"| grep -oE "^[+-]?[0-9]+")
i2=$(echo "$2"| grep -oE "^[+-]?[0-9]+")

### If number of arguments = 2 and both are integers then add them.
if [ $# = 2 ] && [[ $1 =~ $REGEX ]] && [[ "$2" =~ $REGEX ]] ; then
	echo "The sum of the numbers $1 and $2 is $(( $i1 + $i2 ))"
else
	echo "ERROR: This script is supposed to add two integers, please provide two command line arguments that are integers."
fi
