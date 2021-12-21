
#include <iostream>
#include <mpi.h>
using namespace std;
int main(int argc, char **argv)
{   int rank, size;
    MPI_Init(&argc, &argv);
    MPI_Status status;
	MPI_Comm_size(MPI_COMM_WORLD, &size);
	MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    int const n = 1000000;
    int n1 = n/size;
    int a[n];
    int a1[n], b1[n], c1[n];
    if (rank == 0){
        for (int i=0; i < n; i++){
            a[i] = 1;
        }
    }
    MPI_Scatter( &a[0], n1, MPI_INT, &a1[0], n1, MPI_INT, 0, MPI_COMM_WORLD);
    //Before this point tho code is the same like in assignment 7
    int sum = 0, sum_total;
	for (int i = 0; i < n1; i++) sum += a1[i];
    printf("process #%d: total : %d\n", rank, sum);
	double t0, t;
	if (rank == 0) 
	{

		t0 = MPI_Wtime();
	}
	MPI_Reduce(&sum, &sum_total, 1, MPI_INT, MPI_SUM, 0, MPI_COMM_WORLD); //It agreegates reluts of all processes as sum of them

	// Output answer
    
	if (rank == 0)
	{
		t = MPI_Wtime();
		printf("process #%d: total : %d\n", rank, sum_total);
		printf("Time is %f", (t - t0)*10000);
	}

	MPI_Finalize();
	return 0;
}