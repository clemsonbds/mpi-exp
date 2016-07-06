#include "mpi.h"
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main(int argc, char *argv[])
{
    int myid, iterations;
    MPI_Request request;

    MPI_Init(&argc,&argv);

    if (argc > 1)
        iterations = atoi(argv[1]);
    else
        iterations = 2;

    MPI_Comm_rank(MPI_COMM_WORLD, &myid);

    MPI_Barrier(MPI_COMM_WORLD);

    if (myid == 1) {
	int remaining = iterations+1;

        while (remaining--) {
            int buf = remaining;
            MPI_Isend(&buf, 1, MPI_INT, 0, 1, MPI_COMM_WORLD, &request);
            int i;
            for (i = 0; i < 200000; i++);
//            usleep(1000);
            MPI_Wait(&request, MPI_STATUS_IGNORE);
        }
    }
    else if (myid == 0) {
        double last_t = MPI_Wtime();
	int diff, remaining;

        do {
            MPI_Recv(&remaining, 1, MPI_INT, 1, 1, MPI_COMM_WORLD, MPI_STATUS_IGNORE);

            double t = MPI_Wtime();
            int diff = (t - last_t) * 1000000;
            last_t = t;

            if (remaining < iterations)
                printf("%d\n", diff);

        } while (remaining);
    }

    MPI_Finalize();
    return 0;
}
