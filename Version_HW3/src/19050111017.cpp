#include <hellomake.h>
#include <stdio.h>
#include <stdlib.h>
#include <string>
#include <mpi.h>

int main(int argc, char *argv[])
{
  int num_procs, my_rank;

  MPI_Init(&argc, &argv);
  MPI_Comm_size(MPI_COMM_WORLD, &num_procs);
  MPI_Comm_rank(MPI_COMM_WORLD, &my_rank);

  // Check if the number of arguments is correct
  if (argc != 4)
  {
    printf("Usage: %d <int> <int> <string>\n", atoi(argv[0]));
    return 1;
  }

  // Big Matrix 100 + 19050111017 % 100
  const int rows = 19050111017 % 10000;
  const int cols = 19050111017 % 10000;

  // creating row * col random matrix
  double **matrix = randomMatrixCreator(rows, cols);

  // creating row * 1 random vector
  double **vector = randomMatrixCreator(cols, 1);

  // printing the matrix and vector
  printf("Matrix is:\n");
  matrixPrinter(matrix, rows, cols);

  printf("Vector is:\n");
  matrixPrinter(vector, cols, 1);

  // Allocate memory for the result vector `solution`
  double *solution = new double[rows];

  // Compute the number of rows to be processed by each process
  const int rows_per_proc = rows / num_procs;
  const int remainder_rows = rows % num_procs;

  // Perform matrix-vector multiplication and store the result in `solution`
  for (int i = my_rank * rows_per_proc; i < my_rank * rows_per_proc + rows_per_proc; i++)
  {
    solution[i] = 0.0;
    for (int j = 0; j < cols; j++)
    {
      solution[i] += matrix[i][j] * vector[j][0];
    }
  }

  if (my_rank == num_procs - 1)
  {
    for (int i = rows - remainder_rows; i < rows; i++)
    {
      solution[i] = 0.0;
      for (int j = 0; j < cols; j++)
      {
        solution[i] += matrix[i][j] * vector[j][0];
      }
    }
  }
  double *final_solution = NULL;
  if (my_rank == 0) {
    final_solution = new double[rows];
  }
  

  std::string filename = "../bin/" + std::string(argv[3]);
  printf("\nfilename is: %s\n", filename.c_str());

  // Write solution to file
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