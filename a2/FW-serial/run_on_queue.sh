#!/bin/bash

## Give the Job a descriptive name
#PBS -N run_fw

## Output and error files
#PBS -o run_fw.out
#PBS -e run_fw.err

## How many machines should we get? 
#PBS -l nodes=1:ppn=1

##How long should the job run for?
#PBS -l walltime=00:30:00

## Start 
## Run make in the src folder (modify properly)

module load openmp
cd /home/parallel/parlab21/a2/FW-serial

for i in 1
do 
	export OMP_NUM_THREADS=$i
	./fw 1024 >> fw1024.out
	## ./fw 2048 >> fw2048.out
	## ./fw 4096 >> fw4096.out
done 
