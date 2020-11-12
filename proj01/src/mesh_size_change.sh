#!/bin/bash

>temp.tmp
>output.tmp

awk '{if($1 ~ /grid_points/){$3 = 10;} print $0;}' input.dat > input.tmp && mv input.tmp input.dat
./heat_solve >> temp.tmp
awk '{if($1 ~ /grid_points/){$3 = 20;} print $0;}' input.dat > input.tmp && mv input.tmp input.dat
./heat_solve >> temp.tmp
awk '{if($1 ~ /grid_points/){$3 = 30;} print $0;}' input.dat > input.tmp && mv input.tmp input.dat
./heat_solve >> temp.tmp
awk '{if($1 ~ /grid_points/){$3 = 50;} print $0;}' input.dat > input.tmp && mv input.tmp input.dat
./heat_solve >> temp.tmp

echo "n       L2_error          Time taken" >> output.tmp
awk '{if($1 == "L2"){printf("%s %s ", $7, $9);}if($1 == "Total"){print $5;}}' temp.tmp >> output.tmp
#grep "Total Measured Time" temp.tmp | awk '{print $5}' >> output.tmp

