#!/bin/bash
#SBATCH -N 1
#SBATCH -n 1
##SBATCH -o job_cpp_results.log
##SBATCH -e error.%j.out
#SBATCH -J INTEGRATION
#SBATCH -p skx-normal
#SBATCH -A cse38018
#SBATCH -t 00:01:00

TIMEFORMAT=%R ## Change time format to give only real time value, got this from stack overflow

## Create empty log files
>results_trapezoidal.log
>results_simpson.log

## Create headings in log files
echo "#N integral_computed e_rel time" >> results_trapezoidal.log
echo "#N integral_computed e_rel time" >> results_simpson.log

## Output stores stdout of integrate and stderr of time

make integrate

{ time ./integrate 1 10  >> results_trapezoidal.log;} 2>> results_trapezoidal.log
{ time ./integrate 1 50  >> results_trapezoidal.log;} 2>> results_trapezoidal.log
{ time ./integrate 1 100  >> results_trapezoidal.log;} 2>> results_trapezoidal.log
{ time ./integrate 1 500  >> results_trapezoidal.log;} 2>> results_trapezoidal.log
{ time ./integrate 1 1000  >> results_trapezoidal.log;} 2>> results_trapezoidal.log
{ time ./integrate 1 5000  >> results_trapezoidal.log;} 2>> results_trapezoidal.log
{ time ./integrate 1 10000  >> results_trapezoidal.log;} 2>> results_trapezoidal.log
{ time ./integrate 1 50000  >> results_trapezoidal.log;} 2>> results_trapezoidal.log
{ time ./integrate 1 100000  >> results_trapezoidal.log;} 2>> results_trapezoidal.log
{ time ./integrate 1 1000000  >> results_trapezoidal.log;} 2>> results_trapezoidal.log

{ time ./integrate 2 10  >> results_simpson.log;} 2>> results_simpson.log
{ time ./integrate 2 50  >> results_simpson.log;} 2>> results_simpson.log
{ time ./integrate 2 100  >> results_simpson.log;} 2>> results_simpson.log
{ time ./integrate 2 500  >> results_simpson.log;} 2>> results_simpson.log
{ time ./integrate 2 1000  >> results_simpson.log;} 2>> results_simpson.log
{ time ./integrate 2 5000  >> results_simpson.log;} 2>> results_simpson.log
{ time ./integrate 2 10000  >> results_simpson.log;} 2>> results_simpson.log
{ time ./integrate 2 50000  >> results_simpson.log;} 2>> results_simpson.log
{ time ./integrate 2 100000  >> results_simpson.log;} 2>> results_simpson.log
{ time ./integrate 2 1000000  >> results_simpson.log;} 2>> results_simpson.log

## Plot results using a script
gnuplot plot.script

## Clean the make build
make clean
