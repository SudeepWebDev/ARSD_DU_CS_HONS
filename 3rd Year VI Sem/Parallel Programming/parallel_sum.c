#include <stdio.h>
#include <omp.h>

int parallelSum(int *data, int size) {
    int sum = 0;

    #pragma omp parallel for reduction(+:sum)
    for (int i = 0; i < size; i++) {
        sum += data[i];
    }

    return sum;
}

int main() {
    int data[] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
    int size = sizeof(data) / sizeof(data[0]);

    int sum = parallelSum(data, size);

    printf("Sum: %d\n", sum);

    return 0;
}
