#include <mpi.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>

/**
 * Implementieren Sie die Funktion gather ring aus der Vorlesung!
 * Verwenden Sie als Datenstruktur ein Feld vom Typ char der Laenge n.
 * Nutzen Sie fuer ihre Tests mehr als 2 Prozessoren.
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
int main(int argc, char **argv) {
    MPI_Init(&argc, &argv);

    //  Rang, Anzahl Prozessoren
    int rank, comm_size;

    char hostname[256];
    gethostname(hostname, 256);

    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &comm_size);

    char *hostnames;
    hostnames = (char *) malloc(256 * comm_size);

    // MPI_Gather(hostname, 256, MPI_CHAR, hostnames, 256, MPI_CHAR, 0, MPI_COMM_WORLD);
    gather_ring1(hostnames, 256, hostnames);

    if (rank == 0) {
        int i;
        for (i = 0; i < comm_size; i++) {
            printf("Process %d: host %s\n", i, &hostnames[i * 256]);
        }
    }

    MPI_Finalize();

    return 0;
}

void gather_ring1(char x[], int blocksize, char y[]) {
    int i, p, my_rank, succ, pred,
            send_offset, recv_offset;

    MPI_Status status;

    MPI_Comm_size(MPI_COMM_WORLD, &p);
    MPI_Comm_rank(MPI_COMM_WORLD, &my_rank);

    for (i = 0; i < blocksize; i++) {
        y[i + my_rank * blocksize] = x[i];
    }

    succ = (my_rank + 1) % p;
    pred = (my_rank - 1 + p) % p;

    for (i = 0; i < p - 1; i++) {
        send_offset = ((my_rank - i + p) % p) * blocksize;
        recv_offset = ((my_rank - i - 1 + p) % p) * blocksize;

        if (my_rank % 2 == 0) {
            MPI_Send(y + send_offset, blocksize, MPI_CHAR, succ, 0, MPI_COMM_WORLD);
            MPI_Recv(y + recv_offset, blocksize, MPI_CHAR, pred, 0, MPI_COMM_WORLD, &status);
        } else {
            MPI_Recv(y + recv_offset, blocksize, MPI_CHAR, pred, 0, MPI_COMM_WORLD, &status);
            MPI_send(y + send_offset, blocksize, MPI_CHAR, succ, 0, MPI_COMM_WORLD);
        }
    }
}

void gather_ring2(float x[], int size, float y[]) {
    int i, p, my_rank, succ, pred,
            send_offset, recv_offset;

    MPI_Status status;
    MPI_Request send_req, recv_req;
    // ... mit MPI_Isend, MPI_Irecv
}

void gather_ring3(float x[], int size, float y[]) {
    int i, p, my_rank, succ, pred,
            send_offset, recv_offset;

    MPI_Status status;

    MPI_Comm_size(MPI_COMM_WORLD, &p);
    MPI_Comm_rank(MPI_COMM_WORLD, &my_rank);

    for (i = 0; i < size; i++) {
        y[i + my_rank * size] = x[i];
    }

    succ = (my_rank + 1) % p;
    pred = (my_rank - 1 + p) % p;

    send_offset = my_rank * size;
    recv_offset = ((my_rank - 1 + p) % p) * size;

    for (i = 0; i < p - 1; i++) {
        MPI_Sendrecv(y + send_offset ...);
        // ...
    }
}







