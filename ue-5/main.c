
 #include <mpi.h>
 #include <stdio.h>

 #define false 0
 #define true  1

 #define SIZE  24
 #define DIM   3
 #define DIM_0 2
 #define DIM_1 3
 #define DIM_2 4

 int main (int argc, char** argv)
 {
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

    MPI_Comm cartcomm;

    MPI_Init(&argc, &argv);
    MPI_Rank(&my_rank);
    MPI_Comm_size(MPI_COMM_WORLD, num_tasks);

    if (num_tasks != SIZE) {
        printf("We need %d proccesses, %d given. Exiting.\n", SIZE, num_tasks);
    } else {

        gethostname(hostname, 79);

        printf("%-15.12s: MPI_COMM_WORLD rank %d\n", hostname, rank);

        MPI_Cart_create(MPI_COMM_WORLD, DIM, dims, periods, reorder, &cartcomm);

        MPI_Cart_coords(cartcomm, my_rank, DIM, coords);

    }

    MPI_Finalize();

    return 0;
 }
