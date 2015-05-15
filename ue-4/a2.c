#include <mpi.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>

/**
 * Ein MPI Programm, welches fuer jeden Knoten den Rang und die Gesamtanzahl der
 * Prozessoren inkl. Hostnamen ausgibt
 *
 * Auf chiclogin1.informatik.tu-chemnitz.de:
 * * Das erste Mal:
 * * * - module initadd comp/gcc/422
 * * * - module initadd mpi/openmpi/gcc422
 * * * - qsub -I -l nodes=2:ppn=1,walltime=00:20:00 -q short
 * * Jedes mal:
 * * * - mpicc -o a2 a2.c
 * Auf dem Knoten:
 * - mpirun -np 2 ./a2
 */
int main(int argc, char** argv)
{
        MPI_Init(&argc, &argv);

        //  Rang, Anzahl Prozessoren
        int rank, comm_size;

        char hostname[256];
        gethostname(hostname, 256);

        MPI_Comm_rank(MPI_COMM_WORLD, &rank);
        MPI_Comm_size(MPI_COMM_WORLD, &comm_size);

        char* hostnames;
        if (rank == 0) {
            hostnames = (char*) malloc(256*comm_size);
        }

        MPI_Gather(hostname, 256, MPI_CHAR, hostnames, 256, MPI_CHAR, 0, MPI_COMM_WORLD);

        if (rank == 0) {
            int i;
            for (i = 0; i < comm_size; i++) {
                printf("Process %d: host %s\n", i, &hostnames[i*256]);
            }
        }

        MPI_Finalize();

        return 0;
}
