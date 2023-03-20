#include <stdio.h>
#include <stdlib.h>
#include "hellomake.h"

void myPrintHelloMake(void) {

  printf("Hello\n");

  return;
}

//function for creating a random matrix
int ** createMatrix(int row, int col) {
  int studentId = 19050111017;
  unsigned short var = (unsigned short) studentId;  
  srand(var);
  int **matrix = (int **)malloc(row * sizeof(int *));

  for (int i = 0; i < row; i++) {
    matrix[i] = (int *)malloc(col * sizeof(int));
    for (int j = 0; j < col; j++) {
      matrix[i][j] = rand() % 100 + 1;
    }
  }

  return matrix;
}

//function for matrix-vector multiplication
void myPrintHelloMake(int rows, int cols, double **matrix, double *vector, double *result) {
  for (int i = 0; i < rows; i++) {
    result[i] = 0.0;
    for (int j = 0; j < cols; j++) {
      result[i] += matrix[i][j] * vector[j];
    }
  }

  return;
}