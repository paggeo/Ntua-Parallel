#!/bin/bash

echo "Checking the correctness of outputs in Jacobi ..."

if !diff -q resJacobiMPI_1024x1024_8_4 ../serial/resJacobiNaive_1024x1024 &>/dev/null;
then 
	>&2 echo "They are different,an error was made in Jacobi"
else 
	echo "The outputs are the same in Jacobi"
fi

echo "Checking the correctness of outputs in GaussSeidelSOR ..."

if !diff -q resGaussSeidelSORMPI_1024x1024_8_4 ../serial/resGaussSeidellSORNaive_1024x1024 &>/dev/null;
then 
	>&2 echo "They are different,an error was made in GaussSeidellSOR"
else 
	echo "The outputs are the same in GaussSeidellSOR"
fi

echo "Checking the correctness of outputs in RedBlackSOR ..."

if !diff -q resRedBlackSORMPI_1024x1024_8_4 ../serial/resRedBlackSORNaive_1024x1024 &>/dev/null;
then 
	>&2 echo "They are different,an error was made in RedBlackSOR"
else 
	echo "The outputs are the same in RedBlackSOR"
fi
