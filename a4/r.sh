#!/bin/bash
qsub -q serial -l nodes=dungani:ppn=1 run_dmm.sh
