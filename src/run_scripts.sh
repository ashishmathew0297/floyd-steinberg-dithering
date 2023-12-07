#!/bin/bash

GREEN=$(tput setaf 2)
NORMAL=$(tput sgr0)
YELLOW=$(tput setaf 3)
BOLD=$(tput bold)

g++ -Wall -std=c++11 -o steinberg main.cpp $(pkg-config --cflags --libs opencv4)

printf "%s%sPlease Wait:%s Generating images from ../input ...\n" "${BOLD}" "${YELLOW}" "${NORMAL}"

# time ./steinberg "elden_ring.jpg" 0
# time ./steinberg "elden_ring.jpg" 1

for filename in ../input/*.*; do
  printf "Generating quantized and dithered results and time readings for %s\n" "$(basename "${filename}")";
  # Removing files if they already exist
  rm ../time_measurements/"quantizing_$(basename "${filename%.*}").dat"
  rm ../time_measurements/"dithering_$(basename "${filename%.*}").dat"

  TIMEFORMAT='%R'
  { time ./steinberg "$(basename "${filename}")" 0 1; } 2>> ../time_measurements/"quantizing_$(basename "${filename%.*}").dat"
  { time ./steinberg "$(basename "${filename}")" 1 1; } 2>> ../time_measurements/"dithering_$(basename "${filename%.*}").dat"
done

printf "%s%sExecution finished:%s Please check the output and time_readings folders for the results\n\n" "${BOLD}" "${GREEN}" "${NORMAL}"

# Uncomment this code for memory checks
# valgrind --tool=memcheck ./steinberg "elden_ring.jpg" 1 2> "../debug_logs/large_image_valgrind.log"

rm steinberg