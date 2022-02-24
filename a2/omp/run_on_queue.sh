#!/bin/bash

## Give the Job a descriptive name
#PBS -N run_fw

## Output and error files
#PBS -o run_fw.out
#PBS -e run_fw.err

## How many machines should we get? 
#PBS -l nodes=1:ppn=8

##How long should the job run for?
#PBS -l walltime=00:20:00

## Start 
## Run make in the src folder (modify properly)

module load openmp
cd /home/parallel/parlab21/a2/omp

for i in 1 8
do 
	export OMP_NUM_THREADS=$i
	for j in 4096 
	do
		##./fw 4096 
		./fw_sr 4096 64 
		##./fw_tiled 4096 64 
	done
done 
