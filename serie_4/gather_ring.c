#include <mpi.h>

#define MAX_SIZE 1000000
#define MAX_MES  100

void Gather_ring3(float x[], int size, float y[]) {
    int i, p, my_rank, succ, pred;
    int send_offset, recv_offset;
    MPI_Status status;

    MPI_Comm_size(MPI_COMM_WORLD, &p);
    MPI_Comm_rank(MPI_COMM_WORLD, &my_rank);
    for (i = 0; i < size; i++) y[i + my_rank * size] = x[i];
    succ = (my_rank + 1) % p;
    pred = (my_rank - 1 + p) % p;
    send_offset = my_rank * size;
    recv_offset = ((my_rank - 1 + p) % p) * size;
    for (i = 0; i < p - 1; i++) {
        MPI_Sendrecv(y + send_offset, size, MPI_FLOAT, succ, 0,
                     y + recv_offset, size, MPI_FLOAT, pred, 0,
                     MPI_COMM_WORLD, &status);
    }
}


void Gather_ring2(float x[], int size, float y[]) {
    int i, p, my_rank, succ, pred;
    int send_offset, recv_offset;
    MPI_Status status;
    MPI_Request send_requ, recv_requ;
    MPI_Comm_size(MPI_COMM_WORLD, &p);
    MPI_Comm_rank(MPI_COMM_WORLD, &my_rank);
    for (i = 0; i < size; i++) y[i + my_rank * size] = x[i];
    succ = (my_rank + 1) % p;
    pred = (my_rank - 1 + p) % p;
    send_offset = my_rank * size;
    recv_offset = ((my_rank - 1 + p) % p) * size;
    for (i = 0; i < p - 1; i++) {
        MPI_Isend(y + send_offset, size, MPI_FLOAT, succ, 0,
                  MPI_COMM_WORLD, &send_requ);
        MPI_Irecv(y + recv_offset, size, MPI_FLOAT, pred, 0,
                  MPI_COMM_WORLD, &recv_requ);
        send_offset = ((my_rank - i - 1 + p) % p) * size;
        recv_offset = ((my_rank - i - 2 + p) % p) * size;
        MPI_Wait(&send_requ, &status);
        MPI_Wait(&recv_requ, &status);
    }
}


void Gather_ring1(float x[], int blocksize, float y[]) {
    int i, p, my_rank, succ, pred;
    int send_offset, recv_offset;
    MPI_Status status;
    MPI_Comm_size(MPI_COMM_WORLD, &p);
    MPI_Comm_rank(MPI_COMM_WORLD, &my_rank);
    for (i = 0; i < blocksize; i++)
        y[i + my_rank * blocksize] = x[i];
    succ = (my_rank + 1) % p;
    pred = (my_rank - 1 + p) % p;
    for (i = 0; i < p - 1; i++) {
        send_offset = ((my_rank - i + p) % p) * blocksize;
        recv_offset = ((my_rank - i - 1 + p) % p) * blocksize;
        if (my_rank == 0) {
            MPI_Send(y + send_offset, blocksize, MPI_FLOAT,
                     succ, 0, MPI_COMM_WORLD);
            MPI_Recv(y + recv_offset, blocksize, MPI_FLOAT,
                     pred, 0, MPI_COMM_WORLD, &status);
        } else {
            MPI_Recv(y + recv_offset, blocksize, MPI_FLOAT,
                     pred, 0, MPI_COMM_WORLD, &status);
            MPI_Send(y + send_offset, blocksize, MPI_FLOAT,
                     succ, 0, MPI_COMM_WORLD);
        }
    }
}


void Gather_ring(float x[], int blocksize, float y[]) {
    int i, p, my_rank, succ, pred;
    int send_offset, recv_offset;
    MPI_Status status;
    MPI_Comm_size(MPI_COMM_WORLD, &p);
    MPI_Comm_rank(MPI_COMM_WORLD, &my_rank);
    for (i = 0; i < blocksize; i++)
        y[i + my_rank * blocksize] = x[i];
    succ = (my_rank + 1) % p;
    pred = (my_rank - 1 + p) % p;
    for (i = 0; i < p - 1; i++) {
        send_offset = ((my_rank - i + p) % p) * blocksize;
        recv_offset = ((my_rank - i - 1 + p) % p) * blocksize;
        MPI_Send(y + send_offset, blocksize, MPI_FLOAT, succ, 0,
                 MPI_COMM_WORLD);
        MPI_Recv(y + recv_offset, blocksize, MPI_FLOAT, pred, 0,
                 MPI_COMM_WORLD, &status);
    }
}


int main(int argc, char **argv) {
    int comm_size;
    int rank;
    int i, j;
    int mode = 0;
    float *x, *y;
    double mtime;

    MPI_Init(&argc, &argv);

    MPI_Comm_size(MPI_COMM_WORLD, &comm_size);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);

    x = (float *) calloc(MAX_SIZE, sizeof(float));
    y = (float *) calloc(MAX_SIZE * comm_size, sizeof(float));

    mode = strtol(argv[1], NULL, 10);

    for (i = 1; i < MAX_SIZE; i *= 2) {

        MPI_Barrier(MPI_COMM_WORLD);
        mtime = -MPI_Wtime();
        for (j = 0; j < MAX_MES; j++) {
            switch (mode) {
                case 0:
                    Gather_ring(x, i, y);
                    break;
                case 1:
                    Gather_ring1(x, i, y);
                    break;
                case 2:
                    Gather_ring2(x, i, y);
                    break;
                case 3:
                    Gather_ring3(x, i, y);
                    break;
            }
        }
        mtime += MPI_Wtime();
        if (rank == 0)
            printf("%d %f\n", i, mtime / MAX_MES);
    }

    MPI_Finalize();
    return 0;
}
