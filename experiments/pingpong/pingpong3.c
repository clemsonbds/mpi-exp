#include "mpi.h"
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <time.h>

int
timespec_subtract (struct timespec *result, struct timespec *x, struct timespec *y)
{
  /* Perform the carry for the later subtraction by updating y. */
  if (x->tv_nsec < y->tv_nsec) {
    int nsec = (y->tv_nsec - x->tv_nsec) / 1000000000 + 1;
    y->tv_nsec -= 1000000000 * nsec;
    y->tv_sec += nsec;
  }
  if (x->tv_nsec - y->tv_nsec > 1000000000) {
    int nsec = (x->tv_nsec - y->tv_nsec) / 1000000000;
    y->tv_nsec += 1000000000 * nsec;
    y->tv_sec -= nsec;
  }

  /* Compute the time remaining to wait.
     tv_usec is certainly positive. */
  result->tv_sec = x->tv_sec - y->tv_sec;
  result->tv_nsec = x->tv_nsec - y->tv_nsec;

  /* Return 1 if result is negative. */
  return x->tv_sec < y->tv_sec;
}

int main(int argc, char *argv[])
{
    int myid, iterations;
    MPI_Request request;

    MPI_Init(&argc,&argv);

    if (argc > 1)
        iterations = atoi(argv[1]);
    else
        iterations = 1;

    iterations++;
    MPI_Comm_rank(MPI_COMM_WORLD, &myid);

    MPI_Barrier(MPI_COMM_WORLD);

    int buf;

    if (myid == 1) {
        while (iterations--) {
            MPI_Recv(&buf, 1, MPI_INT, 0, 1, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
            MPI_Send(&buf, 1, MPI_INT, 0, 1, MPI_COMM_WORLD);
        }
    }
    else if (myid == 0) {
        struct timespec start_t, stop_t, diff_t;

        while (iterations--) {
            clock_gettime(CLOCK_MONOTONIC, &start_t);
//            double start_t = MPI_Wtime();

            MPI_Send(&buf, 1, MPI_INT, 1, 1, MPI_COMM_WORLD);
            MPI_Recv(&buf, 1, MPI_INT, 1, 1, MPI_COMM_WORLD, MPI_STATUS_IGNORE);

            clock_gettime(CLOCK_MONOTONIC, &stop_t);

//            double diff = difftime(start_t, stop_t) * 1000000;
            timespec_subtract(&diff_t, &stop_t, &start_t);
//            int diff = (MPI_Wtime() - start_t) * 1000000;
            double usec = diff_t.tv_sec * 1000000 + diff_t.tv_nsec / 1000.0;
            printf("%f\n", usec);
        }
    }

    MPI_Finalize();
    return 0;
}
