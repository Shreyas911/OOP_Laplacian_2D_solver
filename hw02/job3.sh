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

if [ -e iter.log ]; then
  rm iter.log
fi
touch iter.log

TIMEFORMAT=%R ## Change time format to give only real time value, got this from stack overflow

epsilon=$(echo "scale=10; 0.000005" | bc -l)
erel=1
iter=0
pi_average=0
N_i_average=0
pi_iter_value=0

while [[ $(echo "scale=10; $erel > $epsilon" | bc -l) ]];do
	#empty the iter.log file
	> iter.log
	#run the launcher
	$LAUNCHER_DIR/paramrun

        iter=$(($iter+1))
        pi_iter_value=$(awk 'BEGIN{temp=0;}{temp = temp + $4;}END{temp = temp/48.0;print temp;}' iter.log| bc -l)
        pi_average=$(echo "scale=10; ($pi_average*($iter-1)+$pi_iter_value)/$iter" | bc -l)
        erel=$(echo "scale=20; sqrt((($pi_average-$PI)/$PI)^2)" | bc -l)
	echo "$iter $pi_iter_value $pi_average $erel">>temp1
	$(echo "scale=10; $erel > $epsilon" | bc -l)>>temp1
done

