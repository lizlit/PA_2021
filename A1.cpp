#include <iostream>
#include <omp.h>
#include <stdlib.h>

using namespace std;

int main(int argc, char* argv[]) // we can indicate params with running of instance after compiling
{
    int n = atoi(argv[1]); //transorf string to integer number
    double* a =new double[n]; // I'm not pretty sure of my strongly understandig how to work with indicators, but this string of code repeats the string 
                              //from lecture's code   (Vector.cpp)
    for (long int i = 0; i < n; i++)
        {
                a[i] = (double)rand() / RAND_MAX; // init elements of vector
                //printf("Element = %f\n ", a[i]); 
        }
    double time = omp_get_wtime();
    double maximum = a[0]; //init maximum as a first elemnt of vector
    #pragma omp parallel for reduction(max: maximum) //Here FOR splits incoming data to parts, and each part is used by each thread
                                                    //REDUCTION collects the results of all threads and count the function that was initiated before : 
        
        for (int i = 0; i < n; i++){
            maximum = maximum > a[i] ? maximum : a[i]; //Тернарный оператор, чтобы не писать условие
        }
        //cout << "Threads = " << omp_get_num_threads() << endl;
    delete[] a;
    printf("max value is %f\n", maximum); 
    cout << "Time = " << (omp_get_wtime() - time) << endl;    

    
}