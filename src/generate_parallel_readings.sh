#!/bin/bash

i=1

factor=8

rm -f "../time_measurements/parallel_time_readings.dat"
while [[ i -le 10 ]]
do
  j=1
  while [[ j -le factor ]]
  do
    TIMEFORMAT='%R'
    { printf "%i " "$((2**j - 1))" && time ./steinberg "elden_ring_logo_1080.jpg" 1 $((2**j - 1)) 0; } &>> ../time_measurements/dithering_time_by_factor_large.dat
    ((j = j + 1))
  done
  ((i = i + 1))
done