#include "mpi.h"
#include <stdio.h>
int main(int argc, char *argv[])
{
    int myid;
//, numprocs, left, right;
//    int iter;
//    int buffer[10], buffer2[10];
    MPI_Request request;
//    MPI_Status status;

    MPI_Init(&argc,&argv);

    int iterations = atoi(argv[1]);

    MPI_Comm_rank(MPI_COMM_WORLD, &myid);

    if (my_id == 1) {
        while (iterations--) {
            int buf = iterations;
            MPI_Isend(&buf, 1, MPI_INT, 0, 1, MPI_COMM_WORLD, &request);
            usleep(1000);
        }
    }
    else if (my_id == 0) {
        double t, last_t;
        last_t = MPI_Wtime();

        while (iterations) {
            MPI_Recv(&iterations, 1, MPI_INT, 0, 1, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
            int diff = (MPI_Wtime() - last_t) * 1000000;
            printf("%d", diff);
        }
    }

//    MPI_Irecv(buffer, 10, MPI_INT, left, 123, MPI_COMM_WORLD, &request);
//    MPI_Isend(buffer2, 10, MPI_INT, right, 123, MPI_COMM_WORLD, &request2);
//    MPI_Wait(&request, &status);
//    MPI_Wait(&request2, &status);

    MPI_Finalize();
    return 0;
}
