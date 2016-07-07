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
        iterations = 1;

    iterations++;
    MPI_Comm_rank(MPI_COMM_WORLD, &myid);

    MPI_Barrier(MPI_COMM_WORLD);

    double last_t = 0.0;

    if (myid == 1) {
        int diff = 0;

        while (iterations--) {
            double t = MPI_Wtime();

            if (last_t != 0)
                diff = (t - last_t) * 1000000;

            last_t = t;

            MPI_Isend(&diff, 1, MPI_INT, 0, 1, MPI_COMM_WORLD, &request);
            int i;
            for (i = 0; i < 200000; i++);
//            usleep(1000);
            MPI_Wait(&request, MPI_STATUS_IGNORE);
        }
    }
    else if (myid == 0) {
	int send_diff;

        while (iterations--) {
            MPI_Recv(&send_diff, 1, MPI_INT, 1, 1, MPI_COMM_WORLD, MPI_STATUS_IGNORE);

            double t = MPI_Wtime();

            if (last_t != 0) {
                int recv_diff = (t - last_t) * 1000000;
                printf("%d\t%d\n", send_diff, recv_diff);
            }

            last_t = t;
        }
    }

    MPI_Finalize();
    return 0;
}
