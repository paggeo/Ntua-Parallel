#!/bin/bash
files=("mp_1_64.out" "mp_1_1024.out" "mp_1_4096.out" "mp_2_64.out" "mp_2_1024.out" "mp_2_4096.out" "mp_4_64.out" "mp_4_1024.out" "mp_4_4096.out" "mp_6_64.out" "mp_6_1024.out" "mp_6_4096.out" "mp_8_64.out" "mp_8_1024.out" "mp_8_4096.out")


cd /home/parallel/parlab21/a1/

COUNTER=0
for i in 1 2 4 6 8
do 
	export OMP_NUM_THREADS=$i
	for j in 64 1024 4096
	do 
		./test $j 1000 > ${files[$COUNTER]}
		let COUNTER++
	done
done 
