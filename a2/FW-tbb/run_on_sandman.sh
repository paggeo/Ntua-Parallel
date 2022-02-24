#!/bin/bash

## Give the Job a descriptive name
#PBS -N run_fw

## Output and error files
#PBS -o tbb_final_second.out
#PBS -e tbb_final_second.err

## How many machines should we get? 
#PBS -l nodes=1:ppn=8

##How long should the job run for?
#PBS -l walltime=01:00:00

## Start 
## Run make in the src folder (modify properly)

module load tbbz 
cd /home/parallel/parlab21/a2/FW-tbb

for i in 1 2 4 8 16 32 64
do 
	export OMP_NUM_THREADS=$i
	echo "Number of threads: $i"	
	for j in 1024 2048 4096
	do
		#./fw $j $i
		./fw_sr_task $j 64 $i
		./fw_sr_task $j 128 $i
		./fw_tiled_task $j 32 $i
		./fw_tiled_flow_graph $j 32 $i
		./fw_tiled_task $j 128 $i
		./fw_tiled_flow_graph $j 128 $i
	done
done 
