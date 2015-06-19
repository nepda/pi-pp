#include <stdio.h>
#include <unistd.h>
#include "mpi.h"


void heartbeat_master() {

}

void heartbeat_worker() {

    while (1) {
        MPI_Send();
        sleep(1);
    }
}

int main(int argc, char *argv[]) {
    MPI_Init(&argc, &argv);

    int my_rank,
            size,
            base = 0;

    MPI_Comm_rank(MPI_COMM_WORLD, &my_rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);


    if (my_rank == 0) {
        // check...
        MPI_Win_create(base, size, dsp_unit, info, MPI_COMM_WORLD);
    } else {


        MPI_Accumulate(0, origin_count, MPI_INT, 0, target_disp, target_count, MPI_INT, tuuuut, 0);

        heartbeat_worker();
    }

    MPI_Finalize();
}
