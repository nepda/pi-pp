#include "mpi.h"
#include <stdio.h>

unsigned int log2(unsigned int x) {
    unsigned int ans = 0;
    while (x >>= 1) ans++;
    return ans;
}

void hypercube_reduce(int input, int *output, MPI_Comm comm) {
    int comm_size, rank;
    MPI_Comm_rank(comm, &rank);
    MPI_Comm_size(comm, &comm_size);
    int d = log2(comm_size);

    int value = input;

    int i;
    for (i = d; i >= 0; i--) {
        int iup2 = 1 << i; // left shift // iup2 (i to the power of 2)
        // 11111 ^ 00001 = 11110
        int partner = rank ^iup2;

        if ((iup2 & partner) == 0) {
            int recvBuffer;
            MPI_Status status;
            MPI_Recv(&recvBuffer, 1, MPI_INT, partner, 0, comm, &status);
            value += recvBuffer;
        } else {
            MPI_Send(&value, 1, MPI_INT, partner, 0, comm);
            break;
        }
    }

    if (rank == 0) {
        *output = value;
    }
}

void tree_reduce(int input, int *output, MPI_Comm comm) {
    MPI_Status status;

    int rank;

    MPI_Comm_rank(comm, &rank);

    int recv_buffer;
    int left = rank * 2 + 1;
    int right = rank * 2 + 2;
    int parent = (rank - 1) / 2;

    int value = input;

    int comm_size;

    MPI_Comm_size(comm, &comm_size);

    if (left < comm_size) {
        MPI_Recv(&recv_buffer, 1, MPI_INT, left, 0, comm, &status);
        value += recv_buffer;
    }

    if (right < comm_size) {
        MPI_Recv(&recv_buffer, 1, MPI_INT, right, 0, comm, &status);
        value += recv_buffer;
    }

    if (rank != 0) {
        MPI_Send(&value, 1, MPI_INT, parent, 0, comm);
    } else {

        *output = value;
    }
}

int main(int argc, char **argv) {

    MPI_Init(&argc, &argv);

    return 0;
}