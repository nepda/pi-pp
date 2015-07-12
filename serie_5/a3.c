#include <stdio.h>
#include "mpi.h"

int main(int argc, char argv[]) {

    /*
     * C_1 = {4,3,2,1,0}
     * G_1 = {4,3,2,1,0}
     *
     * ranks_group_incl = {0,2}
     *
     * G_2 = {4,2} // 0ten und 2ten aus Gruppe 1 aus ranks_group_incl
     * G_3 = G_1 \ G_2 = {3,1,0} // Raenge in COMM_WORLD
     * G_4 = G_2 UNION G_3 = {4,2,3,1,0}
     *
     * C_2 = {4,2,3,1,0}
     */

}
