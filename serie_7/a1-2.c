#include "mpi.h"
#include <stdio.h>


int main(int argc, char *argv[]) {

    int my_rank,
            size,
            z;

    MPI_Init(&argc, &argv);
    MPI_Comm_rank(MPI_COMM_WORLD, &my_rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);

    double w = my_rank;

    MPI_Win win;

    MPI_Win_create(&w, sizeof(double), sizeof(double), MPI_INFO_NULL, comm2d, &win);

    int left, right, down, up;

    MPI_Cart_shift(comm2d, 0, 1, &left, &right);
    MPI_Cart_shift(comm2d, 1, 1, &down, &up);

    for (z = 0; z < m; z++) {
        double buff = w;
        w = 0.0;
        MPI_Win_fence(0, win);
        MPI_Accumulate(&buff, 1, MPI_DOUBLE, left, 0, 1, MPI_DOUBLE, MPI_SUM, win);
        MPI_Accumulate(&buff, 1, MPI_DOUBLE, right, 0, 1, MPI_DOUBLE, MPI_SUM, win);
        MPI_Accumulate(&buff, 1, MPI_DOUBLE, up, 0, 1, MPI_DOUBLE, MPI_SUM, win);
        MPI_Accumulate(&buff, 1, MPI_DOUBLE, down, 0, 1, MPI_DOUBLE, MPI_SUM, win);
        MPI_Win_fence(0, win);

        w /= 4;
    }
    MPI_Win_free(&win);


    MPI_Finalize();
    return 0;
}
