#!/bin/bash
#SBATCH -N 1
#SBATCH -n 48
#SBATCH -o pi.script.log
#SBATCH -e error.%j.out
#SBATCH -J PI_ESTIMATION
#SBATCH -p skx-normal
#SBATCH -A cse38018
#SBATCH -t 00:20:00

#SBATCH --mail-user=shreyasg911@gmail.com
#SBATCH --mail-type=begin

TIMEFORMAT=%R ## Change time format to give only real time value
ibrun time ./pi.sh 10
ibrun time ./pi.sh 100
ibrun time ./pi.sh 500
ibrun time ./pi.sh 1000
ibrun time ./pi.sh 5000
ibrun time ./pi.sh 10000
ibrun time ./pi.sh 50000