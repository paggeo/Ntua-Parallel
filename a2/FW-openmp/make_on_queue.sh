#!/bin/bash

## Give the Job a descriptive name
#PBS -N makejob

## Output and error files
#PBS -o makejob.out
#PBS -e makejob.err

## How many machines should we get?
#PBS -l nodes=1:ppn=8

## Start 
## Run make in the src folder (modify properly)

module load openmp
cd /home/parallel/parlab21/a2/FW-openmp
make
