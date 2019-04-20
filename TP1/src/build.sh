#!/usr/bin/env bash

gcc -Wall -Wextra -Wpedantic -Werror main_ground_station.c ground_station.c net.c translate_error.c validation.c -o ground_station
gcc -Wall -Wextra -Wpedantic -Werror main_satellite.c satellite.c net.c translate_error.c validation.c -o satellite
