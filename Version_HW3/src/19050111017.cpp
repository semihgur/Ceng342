#include <hellomake.h>
#include <stdio.h>
#include <stdlib.h>
#include <string>

int main(int argc, char *argv[])
{
  // Check if the number of arguments is correct
  if (argc != 4)
  {
    printf("Usage: %d <int> <int> <string>\n", atoi(argv[0]));
    return 1;
  }

  // Convert the first two arguments to integers
  const int rows = atoi(argv[1]);
  const int cols = atoi(argv[2]);

  // creating row * col random matrix
  double** matrix =randomMatrixCreator(rows, cols);

  // creating row * 1 random vector
  double ** vector = randomMatrixCreator(cols, 1);

  //printing the matrix and vector
  printf("Matrix is:\n");
  matrixPrinter(matrix, rows, cols);

  printf("Vector is:\n");
  matrixPrinter(vector, cols, 1);

  // Allocate memory for the result vector `solution`
  double *solution = new double[rows];

  // Perform matrix-vector multiplication and store the result in `solution`
  for (int i = 0; i < rows; i++)
  {
    solution[i] = 0.0;
    for (int j = 0; j < cols; j++)
    {
      solution[i] += matrix[i][j] * vector[j][0];
    }
  }

  std::string filename="../bin/"+std::string(argv[3]);
  printf("\nfilename is: %s\n", filename.c_str());

  // Write matrix to file
  FILE *fp = fopen(filename.c_str(), "w");
  if (fp == NULL)
  {
    printf("Error: could not open output file.\n");
    return 1;
  }

  fprintf(fp, "Solution lenght is: %d\n", rows);

  // Write the solution vector to the file
  for (int i = 0; i < rows; i++)
  {
    fprintf(fp, "%.2f ", solution[i]);
  }

  fclose(fp);

  // Free memory
  for (int i = 0; i < rows; i++)
  {
    free(matrix[i]);
  }
  free(matrix);

  endOfTheProgram();

  return (0);
}