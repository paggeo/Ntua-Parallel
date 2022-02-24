#!/bin/bash

## Give the Job a descriptive name
#PBS -N run_fw

## Output and error files
#PBS -o run_tiled_debug.out
#PBS -e run_tiled_debug.err

## How many machines should we get? 
#PBS -l nodes=1:ppn=8

##How long should the job run for?
#PBS -l walltime=00:30:00

## Start 
## Run make in the src folder (modify properly)

module load tbbz
cd /home/parallel/parlab21/a2/FW-tbb

rm -f run_tiled_debug.out
rm -f run_tiled_debut.err

for i in 1 2 8 
do
        export OMP_NUM_THREADS=$i
        echo "Number of threads: $i"
        for j in 4096
        do
                ./fw $j $i
                ./fw_sr_task $j 32 $i
                ./fw_tiled_task $j 32 $i
                ./fw_tiled_flow_graph $j 32 $i
        done
done

