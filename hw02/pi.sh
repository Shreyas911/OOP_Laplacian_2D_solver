# !/bin/bash

### Total number of points
N=$1

### Actual value of PI
PI=$(echo "scale =10; 3.14159265358979323846" | bc -l)

### Count points inside the circle
N_i=0

for i in `seq $N`;do
	### Randomly generate x and y between 0 and 1.
	x=$(echo "scale=10; $RANDOM/32767" | bc -l)
	y=$(echo "scale=10; $RANDOM/32767" | bc -l)
	d1=$(echo "scale=10; $x * $x" | bc -l)
	d2=$(echo "scale=10; $y * $y" | bc -l)
	d=$(echo "scale=10; $d1 + $d2" | bc -l)
	### If inside cicle, increase N_i
	if [[ $(echo "scale = 10; $d <= 1.0 " | bc -l) = 1 ]]; then
	 	N_i=$(( $N_i+1 ))
	fi
	piestimate=$(echo "scale=10; 4*$N_i/${N[n]}" | bc -l)
	erel=$(echo "scale=10; sqrt((($PI-$piestimate)/$PI)^2)" | bc -l)
done

### Printing in the required format, the time appending is done by job.sh
echo -n "$N $N_i $(($N-$N_i)) $piestimate $erel "
