/**
 * @file summary.h
 *
 * @brief This file contains all MPI functions, mentioned in the Parallel Programming course script.
 *
 */

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
 * @brief Flexible number of data elements per receiver: vector-based version MPI_Scatterv
 */
int MPI_Scatterv(const void *sendbuf, const int sendcounts[], const int displs[],
                 MPI_Datatype sendtype, void *recvbuf, int recvcount,
                 MPI_Datatype recvtype, int root, MPI_Comm comm);

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
 *
 * `res`:
 * * `MPI_IDENT` The groups `group1` and `group2` contain the **same processes in the same order**
 * * `MPI_SIMILAR` Both groups contain the **same processes** but different order
 * * `MPI_UNEQUAL` The two groups contain **different processes**
 */
int MPI_Group_compare(MPI_Group group1, MPI_Group group2, int *result);

/**
 * @brief Generation of a new intra-communicator to a given group of processes
 *
 * **All** processes of comm must call MPI_Comm_create() with **the same group** as an argument.
 *
 * Result of the call: each calling process which is a member of group `group` obtains a pointer to
 * the new communicator `newcomm`.
 *
 * Processes not belonging to group get `MPI_COMM_NULL` as return value in `new_comm`.
 *
 * @param group Must specify a process gorup which is a subset of the process `group` associated with communicator `comm`.
 */
int MPI_Comm_create(MPI_Comm comm, MPI_Group group, MPI_Comm *newcomm);

/**
 * @brief Splitting of a communicator
 *
 * The process group associated with communicator `comm` is partitioned into a number of
 * disjoint subgroups that equals the number of different values specified in `color`.
 *
 * Each subgroup contains all processes that specify the same value for `color`.
 *
 * The rank order of the processes within a subgroup is defined by the argument `key`.
 *
 * If two processes specify the same value for `key` the order of the original group is used.
 *
 * If a process specifies `color = MPI_UNDEFINED`, it is not a member of any of the subgroups generated.
 *
 * Each participating process gets a pointer `new_comm` to the communicator of that subgroup which
 * the process belongs to.
 *
 */
int MPI_Comm_split(MPI_Comm comm, int color, int key, MPI_Comm *newcomm);


/**
 * @brief Definition of a virtual Cartesian grid structure of arbitrary dimension
 *
 * The array `periods` of size `ndims` specifies for each dimension whether the grid is periodic
 * (entry 1) or not (entry 0) in this dimension.
 *
 * @param old_comm Is the original communicator **without topology**
 * @param ndims Specifies the **number** of dimensions of hte grid to be created
 * @param dims Is an integer array with `ndims` elements where `dims[i]` denotes the **total number of processes in
 * dimension `i`**
 * @param reorder For `reorder = false`, the processes in `comm_cart` have the same rank as in `old_comm`
 */
int MPI_Cart_create(MPI_Comm old_comm, int ndims, const int dims[],
                    const int periods[], int reorder, MPI_Comm *comm_cart);

/**
 * @brief Select a balanced distribution of the processes for the different dimensions
 *
 * In the case `dims[i] = 0` is specified for the call, `dims[i]` contains the number of
 * processes in dimension `i` after the call.
 *
 * The function tries to assign the same number of processes to each dimension.
 *
 * The number of processes in a dimension `i` can be fixed by setting `dims[i]` to the desired
 * number of processes before the call. The MPI runtime system sets the entries of the other,
 * non-initialized entries of `dims` accordingly.
 *
 * @param nnodes Is the total number of processes in the grid
 * @param ndims Is the number of dimensions in the grid to be defined
 * @param dims Is an integer array of size `ndims`.
 */
int MPI_Dims_create(int nnodes, int ndims, int dims[]);

/**
 * @param Translation of Cartesian coordinates into group ranks
 *
 * The call translates the Cartesian coordinates of a process provided in the array `coords`
 * into the group rank according to the virtual grid associated with `comm`.
 */
int MPI_Cart_rank(MPI_Comm comm, const int coords[], int *rank);

/**
 * @brief Translation of group ranks into Cartesian coordinates
 *
 * The cartesian coordinates of the process are returned in the array `coords`.
 *
 * @param rank Contains the process number
 * @param dims Denotes the number of dimensions in the virtual grid defined for communicator `comm`.
 */
int MPI_Cart_coords(MPI_Comm comm, int rank, int maxdims, int coords[]);

/**
 * @brief Determining the neighboring processes in each dimension of the grid
 *
 * The result of the call is that `rank_dest` contains the group rank of the neighboring process in
 * the specified dimension and distance;
 * `rank_source` returns the rank of the process for which the calling process is the neighbor in the
 * specified dimension and distance.
 *
 * * positive value: request neighbors in upward direction;
 * * negative value: request neighbors in downward direction.
 *
 * @param direction Specifies the dimension for which the neighboring process should be determined.
 * @param disp Specifies the displacement desired.
 */
int MPI_Cart_shift(MPI_Comm comm, int direction, int disp,
                   int *rank_source, int *rank_dest);


/**
 * @brief A virtual topology can be partitioned into subgrids
 *
 * The subgrid selection is controlled by the array `remain_dims` which contains an entry for each
 * dimension of the original grid.
 *
 * Setting `remain_dims[i]=1` means that the ith dimension is kept in the subgrid;
 *
 * `remain_dims[i]=0` means that the ith dimension is dropped in the subgrid.
 *
 * If a dimension `i` does not exist in the subgrid, the size of dimension `i` defines the number
 * of subgrids that have been generated for this dimension.
 *
 * @param comm Is the communicator for which the virtual topology has been defined;
 * @param new_comm Denotes the new communicator for which the new topology as a subgrid of
 * the original grid is defined.
 */
int MPI_Cart_sub(MPI_Comm comm, const int remain_dims[], MPI_Comm *new_comm);

/**
 * @brief Number of dimensions of the virtual grid
 */
int MPI_Cartdim_get(MPI_Comm comm, int *ndims);

/**
 * @brief Cartesian coordinates of the calling process within the virtual grid associated with communicator comm
 *
 * Where `maxdims` is the number of dimensions of the virtual topology, and `dims`,
 * `periods`, and `coords` are arrays of size `maxdims`.
 *
 * The arrays `dims` and periods have the same meaning as for MPI_Cart_create().
 *
 * The array `coords` is used to return the coordinates.
 */
int MPI_Cart_get(MPI_Comm comm, int maxdims, int dims[],
                 int periods[], int coords[]);

// Thomas
/**
 * @brief Returns an elapsed time on the calling processor.
 *
 * <code>
 * start = MPI_Wtime();\n
 * // part to measure();\n
 * end = MPI_Wtime();\n
 * time = end - start;
 * </code>
 */
double MPI_Wtime(void);

/**
 * @brief Abortion of the execution of all processes of a communicator
 */
int MPI_Abort(MPI_Comm comm, int errorcode);

/**
 * @brief a new structure of type `MPI_Info` is created
 * 
 * Creates a new info object.
 */
int MPI_Info_create(MPI_Info *info);

/**
 * @brief Adds a key/value pair to info.
 * 
 * adds a new pair (`key`, `value`) to `info`, or overwrites an already existing pair by with the same content of key
 */
int MPI_Info_set(MPI_Info info, const char *key, const char *value);

/**
 * @brief Retrieves the value associated with a `key` in an info object.
 * 
 * searches in info for a pair with the provided `key` and writes in `value` the
 * respective value with a max. length of `valuelen`. Value of `flag` is set to
 * false if no matching pair was found, otherwise it is set to true
 */
int MPI_Info_get(MPI_Info info, const char *key, int valuelen,
                 char *value, int *flag);

/**
 * @brief Pair (`key`, `value`) can be removed by this function
 */
int MPI_Info_delete(MPI_Info info, const char *key);

/**
 * @brief Spawns a number of identical binaries.
 * 
 * New processes can be created in MPI-2 by this function
 */
int MPI_Comm_spawn(const char *command, char *argv[], int maxprocs, MPI_Info info,
                   int root, MPI_Comm comm, MPI_Comm *intercomm,
                   int array_of_errcodes[]);

/**
 * @brief Spawns multiple binaries, or the same binary with multiple sets of arguments.
 * 
 * Several different MPI programs with possibly different command line
 * arguments can be split off as new processes by this function
 */
int MPI_Comm_spawn_multiple(int count, char *array_of_commands[], char **array_of_argv[],
                            const int array_of_maxprocs[], const MPI_Info array_of_info[],
                            int root, MPI_Comm comm, MPI_Comm *intercomm,
                            int array_of_errcodes[]);

/**
 * @brief Global synchronization of a process group of a window
 * 
 * Suitable for regular applications with alternating
 * * global computation phases and
 * * global communication phases
 *
 * @see MPI_Win_create
 */
int MPI_Win_fence(int assert, MPI_Win win);

/**
 * @brief Starts an RMA access epoch for win
 * 
 * @see MPI_Win_create
 */
int MPI_Win_start(MPI_Group group, int assert, MPI_Win win);

/**
 * @brief Completes an RMA access epoch on win started by a call to MPI_Win_start
 * 
 * @see MPI_Win_create
 */
int MPI_Win_complete(MPI_Win win);

/**
 * @brief Starts an RMA exposure epoch for the local window associated with win
 * 
 * @see MPI_Win_create
 */
int MPI_Win_post(MPI_Group group, int assert, MPI_Win win);

/**
 * @brief Completes an RMA exposure epoch started by a call to MPI_Win_post on win
 * 
 * @see MPI_Win_create
 */
int MPI_Win_wait(MPI_Win win);

/**
 * @brief Attempts to complete an RMA exposure epoch; a nonblocking version of MPI_Win_wait
 * 
 * @see MPI_Win_create
 */
int MPI_Win_test(MPI_Win win, int *flag);

/**
 * @brief Setting a lock before accessing
 */
int MPI_Win_lock(int lock_type, int rank, int assert, MPI_Win win);

/**
 * @brief Releasing a lock after access
 * 
 * @see MPI_Win_create
 */
int MPI_Win_unlock(int rank, MPI_Win win);

/**
 * @brief Accumulation of data in the memory of another process
 * 
 * Combines the contents of the origin buffer with that of a target buffer.
 * 
 * @see MPI_Win_create
 */
int MPI_Accumulate(const void *origin_addr, int origin_count, MPI_Datatype origin_datatype,
                   int target_rank, MPI_Aint target_disp, int target_count,
                   MPI_Datatype target_datatype, MPI_Op op, MPI_Win win);

/**
 * @brief Reading a data block from the memory of another process
 * 
 * Copies data from the target memory to the origin.
 * 
 * @param origin_addr is the starting address of the receive buffer in the local memory of the calling process,
 * @param origin_count specifies the number of elements from type `origin_type`, transferred to the receiving buffer.
 * @param target_rank is the rank of the target process, i.e. the process to be read from
 * @param win is the window object
 * 
 * @see MPI_Win_create
 */
int MPI_Get(void *origin_addr, int origin_count,
            MPI_Datatype origin_datatype, int target_rank,
            MPI_Aint target_disp, int target_count,
            MPI_Datatype target_datatype, MPI_Win win);

/**
 * @brief Copies data from the origin memory to the target.
 * 
 * @see MPI_Win_create
 */
int MPI_Put(const void *origin_addr, int origin_count, MPI_Datatype origin_datatype,
            int target_rank, MPI_Aint target_disp, int target_count,
            MPI_Datatype target_datatype, MPI_Win win);

/**
 * @brief One-sided MPI call that returns a window object for RMA operations.
 * 
 * each process from the communicator comm has to execute that operation
 */
int MPI_Win_create(void *base, MPI_Aint size, int disp_unit, MPI_Info info, MPI_Comm comm, MPI_Win *win);

/**
 * @brief Frees the window object and returns a null handle.
 * 
 * All operations of a participating processes have to be finished
 */
int MPI_Win_free(MPI_Win *win);
// ende

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
    MPI_Scatterv();
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
    MPI_Comm_create();
    MPI_Comm_split();
    MPI_Cart_create();
    MPI_Dims_create();
    MPI_Cart_rank();
    MPI_Cart_coords();
    MPI_Cart_shift();
    MPI_Cart_sub();
    MPI_Cartdim_get();
    MPI_Cart_get();

    // Thomas
    MPI_Wtime();
    MPI_Abort();
    MPI_Info_create();
    MPI_Info_set();
    MPI_Info_get();
    MPI_Info_delete();
    MPI_Comm_spawn();
    MPI_Comm_spawn_multiple();
    MPI_Win_create();
    MPI_Win_free();
    MPI_Accumulate();
    MPI_Get();
    MPI_Put();
    MPI_Win_fence();
    MPI_Win_start();
    MPI_Win_complete();
    MPI_Win_post();
    MPI_Win_wait();
    MPI_Win_test();
    MPI_Win_lock();
    MPI_Win_unlock();




    // ende
}