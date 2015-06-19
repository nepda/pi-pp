/*
 * Einseitige Kommunikation:
 *      - normalerweise send-recv.
 *      - bei einseitiger komm. zu beginn wird gemeinsamer speicher (fenster) angelegt, alle knoten koennen zugreifen
 */


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

    MPI_Win_fence()

    for (z = 0; z < m; z++) {

    }


    MPI_Finalize();
    return 0;
}
