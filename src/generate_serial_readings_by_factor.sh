#!/bin/bash

i=1
factor=8

while [[ i -le factor ]]
do
  j=1
  printf "%i " "$((2**i - 1))"
  while [[ j -le 10 ]]
  do
    TIMEFORMAT='%R'
    ./steinberg "$1" 1 $((2**i - 1)) 0 1
    ((j = j + 1))
  done
  printf "\n"
  ((i = i + 1))
done