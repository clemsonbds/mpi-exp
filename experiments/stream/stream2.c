#include "mpi.h"
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <time.h>

#include <stdint.h>

inline uint64_t rdtsc() {
    uint32_t lo, hi;
    __asm__ __volatile__ (
      "xorl %%eax, %%eax\n"
      "cpuid\n"
      "rdtsc\n"
      : "=a" (lo), "=d" (hi)
      :
      : "%ebx", "%ecx");
    return (uint64_t)hi << 32 | lo;
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

    MPI_Comm_rank(MPI_COMM_WORLD, &myid);

    MPI_Barrier(MPI_COMM_WORLD);

    unsigned long long send_t, recv_t;

    if (myid == 1) {
        while (iterations--) {
//            send_t = MPI_Wtime();
            send_t = rdtsc();
            MPI_Isend(&send_t, 1, MPI_UNSIGNED_LONG_LONG, 0, 1, MPI_COMM_WORLD, &request);
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
            MPI_Recv(&send_t, 1, MPI_UNSIGNED_LONG_LONG, 1, 1, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
//            recv_t = MPI_Wtime();
            recv_t = rdtsc();

            double send_usec = send_t/(double)2600;
            double recv_usec = recv_t/(double)2600;

//            printf("%lld\t%lld\n", send_t, recv_t);
            printf("%f\t%f\n", send_usec, recv_usec);
        }
    }

    MPI_Finalize();
    return 0;
}
