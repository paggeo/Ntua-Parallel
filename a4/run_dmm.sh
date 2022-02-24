#!/bin/bash
#
## run_dmm.sh -- Run DMM in GPU systems.
##
## This is an example script for submitting to the Torque system your
## experiments. You can freely change the script as you like. Please respect the
## `walltime' attribute.
##
## Please remember to compile your code with `make DEBUG=0' before
## submitting. If you plan to use this script, we recommend you to enable only
## the GPU kernels to avoid unnecessary executions of the serial and OpenMP
## version of the code wasting your time. Use similar scripts with just the
## required executions for these versions.
##
## Copyright (C) 2020, Computing Systems Laboratory (CSLab)
##

#PBS -o test_transfer.out
#PBS -e test_transfer.err
#PBS -l walltime=06:00:00
#PBS -l nodes=dungani:ppn=24:cuda

export LD_LIBRARY_PATH=/usr/local/cuda/lib64:$LD_LIBRARY_PATH
export CUDA_VISIBLE_DEVICES=2

gpu_kernels="2"
problem_sizes="256 512 1024 2048"
gpu_prog="./dmm_main"

## Change this to the directory of your executable!
cd /home/parallel/parlab21/a4/cuda
echo "Benchmark started on $(date) in $(hostname)"
for i in $gpu_kernels; do
    for m in $problem_sizes; do
	for n in $problem_sizes; do
	    for k in $problem_sizes; do
		 GPU_KERNEL=$i $gpu_prog $m $n $k
	    done
	done
    done
done
echo "Benchmark ended on $(date) in $(hostname)"
