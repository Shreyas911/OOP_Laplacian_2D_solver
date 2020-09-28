#!/bin/bash
#SBATCH -N 1
#SBATCH -n 48
#SBATCH -o job.log
#SBATCH -e error.%j.out
#SBATCH -J PI_PARALLEL
#SBATCH -p skx-normal
#SBATCH -A cse38018
#SBATCH -t 00:10:00

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

if [ -e temp.log ]; then
  rm temp.log
fi
touch temp.log

TIMEFORMAT=%R ## Change time format to give only real time value, got this from stack overflow

epsilon=$(echo "scale=10; 0.000005" | bc -l)
erel=1
iter=0
pi_average=0
num_i=0
pi_iter_value=0

echo "# iter num_samples num_i pi relative_error time_accum">>iter.log

while [ 1 ];do

	if [[ $(echo "scale=10; $erel < $epsilon" | bc -l) = 1 ]]; then
		break
	fi
	#empty the temp.log file
	> temp.log
	#run the launcher
	$LAUNCHER_DIR/paramrun

    iter=$(($iter+1))
    pi_iter_value=$(awk 'BEGIN{z=0;}{z = z + $4;}END{z = z/48.0;print z;}' iter.log| bc -l)
    num_i=$(($num_i+$(awk 'BEGIN{z=0;}{z = z + $2;}END{print z;}' iter.log| bc -l)))
    pi_average=$(echo "scale=10; ($pi_average*($iter-1)+$pi_iter_value)/$iter" | bc -l)
    pi_average_2=$(echo "scale=10; $num_i/$(($iter*960000000))" | bc -l)
    erel=$(echo "scale=20; sqrt((($pi_average-$PI)/$PI)^2)" | bc -l)
	echo "$iter $(($iter*960000000)) $num_i $pi_average $pi_average_2 $erel">>iter.log
done

rm temp.log
