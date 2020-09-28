#!/bin/bash
#SBATCH -N 1
#SBATCH -n 1
##SBATCH -o job_results.log
##SBATCH -e error.%j.out
#SBATCH -J PI_ESTIMATION
#SBATCH -p skx-normal
#SBATCH -A cse38018
#SBATCH -t 00:40:00

TIMEFORMAT=%R ## Change time format to give only real time value

### Output stores stdout of ./pi.sh and stderr of time since the time command gives it's output to stderr.
{ time ./pi.sh 10 >> pi.script.log ;} 2>> pi.script.log
{ time ./pi.sh 100 >> pi.script.log ;} 2>> pi.script.log
{ time ./pi.sh 500 >> pi.script.log ;} 2>> pi.script.log
{ time ./pi.sh 1000 >> pi.script.log ;} 2>> pi.script.log
{ time ./pi.sh 5000 >> pi.script.log ;} 2>> pi.script.log
{ time ./pi.sh 10000 >> pi.script.log ;} 2>> pi.script.log
{ time ./pi.sh 50000 >> pi.script.log ;} 2>> pi.script.log