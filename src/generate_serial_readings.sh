#!/bin/bash

i=1

while [[ i -le 30 ]]
do
  printf "%i " "$i"
  ./steinberg "$1" 1 1 0 1
  ((i = i + 1))
  printf "\n"
done
