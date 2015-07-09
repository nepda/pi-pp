#include "mpi.h"


/**
 * @brief Initialize the MPI library
 *
 * @param argc The argc argument from the main function
 * @param argv The argv argument from the main function
 */
int MPI_Init(int *argc, char ***argv);

/**
 * @brief Obtaining the total number of processes of the program
 *
 * @param comm The communicator of the process group
 * @param size The output variable for the total number of processes
 */
int MPI_Comm_size(MPI_Comm comm, int *size);

/**
 * Obtaining the local process number
 *
 * @param comm The communicator (e.g. MPI_COMM_WORLD)
 * @param rank The variable for my rank
 */
int MPI_Comm_rank(MPI_Comm comm, int *rank);

/**
 * @brief Sending Data using MPI Point-to-Point Communication
 *
 * This function is blocking.
 *
 * @param buf Send buffer containing the elements to be sent successively
 * @param count Number of elements to be sent
 * @param datatype Data type common to all elements to be sent
 * @param dest Rank of the target process that should receive the data
 * @param tag Additional message tag (between 0 and 32767) to distinguish different messages of the same sender
 * @param comm Communicator of the underlying processor group
 */
int MPI_Send(const void *buf, int count, MPI_Datatype datatype, int dest, int tag, MPI_Comm comm);

/**
 * @brief Receiving Data with MPI Point-to-Point Communication
 *
 * MPI_Send() and MPI_Recv() are *blocking* and *asynchronous* operations!
 *
 * @param buf Buffer of adequate size to receive the message
 * @param count Upper limit of the number of elements to accept
 * @param datatype Data type of the elements to be received
 * @param source Rank of the process from which to receive a message
 * @param tag Message tag of the message to be received
 * @param comm Communicator of the underlying processor group
 * @param status Data structure to be filled with information on the message received
 */
int MPI_Recv(void *buf, int count, MPI_Datatype datatype, int source,
             int tag, MPI_Comm comm, MPI_Status *status);

/**
 * @brief The number of data elements transmitted to the receiver can be obtained from the data structure status
 *
 * @param status Pointer to the data structure returned by the corresponding call to MPI_Recv()
 * @param datatype Data type of the elements
 * @param count Address of a variable wich the number of elements received are returned
 */
int MPI_Get_count(const MPI_Status *status, MPI_Datatype datatype, int *count);


/**
 * @brief Data Exchange with MPI Sendrecv()
 *
 * Advantage of MPI Sendrecv(): The runtime system guarantees deadlock freedom.
 *
 * Prerequisit: sendbuf and recvbuf must be disjoint, non-overlapping memory locations.
 *
 * Messages of different lengths and different data types may be exchanged.
 *
 * If send and receive buffers are identical, the MPI operation MPI_Sendrecv_replace() may be used.

 * @param sendbuf Send buffer in which the data elements to be sent are stored
 * @param sendcount Number of data elements to be sent
 * @param sendtype Data type of the elements to be sent
 * @param dest Rank of the target process to which the data elements are sent
 * @param sendtag Tag for the message to be send
 * @param recvbuf Receive buffer for the message to be received
 * @param recvcount Maximum number of data elements to be received
 * @param recvtype Data type of the data elements to be received
 * @param source Rank of the process from which the message is expected
 * @param recvtag Tag of the message to be received
 * @param comm Communicator used for the communication
 * @param status Data structure to store information on the message received
 */
int MPI_Sendrecv(const void *sendbuf, int sendcount, MPI_Datatype sendtype,
                 int dest, int sendtag, void *recvbuf, int recvcount,
                 MPI_Datatype recvtype, int source, int recvtag,
                 MPI_Comm comm, MPI_Status *status);


/**
 * @brief Like MPI_Sendrecv
 *
 * @param buf Buffer that is used as both send and receive buffer
 * @see MPI_Sendrecv
 */
int MPI_Sendrecv_replace(void *buf, int count, MPI_Datatype datatype,
                         int dest, int sendtag, int source, int recvtag,
                         MPI_Comm comm, MPI_Status *status);


/**
 * @brief Non-blocking send operation
 *
 * The same as MPI_Send() but non-blocking.
 *
 * @param buf Send buffer containing the elements to be sent successively
 * @param count Number of elements to be sent
 * @param datatype Data type common to all elements to be sent
 * @param dest Rank of the target process that should receive the data
 * @param tag Additional message tag (between 0 and 32767) to distinguish different messages of the same sender
 * @param comm Communicator of the underlying processor group
 *
 * @see MPI_Send
 */
int MPI_Isend(const void *buf, int count, MPI_Datatype datatype, int dest,
              int tag, MPI_Comm comm, MPI_Request *request);

/**
 * @brief Non-blocking receive operation
 *
 *
 * @param buf Buffer of adequate size to receive the message
 * @param count Upper limit of the number of elements to accept
 * @param datatype Data type of the elements to be received
 * @param source Rank of the process from which to receive a message
 * @param tag Message tag of the message to be received
 * @param comm Communicator of the underlying processor group
 * @param request Communication request
 *
 * @see MPI_Recv()
 */
int MPI_Irecv(void *buf, int count, MPI_Datatype datatype, int source,
              int tag, MPI_Comm comm, MPI_Request *request);


/**
 * @brief Querying the status of a non-blocking communication operation
 *
 * If MPI Test() is called for a receive operation that is completed the parameter status contains
 *
 * @param request The request
 * @param flag 1 if the send or receive communication operation specified by request has been completed, 0 denotes that the operation is still in progress.
 * @param status
 */
int MPI_Test(MPI_Request *request, int *flag, MPI_Status *status);


/**
 * @brief Waiting for the completion of a communication operation
 *
 * This MPI operation blocks the calling process until the send or receive operation specified by request is completed.
 *
 * @param request
 * @param status
 */
int MPI_Wait(MPI_Request *request, MPI_Status *status);


/**
 * @brief Blocking send operation in buffered mode
 */
int MPI_Bsend(const void *buf, int count, MPI_Datatype datatype,
              int dest, int tag, MPI_Comm comm);

/**
 * @brief Non-blocking send operation in buffered mode
 */
int MPI_Ibsend(const void *buf, int count, MPI_Datatype datatype, int dest,
               int tag, MPI_Comm comm, MPI_Request *request);


/**
 * @brief Provision of a buffer
 *
 * The buffer space to be used by the runtime system must be provided by the programmer
 *
 * @param size is the size of the buffer buffer in bytes.
 */
int MPI_Buffer_attach(void *buffer, int size);


/**
 * @brief Detaching a buffer previously provided
 */
int MPI_Buffer_detach(void *buffer, int *size);


/**
 * @brief Broadcast Operation
 *
 * The root process root sends the same data block to all other processes of the group.
 *
 * All global communication operations are blocking in MPI.
 */
int MPI_Bcast(void *buffer, int count, MPI_Datatype datatype,
              int root, MPI_Comm comm);


/**
 * @brief Accumulation Operation
 *
 * MPI provides the following predefined reduction operations:
 * * arithmetical: MPI_{MAX, MIN, SUM, PROD, MINLOC, MAXLOC};
 * * logical: MPI_{LAND, BAND, LOR, BOR, LXOR, BXOR};
 * * MPI_{MAXLOC, MINLOC} additionally return the index attached by the process with the maximum or minimum value respectively
 */
int MPI_Reduce(const void *sendbuf, void *recvbuf, int count,
               MPI_Datatype datatype, MPI_Op op, int root, MPI_Comm comm);


/**
 * @brief User defined accumulation operation
 *
 * The call of MPI Op create() returns a reduction operation op which can then be used as parameter of MPI Reduce().
 *
 * @param function The argument function specifies a user-defined function which must define the following four parameters: void *in, void *out, int *len, MPI Datatype *type.
 * @param commute The parameter commute specifies whether the function is commutative (commute = 1) or not (commute = 0).
 */
int MPI_Op_create(MPI_User_function *function, int commute, MPI_Op *op);


/**
 * @brief Each of the participating n processes provides a block of data that is collected at the root process.
 *
 * @param sendbuf Send buffer that is provided by each participating process
 * @param sendcount Number of data elements with data type `sendtype`
 * @param recvbuf Receive buffer provided by the root process `root` that is large enough to hold all data elements sent.
 */
int MPI_Gather(const void *sendbuf, int sendcount, MPI_Datatype sendtype,
               void *recvbuf, int recvcount, MPI_Datatype recvtype,
               int root, MPI_Comm comm);

/**
 * @brief More general vector-based MPI Gatherv operation
 *
 * Each process can provide a different number of elements.
 *
 * Overlaps in the receive buffer must not occur;
 *  --> displs_`root` [i + 1] >= displs_`root` [i] + sendcount_`i` with recvcounts_`root`[i] = sendcount_`i`
 *
 * @param sendcount Number of data elements to be sent
 * @param recvcounts Array, where recvcounts[i] denotes the number of elements proviced by process i
 * @param displs Array that specifies the positions of the data blocks in `recvbuf`
 */
int MPI_Gatherv(const void *sendbuf, int sendcount, MPI_Datatype sendtype,
                void *recvbuf, const int recvcounts[], const int displs[],
                MPI_Datatype recvtype, int root, MPI_Comm comm);


/**
 * @brief Scatter: The root process provides a data block (with the same size but possibly different elements) for each participating process.
 *
 * @param sendbuf Is the send buffer provided by the root process `root` which contains a data block with `sendcount` elements of data type `sendtype` for each process of communicator `comm`.
 */
int MPI_Scatter(const void *sendbuf, int sendcount, MPI_Datatype sendtype,
                void *recvbuf, int recvcount, MPI_Datatype recvtype,
                int root, MPI_Comm comm);

/**
 * @brief Multi-broadcast operation: Each process sends the same block of data to each other process
 *
 * Each process performs a single-broadcast operation.
 *
 * Each process provides a receive buffer recvbuf in which all received data blocks are collected
 * in rank order of the sending processes.
 *
 * A multi-broadcast does not have a distinguished root process.
 *
 * Example: each process contributes a send buffer with 100 integer values which are made
 * available by a multi-broadcast operation to all processes:
 *
 * int sbuf[100], gsize, *rbuf;
 * MPI Comm size (comm, &gsize);
 * rbuf = (int*) malloc (gsize*100*sizeof(int));
 * MPI Allgather (sbuf, 100, MPI INT, rbuf, 100, MPI INT, comm);
 *
 * @param sendbuf `send buffer` proviced by each of the participating processes.
 */
int MPI_Allgather(const void *sendbuf, int sendcount, MPI_Datatype sendtype,
                  void *recvbuf, int recvcount,
                  MPI_Datatype recvtype, MPI_Comm comm);

/**
 * @brief Syntax of the vector-based MPI operation MPI_Allgatherv()
 *
 * Each process provides a receive buffer recvbuf in which all received data blocks are collected in rank order of the sending processes.
 *
 * A multi-broadcast does not have a distinguished root process.
 *
 */
int MPI_Allgatherv(const void *sendbuf, int sendcount, MPI_Datatype sendtype,
                   void *recvbuf, const int recvcounts[],
                   const int displs[], MPI_Datatype recvtype, MPI_Comm comm);


/**
 * @brief Multi-accumulation Operation
 *
 * Each process provides a data block of the same size.
 *
 * The data blocks are accumulated with a reduction operation -> multi-accumulation equals a
 * single-accumulation with a subsequent broadcast.
 *
 * @param sendbuf is the **local buffer** in which each process provices its local data
 * @param recvbuf is the local buffer of each process in which the accumulated result is **collected**.
 */
int MPI_Allreduce(const void *sendbuf, void *recvbuf, int count,
                  MPI_Datatype datatype, MPI_Op op, MPI_Comm comm);

/**
 * @brief Total Exchange
 *
 * Each process provides a different block of data for each other process
 * Each process collects the data blocks provided for this particular process.
 *
 * The blocks are arranged in rank order of the target processes.
 *
 * @param sendbuf is the **send buffer** in which each process provides for each process a block of
 * data with **sendcount** elements of type **sendtype**
 *
 */
int MPI_Alltoall(const void *sendbuf, int sendcount, MPI_Datatype sendtype,
                 void *recvbuf, int recvcount,
                 MPI_Datatype recvtype, MPI_Comm comm);

/**
 * @brief Syntax of the more general vector-based version for data blocks of different sizes
 *
 */
int MPI_Alltoallv(const void *sendbuf, const int sendcounts[], const int sdispls[],
                  MPI_Datatype sendtype, void *recvbuf, const int recvcounts[],
                  const int rdispls[], MPI_Datatype recvtype, MPI_Comm comm);


/**
 * @brief The corresponding process group to a given communicator comm can be obtained by calling
 *
 * `MPI_GROUP_EMPTY` denotes the empty process group.
 */
int MPI_Comm_group(MPI_Comm comm, MPI_Group *group);

/**
 * @brief Union of two existing groups group1 and group2
 *
 * The processes in group1 keep their ranks from group1 and the processes in group2 which are
 * not in group1 get subsequent ranks in consecutive order.
 */
int MPI_Group_union(MPI_Group group1, MPI_Group group2,
                    MPI_Group *newgroup);


/**
 * @brief The intersection of two groups is obtained by calling this function
 *
 * Where the process order from `group1` is kept for new group. The processes in `new_group` get
 * successive ranks starting from 0.
 */
int MPI_Group_intersection(MPI_Group group1, MPI_Group group2,
                           MPI_Group *newgroup);


/**
 * @brief The set difference of two groups
 *
 * Where the process order from `group1` is kept as well.
 *
 */
int MPI_Group_difference(MPI_Group group1, MPI_Group group2,
                         MPI_Group *newgroup);

/**
 * @brief Construction of a subset of an existing group
 *
 * The call creates a new group new group with p processes which have ranks from 0 to p-1.
 *
 * Process i is the process which has rank `ranks[i]` in group group.
 *
 * The group group must contain at least p processes and the values `ranks[i]` must be valid
 * process ranks in group which are different from each other.
 *
 * @param ranks is an integer array with p entries.
 *
 */
int MPI_Group_incl(MPI_Group group, int n, const int ranks[],
                   MPI_Group *newgroup);

/**
 * @brief Deletion of processes from a group
 *
 * The new group `new_group` is generated by deleting the processes with ranks
 * `ranks[0]`, ..., `ranks[p-1]` from `group`.
 */
int MPI_Group_excl(MPI_Group group, int n, const int ranks[],
                   MPI_Group *newgroup);

/**
 * @brief The size of a process group `group`
 */
int MPI_Group_size(MPI_Group group, int *size);

/**
 * @brief The rank of the calling process in a group
 */
int MPI_Group_rank(MPI_Group group, int *rank);


/**
 * @brief To check whether two process groups describe the same process group
 */
int MPI_Group_compare(MPI_Group group1, MPI_Group group2, int *result);


int main(int argc, char **argv) {

    MPI_Init();
    MPI_Comm_size();
    MPI_Comm_rank();
    MPI_Send();
    MPI_Recv();
    MPI_Get_count();
    MPI_Sendrecv();
    MPI_Sendrecv_replace();
    MPI_Isend();
    MPI_Irecv();
    MPI_Test();
    MPI_Wait();
    MPI_Bsend();
    MPI_Ibsend();
    MPI_Buffer_attach();
    MPI_Buffer_detach();
    MPI_Bcast();
    MPI_Reduce();
    MPI_Op_create();
    MPI_Gather();
    MPI_Gatherv();
    MPI_Scatter();
    MPI_Allgather();
    MPI_Allgatherv();
    MPI_Allreduce();
    MPI_Alltoall();
    MPI_Alltoallv();
    MPI_Comm_group();
    MPI_Group_union();
    MPI_Group_intersection();
    MPI_Group_difference();
    MPI_Group_incl();
    MPI_Group_excl();
    MPI_Group_size();
    MPI_Group_rank();
    MPI_Group_compare();
}