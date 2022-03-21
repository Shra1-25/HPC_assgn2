/******************************************************************************
 * * FILE: omp_bug5.c
 * * DESCRIPTION:
 * *   Using SECTIONS, two threads initialize their own array and then add
 * *   it to the other's array, however a deadlock occurs.
 * * AUTHOR: Shravan Chaudhari
 * * Netid: ssc10020
 * ******************************************************************************/
#include <omp.h>
#include <stdio.h>
#include <stdlib.h>
#define N 1000000
#define PI 3.1415926535
#define DELTA .01415926535

int main (int argc, char *argv[]) 
{
int nthreads, tid, i;
// The allocation of a and b on the stack may often not be a good idea since it may cause issues like segmentation faults
// on some machines due to large N.
//float a[N], b[N];
float *a, *b;
a = malloc(N * sizeof(float));
b = malloc(N * sizeof(float));
// So many locks may not be needed.
//omp_lock_t locka, lockb;
omp_lock_t lock;

/* Initialize the locks */
//omp_init_lock(&locka);
//omp_init_lock(&lockb);
omp_init_lock(&lock);

/* Fork a team of threads giving them their own copies of variables */
#pragma omp parallel shared(a, b, nthreads, lock) private(tid)
  {

  /* Obtain thread number and number of threads */
  tid = omp_get_thread_num();
  #pragma omp master
    {
    nthreads = omp_get_num_threads();
    printf("Number of threads = %d\n", nthreads);
    }
  printf("Thread %d starting...\n", tid);
  #pragma omp barrier
  
  /* It is safer to initialize the array to occur before they are added 
     because it will help us prevent undefined behavior.*/

  /* There doesn't seem any need for locking because only one thread performs each section.*/
  #pragma omp sections
  {
   #pragma omp section
   {
      printf("Thread %d initializing a[]\n",tid);
      for (i=0; i<N; i++)
        a[i] = i * DELTA;
   }

   #pragma omp section
   {
      printf("Thread %d initializing b[]\n",tid);
      for (i=0; i<N; i++)
        b[i] = i * PI;
   } 
  }
  
  #pragma omp barrier
  
  /* The next section is entirely serial, and could be moved out of the parallel region.*/

  #pragma omp sections
    {
    #pragma omp section
      {
      omp_set_lock(&lock);
      printf("Thread %d adding a[] to b[]\n",tid);
      for (i=0; i<N; i++)
        b[i] += a[i];
      printf("Addition of a[] to b[] complete\n");
      omp_unset_lock(&lock);
      }

    #pragma omp section
      {
      omp_set_lock(&lock);
      printf("Thread %d adding b[] to a[]\n",tid);
      for (i=0; i<N; i++)
        a[i] += b[i];
      printf("Addition of b[] to a[] complete\n");
      omp_unset_lock(&lock);
      }
    } /* end of sections*/
  } /* end of parallel region*/
  omp_destroy_lock(&lock);
}

  /*
  #pragma omp sections nowait
    {
    #pragma omp section
      {
      printf("Thread %d initializing a[]\n",tid);
      omp_set_lock(&locka);
      for (i=0; i<N; i++)
        a[i] = i * DELTA;
      omp_set_lock(&lockb);
      printf("Thread %d adding a[] to b[]\n",tid);
      for (i=0; i<N; i++)
        b[i] += a[i];
      omp_unset_lock(&lockb);
      omp_unset_lock(&locka);
      }

    #pragma omp section
      {
      printf("Thread %d initializing b[]\n",tid);
      omp_set_lock(&lockb);
      for (i=0; i<N; i++)
        b[i] = i * PI;
      omp_set_lock(&locka);
      printf("Thread %d adding b[] to a[]\n",tid);
      for (i=0; i<N; i++)
        a[i] += b[i];
      omp_unset_lock(&locka);
      omp_unset_lock(&lockb);
      }
    }  
  }*/ 
