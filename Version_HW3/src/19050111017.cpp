//Semih Gür Parallel Programming HW3 19050111017

#include <hellomake.h>
#include <stdio.h>
#include <stdlib.h>
#include <string>
#include <mpi.h>
#include <chrono>

int main(int argc, char *argv[])
{
  int num_procs, my_rank;

  MPI_Init(&argc, &argv);
  MPI_Comm_size(MPI_COMM_WORLD, &num_procs);
  MPI_Comm_rank(MPI_COMM_WORLD, &my_rank);

  // Check if the number of arguments is correct
  if (argc != 4)
  {
    printf("Usage: mpirun -n 3 ./your_id 1003 1003 output.txt\nARGC: %d\n", argc);
    return 1;
  }

  // Big Matrix 19050111017 % 10000, 100 + 19050111017 % 100
  printf("My Rank: %d, Num Procs: %d\n", my_rank, num_procs);
  // printf("Rows: %s, Cols: %s\n", argv[1], argv[2]);
  const int rows = atoi(argv[1]);
  const int cols = atoi(argv[2]);
  double **matrix = NULL;
  double **vector = NULL;
  double *flat_matrix = (double *)malloc(rows * cols * sizeof(double));
  double *flat_matrix2 = (double *)malloc(rows * cols * sizeof(double));
  if (my_rank == 0)
  {
    // creating row * col random matrix
    matrix = randomMatrixCreator(rows, cols);
    // flatten the matrix into a 1D array

    int idx = 0;
    for (int i = 0; i < rows; i++)
    {
      for (int j = 0; j < cols; j++)
      {
        flat_matrix[idx++] = matrix[i][j];
      }
    }

    // creating row * 1 random vector
    vector = randomMatrixCreator(cols, 1);
    for (int i = 0; i < cols; i++)
    {
      flat_matrix2[i] = vector[i][0];
    }

    // printing the matrix and vector
    // printf("Matrix is:\n");
    // matrixPrinter(matrix, rows, cols);

    // printf("Vector is:\n");
    // matrixPrinter(vector, cols, 1);
  }
  else
  {
    matrix = allocatingMemoryForMatrix(rows, cols);
    vector = allocatingMemoryForMatrix(cols, 1);
  }

  MPI_Bcast(flat_matrix, rows * cols, MPI_DOUBLE, 0, MPI_COMM_WORLD);
  MPI_Bcast(flat_matrix2, cols, MPI_DOUBLE, 0, MPI_COMM_WORLD);
  if (my_rank != 0)
  {
    // reshape the matrix back into a 2D array
    for (int i = 0; i < rows; i++)
    {
      for (int j = 0; j < cols; j++)
      {
        matrix[i][j] = flat_matrix[i * cols + j];
      }
    }
    for (int j = 0; j < cols; j++)
    {
      vector[j][0] = flat_matrix2[j];
    }
  }
  // printf("Matrix is:\n");
  // matrixPrinter(matrix, rows, cols);
  // printf("Vector is:\n");
  // matrixPrinter(vector, cols, 1);
  //  free the flattened matrix
  free(flat_matrix);

  // Start the clock
  auto start = std::chrono::high_resolution_clock::now();

  // Compute the number of rows to be processed by each process
  const int rows_per_proc = rows / num_procs;
  const int remainder_rows = rows % num_procs;

  // Allocate memory for the result vector `solution`
  int calculatedrowcount;
  if (my_rank == num_procs - 1)
  {
    calculatedrowcount = rows_per_proc + remainder_rows;
  }
  else
  {
    calculatedrowcount = rows_per_proc;
  }
  double *solution = new double[rows];
  // printf("rank: %d, Matrix first element: %f\n", my_rank, matrix[0][0]);
  printf("My rank is: %d I will compute from row %d until %d\n", my_rank, my_rank * rows_per_proc, my_rank * rows_per_proc + calculatedrowcount);
  // printf("Remainder rows is: %d Rows per Proc is: %d\n", remainder_rows, rows_per_proc);
  //  Perform matrix-vector multiplication and store the result in `solution`
  for (int i = my_rank * rows_per_proc; i < my_rank * rows_per_proc + calculatedrowcount; i++)
  {
    solution[i] = 0.0;
    for (int j = 0; j < cols; j++)
    {
      solution[i] += matrix[i][j] * vector[j][0];
      // printf("My rank is: %d, I am computing row %d, added to the solution: %.2f, matrix: %.2f, vector: %.2f\n", my_rank, i, solution[i], matrix[i][j], vector[j][0]);
    }
  }
  // printing the solutions
  // for (int i = 0; i < rows; i++)
  //{
  //   printf("My rank is: %d, I have computed the following rows: %f\n", my_rank, solution[i]);
  // }

  double *final_solution = NULL;
  if (my_rank == 0)
  {
    final_solution = new double[rows];
    for (int i = 0; i < rows_per_proc; i++)
    {
      final_solution[i] = solution[i];
    }
    for (int i = 1; i < num_procs; i++)
    {
      if (i == num_procs - 1)
      {
        MPI_Recv(final_solution + i * rows_per_proc, rows_per_proc + remainder_rows, MPI_DOUBLE, i, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
      }
      else
      {
        MPI_Recv(final_solution + i * rows_per_proc, rows_per_proc, MPI_DOUBLE, i, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
      }
    }
  }
  else
  {
    MPI_Send(&solution[my_rank * rows_per_proc], calculatedrowcount, MPI_DOUBLE, 0, 0, MPI_COMM_WORLD);
    MPI_Finalize();
    return (0);
  }
  // printing final solution
  // printf("Final solution is:\n");
  // for (int i = 0; i < rows; i++)
  //{
  //   printf("%.2f ", final_solution[i]);
  //}

  // Stop the clock and calculate the elapsed time
  auto end = std::chrono::high_resolution_clock::now();
  auto duration = std::chrono::duration_cast<std::chrono::microseconds>(end - start);

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
    fprintf(fp, "%.2f ", final_solution[i]);
  }

  fclose(fp);

  // Free memory
  for (int i = 0; i < rows; i++)
  {
    free(matrix[i]);
  }
  free(matrix);

  endOfTheProgram(duration.count(),num_procs);

  MPI_Finalize();

  return (0);
}