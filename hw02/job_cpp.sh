#!/bin/bash
#SBATCH -N 1
#SBATCH -n 1
##SBATCH -o job_cpp_results.log
##SBATCH -e error.%j.out
#SBATCH -J PI_ESTIMATION_CPP
#SBATCH -p skx-normal
#SBATCH -A cse38018
#SBATCH -t 00:05:00

TIMEFORMAT=%R ## Change time format to give only real time value, got this from stack overflow

## Create empty pi.compiled.log file
>pi.compiled.log


### Output stores stdout of ./pi.sh and stderr of time

g++ pi.cpp -o ./b.out 
{ time ./b.out 10  >> pi.compiled.log;} 2>> pi.compiled.log
{ time ./b.out 100  >> pi.compiled.log;} 2>> pi.compiled.log
{ time ./b.out 500  >> pi.compiled.log;} 2>> pi.compiled.log
{ time ./b.out 1000  >> pi.compiled.log;} 2>> pi.compiled.log
{ time ./b.out 5000  >> pi.compiled.log;} 2>> pi.compiled.log
{ time ./b.out 10000  >> pi.compiled.log;} 2>> pi.compiled.log
{ time ./b.out 50000  >> pi.compiled.log;} 2>> pi.compiled.log
