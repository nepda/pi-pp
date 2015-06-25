#include <stdio.h>

#define nodeSize 18

struct Graph {
    int AdjMatrix[nodeSize][nodeSize];
};


void printGraph(int Graph[nodeSize][nodeSize])
{
    int i, j;
    for (i = 0; i < nodeSize; i++ ) {
        printf("> ");
        for (j = 0; j < nodeSize; j++ ) {
            printf("%d ", Graph[i][j]);
        }
        printf("<\n");
    }
}

void getCut(int P1[nodeSize/2], int P2[nodeSize/2], int Graph[nodeSize][nodeSize])
{
    int i,j;
    int countCut;
    for (i = 0; i < nodeSize/2; i++) {
        for (j = 0; j < nodeSize/2; j++) {
            //Kante von i nach j ?
            if (Graph[ P1[i] ][ P2[j] ]) countCut++;
        }
    }
    printf("\nCut of G is %d\n", countCut);
}

void getDegree(int Graph[nodeSize][nodeSize])
{
    int i, j;
    int maxDegree = 0;
    for (i = 0; i < nodeSize; i++ ) {
        int tmpDegree = 0;
        for (j = 0; j < nodeSize; j++ ) {
            if (Graph[i][j]) tmpDegree++;
        }
        if (tmpDegree>maxDegree) maxDegree=tmpDegree;
    }
    printf("\nDegree of G is %d\n", maxDegree);
}

int main(void)
{
    struct Graph graph;
    int i, j;
    for (i = 0; i < nodeSize; i++ ) {
        for (j = 0; j < nodeSize; j++ ) {
            graph.AdjMatrix[i][j] = 0;
        }
    }
    int E[68] = {1, 2, 1, 3, 1, 4, 1, 5, 2, 3, 2, 4, 2, 5, 3, 43, 6, 3, 10, 4, 6, 4, 11,
                 5, 7, 5, 8, 5, 9, 6, 7, 6, 8, 6, 9, 10, 11, 10, 12, 10, 13, 10, 14, 11, 12,
                 11, 13, 11, 14, 12, 13, 12, 15, 13, 15, 14, 16, 14, 17, 14, 18, 15, 16,
                 15, 17, 15, 18};

    for (i = 0; i < 68; i+=2) {
        graph.AdjMatrix[ E[i] ][ E[i+1] ] = 1;
    }

    printGraph(graph.AdjMatrix);
    getDegree(graph.AdjMatrix);

    int P1[nodeSize/2] = {1, 2, 3, 4, 14, 15, 16, 17, 18};
    int P2[nodeSize/2] = {5, 6, 7, 8, 9, 10, 11, 12, 13};

    getCut(P1, P2, graph.AdjMatrix);

    return 0;
}

