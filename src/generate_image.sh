#!/bin/sh

GREEN=$(tput setaf 2)
NORMAL=$(tput sgr0)
YELLOW=$(tput setaf 3)
BOLD=$(tput bold)

input=$1
dithered=$2
factor=$3
parallel=$4
threads=$5

g++ -Wall -std=c++11 -fopenmp -o steinberg main.cpp $(pkg-config --cflags --libs opencv4)

printf "%s%sPlease Wait:%s Generating processed image from ../input ...\n" "${BOLD}" "${YELLOW}" "${NORMAL}"
./steinberg "$input" "$dithered" "$factor" "$parallel" "$threads" > /dev/null
printf "%s%sExecution finished:%s Please check the output folder for the result\n\n" "${BOLD}" "${GREEN}" "${NORMAL}"

rm steinberg