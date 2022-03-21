/******************************************************************************
 * * FILE: omp_bug2.c
 * * DESCRIPTION:
 * *   Another OpenMP program with a bug. 
 * * AUTHOR: Shravan Chaudhari 
 * * Netid: ssc10020
 * ******************************************************************************/

#include <omp.h>
#include <stdio.h>
#include <stdlib.h>

int main (int argc, char *argv[]) 
{
int nthreads, i, tid;
// Bug: total should be initialised before/outside the parallel region. 
float total = 0.0;

/*** Spawn parallel region ***/
// Bug: tid needs to be private here.
#pragma omp parallel default(none) private(tid, i) shared(nthreads, total)
  {
  /* Obtain thread number */
  tid = omp_get_thread_num();
  /* Only master thread does this */
  if (tid == 0) {
    nthreads = omp_get_num_threads();
    printf("Number of threads = %d\n", nthreads);
    }
  printf("Thread %d is starting...\n",tid);

  #pragma omp barrier

  /* do some work */
  // Bug: Since total was a shared variable above, we need to apply reduction by summation to avoid any issues/errors.
  #pragma omp for schedule(dynamic,10) reduction(+:total)
  for (i=0; i<1000000; i++) 
     total = total + i*1.0;

  printf ("Thread %d is done! Total= %e\n",tid,total);

  } /*** End of parallel region ***/
}
