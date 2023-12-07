#!/bin/bash

GREEN=$(tput setaf 2)
NORMAL=$(tput sgr0)
YELLOW=$(tput setaf 3)
BOLD=$(tput bold)

g++ -Wall -std=c++11 -fopenmp -o steinberg main.cpp $(pkg-config --cflags --libs opencv4)

printf "%s%sPlease Wait:%s Generating images from ../input ...\n" "${BOLD}" "${YELLOW}" "${NORMAL}"

# time ./steinberg "elden_ring.jpg" 0
# time ./steinberg "elden_ring.jpg" 1

for filename in ../input/*.*; do
  printf "Generating quantized and dithered results and time readings for %s\n" "$(basename "${filename}")";
  # Removing files if they already exist
  rm -f ../time_measurements/"quantizing_$(basename "${filename%.*}").dat"
  rm -f ../time_measurements/"dithering_$(basename "${filename%.*}").dat"

  ./generate_serial_readings_by_factor.sh "$(basename "${filename}")" "$(basename "${filename%.*}")"
done

printf "%s%sExecution finished:%s Please check the output and time_readings folders for the results\n\n" "${BOLD}" "${GREEN}" "${NORMAL}"

# Uncomment this code for memory checks
# valgrind --tool=memcheck ./steinberg "elden_ring.jpg" 1 2> "../debug_logs/large_image_valgrind.log"

rm steinberg