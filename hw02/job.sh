#!/bin/bash
#SBATCH -N 1
#SBATCH -n 1
#SBATCH -o job.log
#SBATCH -e error.%j.out
#SBATCH -J PI_ESTIMATION
#SBATCH -p skx-normal
#SBATCH -A cse38018
#SBATCH -t 00:20:00

#SBATCH --mail-user=shreyasg911@gmail.com
#SBATCH --mail-type=begin

TIMEFORMAT=%R ## Change time format to give only real time value
time ibrun ./pi.sh 10 >> pi.script.log
time ibrun ./pi.sh 100 >> pi.script.log
time ibrun ./pi.sh 500 >> pi.script.log
time ibrun ./pi.sh 1000 >> pi.script.log
time ibrun ./pi.sh 5000 >> pi.script.log
time ibrun ./pi.sh 10000 >> pi.script.log
time ibrun ./pi.sh 50000 >> pi.script.log