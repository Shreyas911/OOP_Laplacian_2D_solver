#!/bin/bash
#SBATCH -N 1
#SBATCH -n 1
#SBATCH -o job.log
#SBATCH -e error.%j.out
#SBATCH -J PI_ESTIMATION_CPP
#SBATCH -p skx-normal
#SBATCH -A cse38018
#SBATCH -t 00:40:00
#SBATCH --mail-user=shreyasg911@gmail.com
#SBATCH --mail-type=begin
export LAUNCHER_SCHED=interleaved
TIMEFORMAT=%R ## Change time format to give only real time value, got this from stack overflow

erel=1
### This will run on all 48 cores
{ time ./a.out >> iter.log;} 2>> iter.log

