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

### Output stores stdout of ./pi.sh and stderr of time

g++ pi.cpp -o ./b.out 
echo 10 > input
{ { time ./b.out >> pi.compiled.log;} < input ;} 2>> pi.compiled.log 
echo 100 > input
{ { time ./b.out >> pi.compiled.log;} < input ;} 2>> pi.compiled.log 
echo 500 > input
{ { time ./b.out >> pi.compiled.log;} < input ;} 2>> pi.compiled.log 
echo 1000 > input
{ { time ./b.out >> pi.compiled.log;} < input ;} 2>> pi.compiled.log 
echo 5000 > input
{ { time ./b.out >> pi.compiled.log;} < input ;} 2>> pi.compiled.log 
echo 10000 > input
{ { time ./b.out >> pi.compiled.log;} < input ;} 2>> pi.compiled.log
echo 50000 > input
{ { time ./b.out >> pi.compiled.log;} < input ;} 2>> pi.compiled.log  