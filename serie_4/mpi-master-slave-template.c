// Pseudocode for master slave
#define TAG_RESULT 0

#define TAG_ASK_FOR_JOB 1
#define TAG_JOB_DATA 2
#define TAG_STOP 3

// for the master you have to provide code for managing individual tasks
// and for managing the slaves with their tasks they are working on
void master () {

    MPI_Status stat, stat2;

    while ( /* there are jobs unprocessed */ || /* there are slaves still working on jobs */ ) {

        // Wait for any incomming message
        MPI_Probe(MPI_ANY_SOURCE, MPI_ANY_TAG, MPI_COMM_WORLD, &stat);

        // Store rank of receiver into slave_rank
        int slave_rank = stat.MPI_SOURCE;

        // Decide according to the tag which type of message we have got
        if (stat.MPI_TAG == TAG_ASK_FOR_JOB) {

            MPI_Recv(buff, slave_rank, TAG_ASK_FOR_JOB, MPI_COMM_WORLD, &stat2);

            if (/* there are unprocessed jobs */) {

                // here we have unprocessed jobs , we send one job to the slave
                job = /* compute job */
                /* pack data of job into the buffer msg_buffer */
                MPI_Send(msg_buffer, /*...*/ , slave_rank, TAG_JOB_DATA, MPI_COMM_WORLD);
                /* mark slave with rank my_rank as working on a job */
            } else {

                // send stop msg to slave
                MPI_Send (/*...*/ , slave_rank , TAG_STOP , MPI_COMM_WORLD);
            }
        } else {

            // We got a result message
            MPI_Recv( result_data_buffer , /*...*/ , slave_rank , TAG_RESULT, MPI_COMM_WORLD , & stat2 );
            /* put data from result_data_buffer into a global result */
            /* mark slave with rank slave_rank as stopped */
        }
    }
}

void slave () {
    int stopped = 0;
    MPI_Status stat , stat2 ;
    do {

        // Here we send a message to the master asking for a job
        MPI_Send (/*...*/ , 0 , TAG_ASK_FOR_JOB , MPI_COMM_WORLD ) ;
        MPI_Probe (0 ,/*...*/ , MPI_COMM_WORLD , & stat ) ;
        if ( stat . MPI_TAG == TAG_JOB_DATA ) {

            // Retrieve job data from master into msg_buffer
            MPI_Recv ( msg_buffer , 0, TAG_JOB_DATA , MPI_COMM_WORLD , & stat2 ) ;
            /* work on job_data to get a result and store the result into
            result_buffer */

            // send result to master
            MPI_Send ( result_buffer ,/*...*/ , 0 , TAG_RESULT, MPI_COMM_WORLD);
        } else {
            // We got a stop message we have to retrieve it by using MPI_Recv
            // But we can ignore the data from the MPI_Recv call
            MPI_Recv (/*...*/ , 0, TAG_STOP , MPI_COMM_WORLD , &stat2);
            stopped = 1;
        }
    } while (stopped == 0);
}


int main(int argc, char **argv) {

    int rank;

    MPI_Init(&argc , & argv);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);

    if (rank == 0) {
        master () ;
    } else {
        slave () ;
    }

    MPI_Finalize () ;
}
