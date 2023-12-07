#!/bin/bash

i=0
factor=8

while [[ i -le factor ]]
do
  
  TIMEFORMAT='%R'
  { time ./steinberg "$1" 0 $((2**i)); } &>> ../time_measurements/"quantizing_$2.dat"
  { time ./steinberg "$1" 1 $((2**i)); } &>> ../time_measurements/"dithering_$2.dat"
  printf "\n"
  ((i = i + 1))
done