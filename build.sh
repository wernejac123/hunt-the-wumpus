#!/bin/bash

FILES=src/*.c

gcc -g -Wall -Werror -Wextra -Wconversion $FILES -o wumpus
strip -s wumpus
