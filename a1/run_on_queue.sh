#!/bin/bash

## Give the Job a descriptive name
#PBS -N run_game_of_life

## Output and error files
#PBS -o run_game_of_life.out
#PBS -e run_game_of_life.err

## How many machines should we get? 
#PBS -l nodes=1:ppn=8

##How long should the job run for?
#PBS -l walltime=00:10:00

## Start 
## Run make in the src folder (modify properly)

module load openmp
cd /home/parallel/parlab21/a1/

for i in 1 2 4 6 8 
do 
	export OMP_NUM_THREADS=$i
<<<<<<< HEAD
	./Game_Of_Life 64 1000 >> test64.out
	./Game_Of_Life 1024 1000 >> test1024.out
	./Game_Of_Life 4096 1000 >> test4096.out
=======
	./Game_Of_Life 64 1000 >> game_of_life64.out
	./Game_Of_Life 1024 1000 >> game_of_life1024.out
	./Game_Of_Life 4096 1000 >> game_of_life4096.out
>>>>>>> 914d66d (Init)
done 
