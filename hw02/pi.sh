# !/bin/bash
N=$1
PI=$(echo "scale =10; 3.14159265358979323846" | bc -l)
COUNTER=0

for i in `seq $N`;do
	x=$(echo "scale=10; $RANDOM/32767" | bc -l)
	y=$(echo "scale=10; $RANDOM/32767" | bc -l)
	d1=$(echo "scale=10; $x * $x" | bc -l)
	d2=$(echo "scale=10; $y * $y" | bc -l)
	d=$(echo "scale=10; $d1 + $d2" | bc -l)
	if [[ $(echo "scale = 10; $d <= 1.0 " | bc -l) = 1 ]]; then
	 	COUNTER=$(( $COUNTER+1 ))
	fi
	piestimate=$(echo "scale=10; 4*$COUNTER/${N[n]}" | bc -l)
	erel=$(echo "scale=10; sqrt((($PI-$piestimate)/$PI)^2)" | bc -l)
done
echo -n "$N $COUNTER $(($N-$COUNTER)) $piestimate $erel "
