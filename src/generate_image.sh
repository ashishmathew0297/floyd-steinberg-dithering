#!/bin/sh

GREEN=$(tput setaf 2)
NORMAL=$(tput sgr0)
YELLOW=$(tput setaf 3)
BOLD=$(tput bold)

input=$1
greyscale=$2
dithered=$3
factor=$4
parallel=$5
threads=$6 

g++ -Wall -std=c++11 -fopenmp -o steinberg main.cpp $(pkg-config --cflags --libs opencv4)

printf "%s%sPlease Wait:%s Generating processed image from ../input ...\n" "${BOLD}" "${YELLOW}" "${NORMAL}"
./steinberg "$input" "$greyscale" "$dithered" "$factor" "$parallel" "$threads" > /dev/null
printf "%s%sExecution finished:%s Please check the output folder for the result\n\n" "${BOLD}" "${GREEN}" "${NORMAL}"

rm steinberg