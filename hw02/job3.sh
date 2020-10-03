#!/bin/bash
#SBATCH -N 1
#SBATCH -n 48
##SBATCH -o job.log
##SBATCH -e error.%j.out
#SBATCH -J PI_PARALLEL
#SBATCH -p skx-normal
#SBATCH -A cse38018
#SBATCH -t 00:10:00

#Buit in bash variable that automatically updates after initialization
SECONDS=0
# Actual value of PI
PI=$(echo "scale =10; 3.14159265358979323846" | bc -l)

#setup launcher environment
module purge
module load TACC
module load launcher 
export LAUNCHER_SCHED=interleaved
export LAUNCHER_PLUGIN_DIR=$LAUNCHER_DIR/plugins
export LAUNCHER_RMI=SLURM
#define the file with the commands to run in parallel
export LAUNCHER_JOB_FILE=./jobfile

# Delete temp*.log files if they exist and then create a new one
for((i = 1; i<=48;i++)); do
if [ -e "temp${i}.log" ]; then
  rm "temp${i}.log"
fi
touch "temp${i}.log"
done

TIMEFORMAT=%R ## Change time format to give only real time value, got this from stack overflow

# Epsilon is the desired accuracy
epsilon=$(echo "scale=10; 0.000005" | bc -l)
erel=1
iter=0 #Count number of iterations
pi_average=0 #Average value over all iterations
num_i=0 #Total number of points inside circle across all iterations
pi_iter_value=0 #pi value for this iteration

echo "# iter num_samples num_i pi relative_error time_accum">>iter.log

## empty iter.log file
>iter.log

while [ 1 ];do

	if [[ $(echo "scale=10; $erel < $epsilon" | bc -l) = 1 ]]; then
		break
	fi
	#empty the temp.log files before running the launcher again
	for((i = 1; i<=48;i++)); do
		>temp${i}.log
	done
	#run the launcher
	$LAUNCHER_DIR/paramrun
	# update iteration number and find new value of pi_average and relative error
    	#Each core outputs to a different file to prevent race conditions.
	# awk will read from all temp* files at once, which is cool.
	iter=$(($iter+1))
	pi_iter_value=$(awk 'BEGIN{z=0;}{z = z + $4;}END{z = z/48.0;print z;}' temp*.log| bc -l)
    	num_i=$(($num_i+$(awk 'BEGIN{z=0;}{z = z + $2;}END{print z;}' temp*.log| bc -l)))
    	pi_average=$(echo "scale=10; ($pi_average*($iter-1)+$pi_iter_value)/$iter" | bc -l)
    	pi_average_2=$(echo "scale=10; 4*$num_i/$(($iter*960000000))" | bc -l)
	erel=$(echo "scale=20; sqrt((($pi_average_2-$PI)/$PI)^2)" | bc -l)
	# Print output in desired format
	echo "$iter $(($iter*960000000)) $num_i $pi_average_2 $erel $SECONDS">>iter.log
done

# Remove the temporary log file
rm temp*
