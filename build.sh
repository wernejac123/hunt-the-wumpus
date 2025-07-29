#!/bin/bash

gcc -g -Wall -Werror -Wextra -Wconversion *.c -o wumpus
strip -s wumpus
