#!/bin/bash

GREEN=$(tput setaf 2)
NORMAL=$(tput sgr0)
YELLOW=$(tput setaf 3)
BOLD=$(tput bold)

g++ -Wall -std=c++11 -o steinberg main.cpp $(pkg-config --cflags --libs opencv4)

printf "%s%sPlease Wait:%s Generating image ...\n" "${BOLD}" "${YELLOW}" "${NORMAL}"
time ./steinberg
printf "%s%sSuccess:%s Image successfully generated!\n\n" "${BOLD}" "${GREEN}" "${NORMAL}"

rm steinberg