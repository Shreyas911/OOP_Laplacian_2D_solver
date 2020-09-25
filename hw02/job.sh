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

ibrun ./pi.sh