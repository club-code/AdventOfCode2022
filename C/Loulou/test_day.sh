#! /bin/bash

echo "*** Compiling day$1 ***"
gcc -c -fPIC -o libday.o day$1/*.c

echo "*** Compiling tester ***"
gcc -o tester main.c -L. -l:libday.o

echo "*** Testing ***"
./tester $2 $3
