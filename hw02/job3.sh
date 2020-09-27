#!/bin/bash
#SBATCH -N 1
#SBATCH -n 48
#SBATCH -o job.log
#SBATCH -e error.%j.out
#SBATCH -J PI_ESTIMATION_CPP
#SBATCH -p skx-normal
#SBATCH -A cse38018
#SBATCH -t 00:40:00

#SBATCH --mail-user=shreyasg911@gmail.com
#SBATCH --mail-type=begin

TIMEFORMAT=%R ## Change time format to give only real time value, got this from stack overflow
n_core=48
N_chunk=960000000
N_core=$(($N_chunk/$n_core))
erel=1
iter=0
while [ $erel -gt 1 ]; do
	a=1
	iter=iter+1
done