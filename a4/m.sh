#!/bin/bash

make clean
qsub -q serial -l nodes=dungani:ppn=1 make_on_dungani.sh
