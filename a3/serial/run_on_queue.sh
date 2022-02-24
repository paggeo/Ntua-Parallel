#!/bin/bash

## Give the Job a descriptive name
#PBS -N run_thermal

## Output and error files
#PBS -o test.out
#PBS -e test.err

## How many machines should we get? 
#PBS -l nodes=1:ppn=1

##How long should the job run for?
#PBS -l walltime=01:00:00

## Start 
## Run make in the src folder (modify properly)

module load openmpi/1.8.3
cd /home/parallel/parlab21/a3/serial

./jacobi 1024 
./redblacksor 1024 
./seidelsor 1024
