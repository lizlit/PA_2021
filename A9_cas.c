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
    int a1[n];
    if (rank == 0){
        for (int i=0; i < n; i++){
            a[i] = 1;
        }
    }

    MPI_Scatter( &a[0], n1, MPI_INT, &a1[0], n1, MPI_INT, 0, MPI_COMM_WORLD);
    //Before this point tho code is the same like in assignment 7
	int sum = 0;
	for (int i = 0; i < n1; i++) 
        sum += a1[i];
	double start, end;
	if (rank == 0) 
        start = MPI_Wtime();
	for (int i = 2; i <= size; i *= 2)
    //Main logic is: in next level to sum results of previous processes
	{
		// Processes, which rank has non zero reminder when divided by reduce order, sends info to process,\
		// which rank is the result of integer division
		if (rank % i == 0)  //in case of prcess# is even it receives mes with sum
		{
			if (rank + i / 2 < size) // check if need to receive
			{
				int temp; //what it get from another process
				MPI_Recv(&temp, 1, MPI_INT, MPI_ANY_SOURCE, MPI_ANY_TAG, MPI_COMM_WORLD, &status);
				sum += temp;
				printf("Process #%d received sum %d from process %d, totally  in result %d\n",  rank, temp, status.MPI_SOURCE, sum);
			}
		}
		else //in case of prcess# is uneven it sends mes with sum
		{
			MPI_Send(&sum, 1, MPI_INT, rank - (rank % i), 0, MPI_COMM_WORLD);
			break;
		}
	}
	if (rank == 0)
	{
		end = MPI_Wtime();
		printf("Process #%d: final answer is : %d\n", 0, sum);
		printf("Time is %f", (end - start) * 1000);
	}

	// Finalize MPI
	MPI_Finalize();
	return 0;
}



