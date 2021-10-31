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

mkdir -p ${HOME}/tmp
export TMPDIR=${HOME}/tmp

module load openmp
cd /home/parallel/parlab21/a1
make

rm -r ${HOME}/tmp


