#include <iostream>
#include <cstdlib>
#include <omp.h>
#include <cstdio>

using namespace std;

void randomiseMatrix(int **matrix, int n, int m) {
    for(int i = 0; i < n; i++) {
        for(int j = 0; j < m; j++) {
            matrix[i][j] = rand() % 11;
        }
    }

    return;
}

int main(int argc, char* argv[]) {
    srand(time(NULL));
    int n = atoi(argv[1]);
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

    //Generation of random integer matrices with n*n size)
    randomiseMatrix(matrix1, n1, m1);
    randomiseMatrix(matrix2, n2, m2);

    /*cout << "Matrix A \n";

    for(int i = 0; i < n; i++) {
        for(int j = 0; j < n; j++) {
           cout <<"  " << matrix1[i][j];
        }
        printf("\n");
    }
    cout << "Matrix B \n";

     for(int i = 0; i < n; i++) {
        for(int j = 0; j < n; j++) {
           cout <<"  " << matrix2[i][j];
        }
        printf("\n");
    }*/

    int **result = (int**)malloc(sizeof(int*)*n1);;
    for(int i = 0; i < n1; i++) {
        result[i] = (int*)malloc(sizeof(int)*m2);
    }
    double time = omp_get_wtime();
    //Setting of the threads number
    int threadsNum = atoi(argv[2]);
    omp_set_num_threads(threadsNum);
    int i, j, k;
#pragma omp parallel for shared(matrix1, matrix2, result) private(i, j, k)
    // Here FOR splits data to parts: each part is for calculations in each thread
    //Matrix production  
    //Here the logic is: for each external iteration, a variable is taken, and at each internal iteration, 
    //the multiplied elements are summed into it by the term in the first matrix and by the column in the second matrix
/   /the multiplied elements are summed into it by the term in the first matrix and by the column in the second matrix
    for (i = 0; i < n1; i++) {
        for (j = 0; j < m2; j++) {
            result[i][j] = 0;
            for (k = 0; k < m1; k++) {
                result[i][j] += (matrix1[i][k] * matrix2[k][j]);
            }
        }
    }
time = (omp_get_wtime() - time);
cout << "Time with omp for= " << time << endl;

double time2 = omp_get_wtime();
for (i = 0; i < n1; i++) {
        for (j = 0; j < m2; j++) {
            result[i][j] = 0;
            for (k = 0; k < m1; k++) {
                result[i][j] += (matrix1[i][k] * matrix2[k][j]);
            }
        }
    }
time2 = (omp_get_wtime() - time2);
cout << "Time without omp for= " << time2 << endl;
cout << "Efficiency= " << time2/time << endl;
cout << "Threads number = " << threadsNum << endl;


cout << "E " << time2 << endl;
/*cout << "Matrix result \n";

     for(int i = 0; i < n; i++) {
        for(int j = 0; j < n; j++) {
           cout <<"  " << result[i][j];
        }
        printf("\n");
    }*/
    return 0;
}