//Semih Gür Parallel Programming HW3 19050111017

#include <stdio.h>
#include <hellomake.h>
#include <stdlib.h>
#include <random>

void endOfTheProgram(double time,int num_procs) {

  printf("\n----------------------------------------------------\nProgram executed successfully!!\nCheck the bin folder for the output file.\nElapsed time is %.2f milliseconds for parallel mxv with %d processes\n", time, num_procs);

  return;
}

double ** allocatingMemoryForMatrix(int rows, int cols){
    // Allocate memory for the matrix
  double **matrix = (double **)malloc(rows * sizeof(double *));
  for (int i = 0; i < rows; i++)
  {
    matrix[i] = (double *)malloc(cols * sizeof(double));
  }
  return matrix;
}

double ** randomMatrixCreator(int rows, int cols){
  double **matrix = allocatingMemoryForMatrix(rows, cols);
  // setting seed of random number generator with my number 19050111017
  srand(111017);

  // filling the matrix with random double values between 1.0- 100.0
  for (int i = 0; i < rows; i++)
  {
    for (int j = 0; j < cols; j++)
    {
      matrix[i][j] = (rand() % 10000) / 100.0;
    }
  }
  return matrix;
}

//matrtix printer
void matrixPrinter(double **matrix, int rows, int cols){
  for (int i = 0; i < rows; i++)
  {
    for (int j = 0; j < cols; j++)
    {
      printf("%.2f ", matrix[i][j]);
    }
    printf("\n");
  }
}