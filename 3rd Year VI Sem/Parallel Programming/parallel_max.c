#include <stdio.h>
#include <omp.h>

int parallelMax(int *data, int size) {
    int max_val = data[0];

    #pragma omp parallel for reduction(max:max_val)
    for (int i = 1; i < size; i++) {
        if (data[i] > max_val) {
            max_val = data[i];
        }
    }

    return max_val;
}

int main() {
    int data[] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
    int size = sizeof(data) / sizeof(data[0]);

    int max_val = parallelMax(data, size);

    printf("Max: %d\n", max_val);

    return 0;
}
