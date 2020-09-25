factorial=1
i=$1

### This loop will not run for 0, so we directly have factorial = 1
while [ $i -gt 1 ]; do
	factorial=`expr $factorial \* $i`
	i=`expr $i - 1`
done

echo "The factorial of the number $1 is $factorial"