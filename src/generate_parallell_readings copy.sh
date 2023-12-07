#!/bin/bash

# i=1
num_iter=5
# num_threads=12

TIMEFORMAT='%R'
{ time ./steinberg "$1" 0 1; } 2>> ../time_measurements/"quantizing_$2.dat"
{ time ./steinberg "$1" 1 1; }  2>> ../time_measurements/"dithering_$2.dat"

while [[ i -le num_iter ]]
do
#   j=1
#   while [[ j -le num_threads ]]
#   do
#     ./steinberg "$1"
#     ((j = j + 1))
#   done
#   printf "\n"
#   ((i = i + 1))
done