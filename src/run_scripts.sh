#!/bin/bash

GREEN=$(tput setaf 2)
NORMAL=$(tput sgr0)
YELLOW=$(tput setaf 3)
BOLD=$(tput bold)

g++ -Wall -std=c++11 -fopenmp -o steinberg main.cpp $(pkg-config --cflags --libs opencv4)

# Generating time readings to see if factor for calculation affects the time of execution
printf "%s%sPlease Wait:%s Generating processed outputs and time vs dithering factor readings for a 7680x4320 resolution image and a 512x512 resolution image ...\n" "${BOLD}" "${YELLOW}" "${NORMAL}"
./generate_serial_readings_by_factor.sh "RGB_color_gradient_15360x8640.jpg" > "../time_measurements/serial_dithering_time_by_factor_large.dat"
./generate_serial_readings_by_factor.sh "lenna.tif" > "../time_measurements/serial_dithering_time_by_factor_small.dat"
printf "%s%sExecution finished:%s Please check the output and time_readings folders for the results\n\n" "${BOLD}" "${GREEN}" "${NORMAL}"

printf "%s%sPlease Wait:%s Generating time readings for parallelized dithering algorithm on a 512x512 and a 7680x4320 resolution image ...\n" "${BOLD}" "${YELLOW}" "${NORMAL}"
./generate_parallel_readings.sh "malenia_7680x4320.jpg" > "../time_measurements/parallel_dithering_time.dat"
./generate_parallel_readings.sh "lenna.tif" > "../time_measurements/parallel_dithering_time.dat"
printf "%s%sExecution Finished:%s Please check the output folder for the results\n\n" "${BOLD}" "${GREEN}" "${NORMAL}"


# Uncomment the code below if you want all the images in the input folder quantized and dithered to a factor of 1

printf "%s%sPlease Wait:%s Generating processed images for all images in ../input ...\n" "${BOLD}" "${YELLOW}" "${NORMAL}"
factor=1
for filename in ../input/*.*; do
  echo "Processing $(basename "${filename}")"
  ./steinberg "$(basename "${filename}")" 0 $factor 0 1 > /dev/null
  ./steinberg "$(basename "${filename}")" 1 $factor 0 1 > /dev/null
  ./steinberg "$(basename "${filename}")" 1 $factor 1 12 > /dev/null
done
printf "%s%sExecution finished:%s Please check the output folder for the results\n\n" "${BOLD}" "${GREEN}" "${NORMAL}"

# Uncomment this code for memory checks
# valgrind --tool=memcheck ./steinberg "elden_ring.jpg" 1 2> "../debug_logs/large_image_valgrind.log"

rm steinberg