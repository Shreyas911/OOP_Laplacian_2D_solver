#!/bin/bash
#SBATCH -N 1
#SBATCH -n 48
#SBATCH -o job.log
#SBATCH -e error.%j.out
#SBATCH -J PI_PARALLEL
#SBATCH -p skx-normal
#SBATCH -A cse38018
#SBATCH -t 00:05:00


#setup launcher environment
module purge
module load TACC
module load launcher 
export LAUNCHER_SCHED=interleaved
export LAUNCHER_PLUGIN_DIR=$LAUNCHER_DIR/plugins
export LAUNCHER_RMI=SLURM


TIMEFORMAT=%R ## Change time format to give only real time value, got this from stack overflow

#define the file with the commands to run in parallel
export LAUNCHER_JOB_FILE=./jobfile

#run the launcher
$LAUNCHER_DIR/paramrun