#!/bin/bash

threads=12

i=1
while [[ i -le threads ]]
do
  j=1
  printf "%i " "$i"
  while [[ j -le 10 ]]
  do
    TIMEFORMAT='%R'
    ./steinberg "$1" 0 1 1 1 $i
    ((j = j + 1))
  done
  printf "\n"
  ((i = i + 1))
done