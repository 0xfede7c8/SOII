#!/usr/bin/env bash

gcc -Wall -Wextra -Wpedantic -Werror main.c ground_station.c net.c translate_error.c -o ground_station
