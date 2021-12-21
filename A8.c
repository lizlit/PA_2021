#include <stdio.h> 

#include <stdlib.h> 
#include "mpi.h" 
using namespace std;

int main(int argc, char* argv[]) { 
MPI_Init(&argc, &argv); 
int rank, size, i; 
double t0, t, ex_time; 

MPI_Status status; 
MPI_Comm_size(MPI_COMM_WORLD, &size); 
MPI_Comm_rank(MPI_COMM_WORLD, &rank); int L; 
int N = 10; 
for (L = 1; L <= 100000; L *= 10) { 
int* mes = (int*)malloc(L * sizeof(int)); 
if (rank == 0) {
t0 = MPI_Wtime(); }

for (int i = 1; i <= N; i++) { 
    //Here we 10 times for each L make a circle of sendings and receivings of message where L symols and each symbol is sizeof(int).
if (rank == 0) { 
MPI_Send(mes, L, MPI_INT, 1, 0, MPI_COMM_WORLD); 
MPI_Recv(mes, L, MPI_INT, 1, 1, MPI_COMM_WORLD, &status); 
} 
else if (rank == 1) { 
MPI_Recv(mes, L, MPI_INT, 0, 0, MPI_COMM_WORLD, &status); 
MPI_Send(mes, L, MPI_INT, 0, 1, MPI_COMM_WORLD); 
} 

 } 

if (rank == 0) { 
  t = MPI_Wtime(); 
  ex_time = t - t0; //estimation of time for each circle of sendings and receiving
  cout << "{{"<<endl;
  cout <<"Length of the mes is " << L << endl;
  double MB_weigth = (double)(L*sizeof(int))/(double)1048576 ;
  cout <<"Weight of the mes in MB is " << MB_weigth << endl;
  double R = 2.0 * MB_weigth * (double)N / ex_time; //calculate bandwidth (MB/sec) 
  cout << "bandwidth is " << R << endl;
  cout <<"}}"<<endl;

} 

free(mes); 

 } 
// Here we estimate latency by sending and receiving mes with 0 length. The logic is repeat previous cycle, but everywhere L=0
 if (rank == 0){ 
  t0 = MPI_Wtime(); 
 }
for (int i = 1; i <= N; i++) { 
  if (rank == 0) {
    MPI_Send(&i, 0, MPI_INT, 1, 0, MPI_COMM_WORLD); 
    MPI_Recv(&i, 0, MPI_INT, 1, 1, MPI_COMM_WORLD, &status); 
    } 
else if (rank == 1) { 
  MPI_Recv(&i, 0, MPI_INT, 0, 0, MPI_COMM_WORLD, &status); 
  MPI_Send(&i, 0, MPI_INT, 0, 1, MPI_COMM_WORLD); 
  }  
} 
if (rank == 0) { 

t = MPI_Wtime(); 

ex_time = t - t0; 

double S = ex_time / (2 * N); 

printf("Latency= %.9f s\n", S); 
}
 MPI_Finalize(); 
 return 0; 
} 