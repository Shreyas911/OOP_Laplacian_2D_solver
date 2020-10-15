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

{ time ./integrate 1 6  >> results_trapezoidal.log;} 2>> results_trapezoidal.log
{ time ./integrate 1 10  >> results_trapezoidal.log;} 2>> results_trapezoidal.log
{ time ./integrate 1 50  >> results_trapezoidal.log;} 2>> results_trapezoidal.log
{ time ./integrate 1 100  >> results_trapezoidal.log;} 2>> results_trapezoidal.log
{ time ./integrate 1 200  >> results_trapezoidal.log;} 2>> results_trapezoidal.log
{ time ./integrate 1 500  >> results_trapezoidal.log;} 2>> results_trapezoidal.log
{ time ./integrate 1 1000  >> results_trapezoidal.log;} 2>> results_trapezoidal.log
{ time ./integrate 1 2000  >> results_trapezoidal.log;} 2>> results_trapezoidal.log
{ time ./integrate 1 5000  >> results_trapezoidal.log;} 2>> results_trapezoidal.log
{ time ./integrate 1 10000  >> results_trapezoidal.log;} 2>> results_trapezoidal.log

## Simpson needs even number of intervals, i.e. odd number of points
{ time ./integrate 2 5  >> results_simpson.log;} 2>> results_simpson.log
{ time ./integrate 2 11  >> results_simpson.log;} 2>> results_simpson.log
{ time ./integrate 2 31  >> results_simpson.log;} 2>> results_simpson.log
{ time ./integrate 2 51  >> results_simpson.log;} 2>> results_simpson.log
{ time ./integrate 2 71  >> results_simpson.log;} 2>> results_simpson.log
{ time ./integrate 2 91  >> results_simpson.log;} 2>> results_simpson.log
{ time ./integrate 2 111  >> results_simpson.log;} 2>> results_simpson.log
{ time ./integrate 2 131  >> results_simpson.log;} 2>> results_simpson.log
{ time ./integrate 2 161  >> results_simpson.log;} 2>> results_simpson.log
{ time ./integrate 2 191  >> results_simpson.log;} 2>> results_simpson.log

## Plot results using a script
gnuplot plot.script

## Clean the make build
make clean
