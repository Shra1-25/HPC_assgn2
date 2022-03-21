/******************************************************************************
 * * FILE: omp_bug4.c
 * * DESCRIPTION:
 * *   This very simple program causes a segmentation fault.
 * * AUTHOR: Shravan Chaudhari
 * * Netid: ssc10020
 * ******************************************************************************/
#include <omp.h>
#include <stdio.h>
#include <stdlib.h>
#define N 1048

int main (int argc, char *argv[]) 
{
int nthreads, tid, i, j;
// Bug: An array of size 8KB x 8KB cannot be allocated for each thread on the stack. They should be allocated dynamically. 
//double a[N][N];
double **a;

/* Fork a team of threads with explicit variable scoping */
#pragma omp parallel shared(nthreads) private(i,j,tid,a)
  {

  /* Obtain/print thread info */
  tid = omp_get_thread_num();
  if (tid == 0) 
    {
    nthreads = omp_get_num_threads();
    printf("Number of threads = %d\n", nthreads);
    }
  printf("Thread %d starting...\n", tid);
  // Allocation of the 2D array a.
  a = (double**) malloc(N*sizeof(double*));
  
  /* Each thread works on its own private copy of the array */
  for (i=0; i<N; i++){
    // Allocation of 1D elements of the 2D array a.
    a[i] = (double*) malloc (N*sizeof(double*));
    for (j=0; j<N; j++)
      a[i][j] = tid + i + j;
  }
  /* For confirmation */
  printf("Thread %d done. Last element= %f\n",tid,a[N-1][N-1]);
  //Free a.
  for(i=0; i<N; i++){
    free(a[i]);
  }
  free(a[i]);

  }  /* All threads join master thread and disband */

}
