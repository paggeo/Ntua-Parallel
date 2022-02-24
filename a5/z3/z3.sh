#!/bin/bash

## Give the Job a descriptive name
#PBS -N run

## Output and error files
#PBS -o run.out
#PBS -e run.err

#PBS -l nodes=sandman:ppn=64

##How long should the job run for?
#PBS -l walltime=01:00:00

## Start
## Run make in the src folder (modify properly)

cd /home/parallel/parlab21/a5/z3

for i in ll_fgl.c ll_opt.c ll_lazy.c ll_nb.c
do 
make clean 
export LL_FILE=$i
rm -rf results_${i}.txt
make
for j in 1024 8192 
do
echo $j >> results_${i}.txt
echo "80 10 10" >> results_${i}.txt
MT_CONF=0 ./linked_list $j 80 10 10 >>results_${i}.txt
MT_CONF=0,1 ./linked_list $j 80 10 10 >>results_${i}.txt
MT_CONF=0,1,2,3 ./linked_list $j 80 10 10 >>results_${i}.txt
MT_CONF=0,1,2,3,4,5,6,7 ./linked_list $j 80 10 10 >>results_${i}.txt
MT_CONF=0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15 ./linked_list $j 80 10 10 >>results_${i}.txt
MT_CONF=0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19,20,21,22,23,24,25,26,27,28,29,30,31 ./linked_list $j 80 10 10 >>results_${i}.txt
MT_CONF=0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19,20,21,22,23,24,25,26,27,28,29,30,31,32,33,34,35,36,37,38,39,40,41,42,43,44,45,46,47,48,49,50,51,52,53,54,55,56,57,58,59,60,61,62,63 ./linked_list $j 80 10 10 >>results_${i}.txt

echo "20 40 40" >> results_${i}.txt
MT_CONF=0 ./linked_list $j 20 40 40 >>results_${i}.txt
MT_CONF=0,1 ./linked_list $j 20 40 40 >>results_${i}.txt
MT_CONF=0,1,2,3 ./linked_list $j 20 40 40 >>results_${i}.txt
MT_CONF=0,1,2,3,4,5,6,7 ./linked_list $j 20 40 40 >>results_${i}.txt
MT_CONF=0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15 ./linked_list $j 20 40 40 >>results_${i}.txt
MT_CONF=0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19,20,21,22,23,24,25,26,27,28,29,30,31 ./linked_list $j 20 40 40 >>results_${i}.txt
MT_CONF=0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19,20,21,22,23,24,25,26,27,28,29,30,31,32,33,34,35,36,37,38,39,40,41,42,43,44,45,46,47,48,49,50,51,52,53,54,55,56,57,58,59,60,61,62,63 ./linked_list $j 20 40 40 >>results_${i}.txt
done 
done
