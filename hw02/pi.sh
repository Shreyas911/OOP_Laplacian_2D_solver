# !/bin/bash
N=(5000)
PI=$(echo "scale =10; 3.14159265358979323846" | bc -l)

declare -a erel=( $(for i in {1..${#N[@]}}; do echo 0; done) )
declare -a piestimate=( $(for i in {1..${#N[@]}}; do echo 0; done) )

for n in `seq 0 $((${#N[@]}-1))`; do
	COUNTER=0
	for i in `seq ${N[n]}`;do
		x=$(echo "scale=10; $RANDOM/32767" | bc -l)
		y=$(echo "scale=10; $RANDOM/32767" | bc -l)
		d1=$(echo "scale=10; $x * $x" | bc -l)
		d2=$(echo "scale=10; $y * $y" | bc -l)
		d=$(echo "scale=10; $d1 + $d2" | bc -l)
		if [[ $(echo "scale = 10; $d <= 1.0 " | bc -l) = 1 ]]; then
		 	COUNTER=$(( $COUNTER+1 ))
		fi
	done

	piestimate[n]=$(echo "scale=10; 4*$COUNTER/${N[n]}" | bc -l)
	erel[n]=$(echo "scale=10; sqrt((($PI-${piestimate[n]})/$PI)^2)" | bc -l)
done
echo
echo ${piestimate[@]}
echo ${erel[@]}