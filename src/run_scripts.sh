#!/bin/bash

GREEN=$(tput setaf 2)
NORMAL=$(tput sgr0)
YELLOW=$(tput setaf 3)
BOLD=$(tput bold)

g++ -Wall -std=c++11 -fopenmp -o steinberg main.cpp $(pkg-config --cflags --libs opencv4)

# Generating time readings to see if factor for calculation affects the time of execution
# This also serves the purpose of seeing the time variation for code execution
printf "%s%sPlease Wait:%s Generating processed outputs and time vs dithering factor readings for a 7680x4320 resolution image and a 512x512 resolution image ...\n" "${BOLD}" "${YELLOW}" "${NORMAL}"
./generate_serial_readings_by_factor.sh "RGB_color_gradient_7680x4320.png" > "../time_measurements/serial_dithering_time_by_factor_large.dat"
./generate_serial_readings_by_factor.sh "lenna.tif" > "../time_measurements/serial_dithering_time_by_factor_small.dat"
printf "%s%sExecution finished:%s Please check the output and time_readings folders for the results\n\n" "${BOLD}" "${GREEN}" "${NORMAL}"

# Generating time readings for parallelized dithering for a small and a large image
printf "%s%sPlease Wait:%s Generating time readings for parallelized dithering algorithm on a 512x512 and a 7680x4320 resolution image ...\n" "${BOLD}" "${YELLOW}" "${NORMAL}"
./generate_parallel_readings.sh "RGB_color_gradient_7680x4320.png" > "../time_measurements/parallel_dithering_time_large.dat"
./generate_parallel_readings.sh "lenna.tif" > "../time_measurements/parallel_dithering_time_small.dat"
printf "%s%sExecution Finished:%s Please check the output folder for the results\n\n" "${BOLD}" "${GREEN}" "${NORMAL}"

rm steinberg

#=================================================================================================

# The following code can be used to generate images for your use.
# Make sure you commet out the previous code blocks before running these

#=================================================================================================

# Uncomment the lines below if you want all the images in the input folder quantized and dithered

# greyscale=0
# factor=1
# ./generate_batch_outputs.sh "$greyscale" "$factor"

#-------------------------------------------------------------------------------------------------

# Uncomment the lines below if you want to quantize or dither a particular image from the input folder 
# Change the inputs as per your need I have already filled them in as a reference

# input="me.jpg"
# greyscale=0
# dithered=1
# factor=1
# parallel=1
# threads=12
# ./generate_image.sh "$input" "$greyscale" "$dithered" "$factor" "$parallel" "$threads"

#-------------------------------------------------------------------------------------------------

# Diagnostics
# Uncomment this code for memory checks
# valgrind --tool=memcheck ./steinberg "image.jpg" 1 2> "../debug_logs/large_image_valgrind.log"
