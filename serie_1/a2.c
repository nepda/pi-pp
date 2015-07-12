#include <stdio.h>
#include <stdlib.h>
#include <omp.h>

#define N 1000

int fibonacci(int i) {
    if (i < 2) {
        return i;
    } else {
        int a, b;
// #pragma omp parallel sections shared(a,b)
        {
// #pragma omp section nowait
#pragma omp task shared(a) firstprivate(i)
            a = fibonacci(i - 2);
// #pragma omp section nowait
#pragma omp task shared(b) firstprivate(i)
            b = fibonacci(i - 1);
        }

#pragma omp taskwait
        return a + b;
    }
}

int main(int argc, char **argv) {


    if (argc < 2){
        printf("Test");
        return 1;
    }
    int x = atoi(argv[1]);

#pragma omp parallel shared(x)
    {

        int num = omp_get_num_threads();

        int a = fibonacci(x);

#pragma omp master
        printf("fib %i %i (%i)", x, a, num);
    }


    return 0;
}