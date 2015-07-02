#include <mpi.h>
#include <stdio.h>

/*

P         1      2     3     4
Time      14s    7s    5s    4s
Speedup   1      2     2,8   3,5
Effizienz 1      1     0,93  0,88


Schleife ist unabhänging von anderen Interationen, da Addition kommutativ ist.
*/

int main(int argc, char *argv[]) {
    const int intervals = 1000000000;
    double local_pi = 0.0;

    int comm_size, rank;

    MPI_Init(&argc, &argv);
    MPI_Comm_size(MPI_COMM_WORLD, &comm_size);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);

    double delta = 1.0 / (double) intervals;


    int j;
    for (j = rank; j <= intervals; j += comm_size) {
        double x = ((double) j - 0.5) * delta;
        local_pi += 4.0 / (1.0 + (x * x));
    }

    double final_pi;
    MPI_Reduce(&local_pi, &final_pi, 1, MPI_DOUBLE, MPI_SUM, 0, MPI_COMM_WORLD);

    if (rank == 0) {
        printf("Pi = %.10f\n", final_pi * delta);
    }

    MPI_Finalize();
    return 0;
}
