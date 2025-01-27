#include <iostream>
#include <omp.h>
#include <vector>
#include <algorithm>

void histogramSort(std::vector<int>& data) {
    int max_val = *std::max_element(data.begin(), data.end());
    std::vector<int> histogram(max_val + 1, 0);

    #pragma omp parallel for
    for (int i = 0; i < data.size(); i++) {
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
}

int main() {
    std::vector<int> data = {5, 3, 8, 6, 2, 7, 4, 1, 0, 9};

    histogramSort(data);

    // Print sorted data or validate the result
    for (int i = 0; i < data.size(); i++) {
        std::cout << data[i] << " ";
    }
    std::cout << std::endl;

    return 0;
}
