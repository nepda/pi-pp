#include <mpi.h>
#include <stdio.h>

#define false 0
#define true  1

#define SIZE  24
#define DIM   3
#define DIM_0 2
#define DIM_1 3
#define DIM_2 4

int main(int argc, char **argv) {
    int num_tasks;

    char hostname[80];

    int dims[DIM];
    dims[0] = DIM_0;
    dims[1] = DIM_1;
    dims[2] = DIM_2;

    int periods[DIM] = {false, false, false};
    int reorder = true;
    int my_rank;

    int coords[DIM];

    MPI_Comm cart, y_comm;

    MPI_Init(&argc, &argv);
    MPI_Comm_rank(MPI_COMM_WORLD, &my_rank);
    MPI_Comm_size(MPI_COMM_WORLD, &num_tasks);

    if (num_tasks != SIZE) {
        if (my_rank == 0) {
            printf("We need %d proccesses, %d given. Exiting.\n", SIZE, num_tasks);
        }
    } else {

        gethostname(hostname, 79);

        MPI_Cart_create(MPI_COMM_WORLD, DIM, dims, periods, reorder, &cart);

        MPI_Comm_rank(cart, &my_rank);
        MPI_Cart_coords(cart, my_rank, DIM, coords);


        printf("%-15.12s: MPI_COMM_WORLD rank %2d: (%d, %d, %d)\n", hostname, my_rank, coords[0], coords[1], coords[2]);

        int i;
        int neighbor2, neighbor1;
        for (i = 0; i <= DIM; i++) {

            MPI_Cart_shift(cart, i, 1, &neighbor1, &neighbor2);
            if (neighbor1 > 0) {
                printf("%-15.12s: I'm %d, left neighbor in %d is %d\n", hostname, my_rank, i, neighbor1);
            }
            if (neighbor2 > 0) {
                printf("%-15.12s: I'm %d, right neighbor in %d is %d\n", hostname, my_rank, i, neighbor2);
            }
        }

        int keep_dims[1];
        keep_dims[0] = 1;
        MPI_Cart_sub(cart, keep_dims, &y_comm);
        printf("%-15.12s:  # # # %d: my y rank is %d\n", hostname, my_rank, coords[1]);
    }

    MPI_Finalize();

    return 0;
}
