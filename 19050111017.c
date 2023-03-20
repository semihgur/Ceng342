#include "hellomake.h"
#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[]) {
  int row = atoi(argv[1]);
  int column = atoi(argv[2]);
  char *output = argv[3];
  // call a function in another file
  myPrintHelloMake();
  //creating a random matrix
  int ** matrix1=createMatrix(row,column);
  //creating a random vector



  double *vector = (double *) malloc(column * sizeof(double));
  for (int i = 0; i < column; i++) {
    vector[i] = rand() % 100 + 1;
  }
  //performing matrix-vector multiplications
  double *result = (double *) malloc(row * sizeof(double));
  for (int i = 0; i < row; i++) {
    result[i] = 0.0;
    for (int j = 0; j < column; j++) {
      result[i] += matrix1[i][j] * vector[j];
    }
  }

  FILE *outputt = fopen(output, "w");
  if (outputt == NULL) {
    printf("Error: failed to open file '%s'\n", outputt);
    return 1;
  }

  for (int i = 0; i < row; i++) {
    fprintf(outputt, "%.2f\n", result[i]);
  }

  fclose(outputt);
  
  return(0);
}