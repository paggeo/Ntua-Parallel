#!/bin/bash

## Give the Job a descriptive name
#PBS -N gif_game_of_life

## Output and error files
#PBS -o gif_game_of_life.out
#PBS -e gif_game_of_life.err

## How many machines should we get? 
#PBS -l nodes=1:ppn=8

##How long should the job run for?
#PBS -l walltime=00:10:00

## Start 
## Run make in the src folder (modify properly)

module load openmp
cd /home/parallel/parlab21/a1/

export OMP_NUM_THREADS=4
./Game_Of_Life_Gif 64 1000
