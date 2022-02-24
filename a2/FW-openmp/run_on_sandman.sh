#!/bin/bash

## Give the Job a descriptive name
#PBS -N run_fw

## Output and error files
#PBS -o omp_small_sizes.out
#PBS -e omp_small_sizes.err

## How many machines should we get? 
#PBS -l nodes=1:ppn=8

##How long should the job run for?
#PBS -l walltime=01:00:00

## Start 
## Run make in the src folder (modify properly)

module load openmp
cd /home/parallel/parlab21/a2/FW-openmp

for i in 1 2 4 8 16 32 64
do 
	for j in 1024 2048
	do
		export OMP_NUM_THREADS=$i
		echo "Number of threads: $i"
		./fw $j
		./fw_sr $j 32
		./fw_sr $j 64
		./fw_sr $j 128
		./fw_tiled $j 32
		./fw_tiled $j 64
		./fw_tiled $j 128
	done
done 
