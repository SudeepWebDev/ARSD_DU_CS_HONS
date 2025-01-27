#include <stdio.h>
#include <stdlib.h>
#include <omp.h>

void histogramSort(int *data, int size) {
    int max_val = data[0];
    for (int i = 1; i < size; i++) {
        if (data[i] > max_val) {
            max_val = data[i];
        }
    }

    int *histogram = (int *)calloc(max_val + 1, sizeof(int));

    #pragma omp parallel for
    for (int i = 0; i < size; i++) {
        #pragma omp atomic
        histogram[data[i]]++;
    }

    int index = 0;
    for (int i = 0; i <= max_val; i++) {
        while (histogram[i] > 0) {
            data[index++] = i;
            histogram[i]--;
        }
    }

    free(histogram);
}

int main() {
    int data[] = {5, 3, 8, 6, 2, 7, 4, 1, 0, 9};
    int size = sizeof(data) / sizeof(data[0]);

    histogramSort(data, size);

    // Print sorted data or validate the result
    for (int i = 0; i < size; i++) {
        printf("%d ", data[i]);
    }
    printf("\n");

    return 0;
}
