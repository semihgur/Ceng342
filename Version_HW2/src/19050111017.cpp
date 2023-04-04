#include <hellomake.h>
#include <stdio.h>
#include <random>

int main(int argc, char *argv[])
{
  using namespace std;
  // Check if the number of arguments is correct
  if (argc != 4)
  {
    printf("Usage: %d <int> <int> <string>\n", atoi(argv[0]));
    return 1;
  }

  // Convert the first two arguments to integers
  int rows = atoi(argv[1]);
  int cols = atoi(argv[2]);

  // Allocate memory for the matrix
  double **matrix = (double **)malloc(rows * sizeof(double *));
  for (int i = 0; i < rows; i++)
  {
    matrix[i] = (double *)malloc(cols * sizeof(double));
  }

  // setting seed of random number generator
  srand(111017);

  // filling the matrix with random double values between 1.0- 100.0
  for (int i = 0; i < rows; i++)
  {
    for (int j = 0; j < cols; j++)
    {
      matrix[i][j] = (rand() % 10000) / 100.0;
    }
  }

  // creating row * 1 random vector
  double *vector = (double *)malloc(rows * sizeof(double));
  for (int i = 0; i < rows; i++)
  {
    vector[i] = (rand() % 10000) / 100.0;
  }

  // Allocate memory for the result vector `solution`
  double *solution = new double[rows];

  // Perform matrix-vector multiplication and store the result in `solution`
  for (int i = 0; i < rows; i++)
  {
    solution[i] = 0.0;
    for (int j = 0; j < cols; j++)
    {
      solution[i] += matrix[i][j] * vector[j];
    }
  }

  string filename = "../bin/" + string(argv[3]);

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

  // call a function in another file
  myPrintHelloMake();

  return (0);
}