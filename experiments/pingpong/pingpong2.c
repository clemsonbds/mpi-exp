#include "mpi.h"
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <time.h>

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
    int inner;

    if (myid == 1) {
        while (iterations--) {
            for (inner = 0; inner < 1000; inner++) {
                MPI_Recv(&buf, 1, MPI_INT, 0, 1, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
                MPI_Send(&buf, 1, MPI_INT, 0, 1, MPI_COMM_WORLD);
            }
        }
    }
    else if (myid == 0) {
        while (iterations--) {
            double start_t = MPI_Wtime();

            for (inner = 0; inner < 1000; inner++) {
                MPI_Send(&buf, 1, MPI_INT, 1, 1, MPI_COMM_WORLD);
                MPI_Recv(&buf, 1, MPI_INT, 1, 1, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
            }

            double diff = (MPI_Wtime() - start_t) * 1000;
            printf("%f\n", diff);
        }
    }

    MPI_Finalize();
    return 0;
}
