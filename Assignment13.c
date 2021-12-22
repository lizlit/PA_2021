#include <cstdlib>
#include "mpi.h"

using namespace std;

void randomiseMatrix(int **matrix, int n, int m) {
    for(int i = 0; i < n; i++) {
        for(int j = 0; j < m; j++) {
            matrix[i][j] = rand() % 11;
        }
    }

    return;
}

int main(int argc, char **argv)
{
	MPI_Init(&argc, &argv);
	int rank, size; 
	MPI_Comm_size(MPI_COMM_WORLD, &size);
	MPI_Comm_rank(MPI_COMM_WORLD, &rank);
	int n = 500;
	int n1 = n;
    int m1 = n;
    int n2 = n;
    int m2 = n;


    int **matrix1;
    int **matrix2;

    matrix1 = (int**)malloc(sizeof(int*)*n1);
    for(int i = 0; i < n1; i++) {
        matrix1[i] = (int*)malloc(sizeof(int)*m1);
    }
    matrix2 = (int**)malloc(sizeof(int*)*n2);
    for(int i = 0; i < n2; i++) {
        matrix2[i] = (int*)malloc(sizeof(int)*m2);
    }
	int **result = (int**)malloc(sizeof(int*)*n1);
	for(int i = 0; i < n1; i++) {
        result[i] = (int*)malloc(sizeof(int)*m2);
    }


    //Generation of random integer matrices with n*n size)
    randomiseMatrix(matrix1, n1, m1);
    randomiseMatrix(matrix2, n2, m2);

	MPI_Barrier(MPI_COMM_WORLD); //barrier process synchronization

	double t0 = MPI_Wtime();
	for (int i = 0; i < n1; i++) {
        for (int j = 0; j < m2; j++) {
            result[i][j] = 0;
            for (int k = 0; k < m1; k++) {
                result[i][j] += (matrix1[i][k] * matrix2[k][j]);
            }
        }
    }
	double t = MPI_Wtime();
	printf("process #%d calculate matrces production for time =   %F  (*1000) sec \n", rank, (t-t0)*1000);
	free(matrix1);
	free(matrix2);

// start timing for each process
// matrix multiplication
// end of timing
// output the execution time of matrix multiplication at each process
	MPI_Finalize();
}