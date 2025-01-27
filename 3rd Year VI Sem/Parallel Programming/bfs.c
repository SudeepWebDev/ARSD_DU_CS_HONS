#include <stdio.h>
#include <stdlib.h>
#include <omp.h>

#define MAX_QUEUE_SIZE 1000

typedef struct {
    int *data;
    int front;
    int rear;
    int size;
} Queue;

void initQueue(Queue *q, int size) {
    q->data = (int *)malloc(size * sizeof(int));
    q->front = 0;
    q->rear = 0;
    q->size = size;
}

int isEmpty(Queue *q) {
    return q->front == q->rear;
}

void enqueue(Queue *q, int value) {
    q->data[q->rear++] = value;
}

int dequeue(Queue *q) {
    return q->data[q->front++];
}

void freeQueue(Queue *q) {
    free(q->data);
}

void parallelBFS(int **graph, int numNodes, int start) {
    int *visited = (int *)calloc(numNodes, sizeof(int));
    Queue q;
    initQueue(&q, MAX_QUEUE_SIZE);

    visited[start] = 1;
    enqueue(&q, start);

    while (!isEmpty(&q)) {
        int node = dequeue(&q);

        #pragma omp parallel for
        for (int i = 0; i < numNodes; i++) {
            if (graph[node][i] && !visited[i]) {
                visited[i] = 1;
                #pragma omp critical
                enqueue(&q, i);
            }
        }
    }

    // Print visited nodes or validate the result
    for (int i = 0; i < numNodes; i++) {
        if (visited[i]) {
            printf("Node %d was visited.\n", i);
        }
    }

    free(visited);
    freeQueue(&q);
}

int main() {
    int numNodes = 6;
    int **graph = (int **)malloc(numNodes * sizeof(int *));
    for (int i = 0; i < numNodes; i++) {
        graph[i] = (int *)calloc(numNodes, sizeof(int));
    }

    // Define the graph edges
    graph[0][1] = 1; graph[0][2] = 1;
    graph[1][0] = 1; graph[1][3] = 1; graph[1][4] = 1;
    graph[2][0] = 1; graph[2][4] = 1;
    graph[3][1] = 1; graph[3][5] = 1;
    graph[4][1] = 1; graph[4][2] = 1; graph[4][5] = 1;
    graph[5][3] = 1; graph[5][4] = 1;

    parallelBFS(graph, numNodes, 0);

    for (int i = 0; i < numNodes; i++) {
        free(graph[i]);
    }
    free(graph);

    return 0;
}
