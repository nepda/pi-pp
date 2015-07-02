#include "mpi.h"
#include <stdio.h>
#include <unistd.h>

#define false 0
#define true  1

#define DIM   2

int main(int argc, char **argv) {

    char hostname[80];

    int m = 100, // siehe aufgabe
            world_size,
            my_rank,
            periods[DIM] = {true, true};

    MPI_Init(&argc, &argv);
    MPI_Comm_rank(MPI_COMM_WORLD, &my_rank);
    MPI_Comm_size(MPI_COMM_WORLD, &world_size);

    if (world_size != 16) {
        printf("16 Prozessoren waren gefordert!");
        return 1;
    }

    gethostname(hostname, 79);

    MPI_Comm comm2d;

    MPI_Cart_create(MPI_COMM_WORLD, 2, dims, periods, 1, &comm2d);
    int left, right, down, up;

    MPI_Cart_shift(comm2d, 0, 1, &left, &right);
    MPI_Cart_shift(comm2d, 1, 1, &down, &up);

    double w = (double) rank;
    double buff[4];

    int i;
    for (i = 0; i < m; i++) {
        MPI_Status status;
        MPI_Sendrecv(&w, 1, MPI_DOUBLE, up, 0, &buff[0], 1, MPI_DUBLE, down, 0, comm2d, &status);
        MPI_Sendrecv(&w, 1, MPI_DOUBLE, down, 0, &buff[1], 1, MPI_DUBLE, up, 0, comm2d, &status);
        MPI_Sendrecv(&w, 1, MPI_DOUBLE, left, 0, &buff[2], 1, MPI_DUBLE, right, 0, comm2d, &status);
        MPI_Sendrecv(&w, 1, MPI_DOUBLE, right, 0, &buff[3], 1, MPI_DUBLE, left, 0, comm2d, &status);


        w = 0.0;
        int k;
        for (k = 0; k < 4; k++) {
            w += buff[k];
        }
        w /= 4;
    }


    printf("I'm %d, (l: %d, r: %d, u: %d, d: %d)\n", my_rank, left, right, up, down);

    MPI_Finalize();

    return 0;
}
