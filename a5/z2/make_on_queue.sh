#!/bin/bash

## Give the Job a descriptive name
#PBS -N main

## Output and error files
#PBS -o main.out
#PBS -e main.err

#PBS -l nodes=sandman:ppn=64

##How long should the job run for?
#PBS -l walltime=00:01:00

## Start
## Run make in the src folder (modify properly)

cd /home/parallel/parlab21/a5/z2
make clean
make
