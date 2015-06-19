#include "mpi.h"
#include <stdio.h>

int comm_size;

void heartbeat_master() {
    long *timestamps;

    MPI_Alloc_mem(sizeof(long) * (comm_size - 1), MPI_INFO_NULL, &timestamps);

    for (int i = 0; i < comm_size - 1; i++) {
        timestamps[i] = 0;
    }

    MPI_Win win;
    MPI_Win_create(timestamps, sizeof(long) * (comm_size - 1), sizeof(long), MPI_INFO_NULL, MPI_COMM_WORLD, &win);
    int workers_alive;

    while (1) {
        sleep(1);
        time_t current_time;
        time(&current_time);

        for (int k = 0; k < 100; k++) {
            int flag;
            // ... schaut einfach nach, ob nachricht im eingangspuffer liegt
            // bringt uns eigentlich nichts, MPI intern
            MPI_Iprobe(MPI_ANY_SOURCE, MPI_ANY_TAG, MPI_COMM_WORLD, &flag, MPI_STATUS_IGNORE);
        }

        workers_alive = 0;

        // koennte klappen, dann ohne Iprobe
        // MPI_Win_lock(MPI_LOCK_EXCLUSIVE, 0, 0, win);

        for (int i = 0; i < comm_size - 1; i++) {
            if (current_time - timestamps[i] <= 3) {
                workers_alive++;
            } else {
                printf("Worker %d dead.\n", i + 1);
            }
        }
        if (workers_alive <= 0) {
            break;
        }

        // koennte klappen, dann ohne Iprobe
        // MPI_Win_unlock(0, win);
    }
    MPI_Win_free(&win);
}

void heartbeat_worker() {
    MPI_Win win;
    MPI_Win_create(NULL, 0, 1, MPI_INFO_NULL, MPI_COMM_WORLD, &win);

    while (1) {
        time_t current_time;
        time(&current_time);
        long t = current_time;

        MPI_Win_lock(MPI_LOCK_SHARE, 0, 0, &win);
        MPI_Put(&t, 1, MPI_LONG, 0, rank - 1, 1, MPI_LONG, win);
        MPI_Win_unlock(0, win);
        sleep(1);
    }
    MPI_Win_free(&win);
}

int main(int argc, char *argv[]) {

    int rank;
    MPI_Init(&argc, &argv);

    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &comm_size);

    if (rank == 0) {
        heartbeat_master();
    } else {
        heartbeat_worker();
    }

    MPI_Finalize();
    return 0;
}
