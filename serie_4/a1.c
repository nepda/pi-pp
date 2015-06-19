#include <mpi.h>
#include <unistd.h>
#include <stdio.h>

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
 * * * - mpicc -o a1 a1.c
 * Auf dem Knoten:
 * - mpirun -np 2 ./a1
 */
int main(int argc, char** argv)
{
        MPI_Init(&argc, &argv);

        //  Rang, Anzahl Prozessoren
        int rank, comm_size;

        MPI_Comm_rank(MPI_COMM_WORLD, &rank);
        MPI_Comm_size(MPI_COMM_WORLD, &comm_size);

        char hostname[256];
        gethostname(hostname, 256);

        printf("Rang: %d, Anzahl: %d, Hostname: %s\n", rank, comm_size, hostname);

        MPI_Finalize();

        return 0;
}
