#!/bin/bash
for ((i = 1; ; i++))
do
    echo $i
    ./gen $i > test.in
    ./a < test.in > a.out
    ./b < test.in > b.out
    diff -w a.out b.out || break
done