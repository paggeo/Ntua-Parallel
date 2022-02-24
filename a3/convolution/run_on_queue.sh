#!/bin/bash

## Give the Job a descriptive name
#PBS -N run_thermal

## Output and error files
#PBS -o test.out
#PBS -e test.err

## How many machines should we get? 
#PBS -l nodes=8:ppn=8

##How long should the job run for?
#PBS -l walltime=01:00:00

## Start 
## Run make in the src folder (modify properly)

module load openmpi/1.8.3
cd /home/parallel/parlab21/a3/convolution

rm jacobi_conv.txt
rm seidelsor_conv.txt
rm redblacksor_conv.txt

for i in 1024 
do
	for j in jacobi seidelsor redblacksor
	do
		mpirun -np 64 --map-by node --mca btl self,tcp $j $i $i 8 8 >> ${j}_conv.txt 
	done
done

