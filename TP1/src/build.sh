#!/usr/bin/env bash

gcc -Wall -Wextra -Wpedantic -Werror main.c net.c ground_station.c -o ground_station
