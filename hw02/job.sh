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

TIMEFORMAT=%R ## Change time format to give only real time value, got this from stack overflow

### Output stores stdout of ./pi.sh and stderr of time
{ time ibrun ./pi.sh 10 >> output ;} 2>> output
{ time ibrun ./pi.sh 100 >> output ;} 2>> output
{ time ibrun ./pi.sh 500 >> output ;} 2>> output
{ time ibrun ./pi.sh 1000 >> output ;} 2>> output
{ time ibrun ./pi.sh 5000 >> output ;} 2>> output
{ time ibrun ./pi.sh 10000 >> output ;} 2>> output
{ time ibrun ./pi.sh 50000 >> output ;} 2>> output