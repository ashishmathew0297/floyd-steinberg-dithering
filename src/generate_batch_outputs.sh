#!/bin/sh

GREEN=$(tput setaf 2)
NORMAL=$(tput sgr0)
YELLOW=$(tput setaf 3)
BOLD=$(tput bold)

factor=$1

g++ -Wall -std=c++11 -fopenmp -o steinberg main.cpp $(pkg-config --cflags --libs opencv4)

printf "%s%sPlease Wait:%s Generating processed images for all images in ../input ...\n" "${BOLD}" "${YELLOW}" "${NORMAL}"

for filename in ../input/*.*; do
  echo "Processing $(basename "${filename}")"
  ./steinberg "$(basename "${filename}")" 0 "$factor" 0 1 > /dev/null
  ./steinberg "$(basename "${filename}")" 1 "$factor" 0 1 > /dev/null
  ./steinberg "$(basename "${filename}")" 1 "$factor" 1 12 > /dev/null
done

printf "%s%sExecution finished:%s Please check the output folder for the results\n\n" "${BOLD}" "${GREEN}" "${NORMAL}"

rm steinberg
