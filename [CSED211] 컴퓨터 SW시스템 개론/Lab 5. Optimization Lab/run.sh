#!/bin/bash
timea=`date +%s%5N`
gcc -O0 -o loops -g loops.c
timeb=`date +%s%5N`
gcc -O1 -o loopsO1 -g loops.c
timec=`date +%s%5N`
gcc -O2 -o loopsO2 -g loops.c
timed=`date +%s%5N`
gcc -O3 -o loopsO3 -g loops.c
timee=`date +%s%5N`
gcc -Os -o loopsOs -g loops.c
timef=`date +%s%5N`
gcc -Ofast -o loopsOfast -g loops.c
timeg=`date +%s%5N`
echo "-O0"
echo "Compile time: "$((timeb - timea))
./loops | grep "spent"
echo "-O1"
echo "Compile time: "$((timec - timeb))
./loopsO1 | grep "spent"
echo "-O2"
echo "Compile time: "$((timed - timec))
./loopsO2 | grep "spent"
echo "-O3"
echo "Compile time: "$((timee - timed))
./loopsO3 | grep "spent"
echo "-Os"
echo "Compile time: "$((timef - timee))
./loopsOs | grep "spent"
echo "-Ofast"
echo "Compile time: "$((timeg - timef))
./loopsOfast | grep "spent"

rm -f loops loopsO1 loopsO2 loopsO3 loopsOs loopsOfast
