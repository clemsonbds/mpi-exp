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

    MPI_Comm_rank(MPI_COMM_WORLD, &myid);

    MPI_Barrier(MPI_COMM_WORLD);

    double send_t, recv_t;

    if (myid == 1) {
        while (iterations--) {
            send_t = MPI_Wtime();

            MPI_Isend(&send_t, 1, MPI_DOUBLE, 0, 1, MPI_COMM_WORLD, &request);
/*
            struct timespec req, rem;
            req.tv_sec = 0;
            req.tv_nsec = 1000000;
            while (nanosleep(&req, &rem) == -1) {
                req.tv_sec = rem.tv_sec;
                req.tv_nsec = rem.tv_nsec;
            }
*/
            static volatile int i;
            for (i = 0; i < 500000; i++);
//            usleep(1000);

            MPI_Wait(&request, MPI_STATUS_IGNORE);
        }
    }
    else if (myid == 0) {
        while (iterations--) {
            MPI_Recv(&send_t, 1, MPI_DOUBLE, 1, 1, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
            recv_t = MPI_Wtime();

            printf("%f\t%f\n", send_t, recv_t);
        }
    }

    MPI_Finalize();
    return 0;
}
