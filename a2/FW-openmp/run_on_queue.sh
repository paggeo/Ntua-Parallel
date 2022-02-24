#!/bin/bash

## Give the Job a descriptive name
#PBS -N run_fw

## Output and error files
#PBS -o run_tiled.out
#PBS -e run_tiled.err

## How many machines should we get? 
#PBS -l nodes=1:ppn=8

##How long should the job run for?
#PBS -l walltime=00:30:00

## Start 
## Run make in the src folder (modify properly)

module load openmp
cd /home/parallel/parlab21/a2/FW-openmp

for i in 1 2 8  
do 
	export OMP_NUM_THREADS=$i
	echo "Number of threads: {$i}"	
	for j in 1024 2048 4096
	do
		./fw $j
		./fw_sr $j 64
		./fw_tiled $j 32
	done
done 
