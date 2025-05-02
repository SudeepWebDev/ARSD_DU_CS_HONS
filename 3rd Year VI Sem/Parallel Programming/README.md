# **UNIT 1: Introduction and Motivation**

## **1.1 Motivating Parallelism**

### **The Computational Power Argument – from Transistors to FLOPS**  
As technology advances, the number of transistors on chips grows (Moore's Law), enabling more computation per unit time (FLOPS: Floating Point Operations Per Second). But frequency scaling has stalled due to power and heat limits. Parallelism (multiple cores/processors) is now key to increasing computational power.

**Example:**  
- 1970s: CPUs had thousands of transistors, now billions.
- Modern GPUs/CPUs achieve TeraFLOPS (10¹² FLOPS) using parallel cores.

**Code Example:** (Parallel addition using OpenMP)
```c
#include <stdio.h>
#include <omp.h>
int main() {
    int n = 1000000;
    double sum = 0.0, a[n];
    for (int i = 0; i < n; i++) a[i] = i * 1.0;
    #pragma omp parallel for reduction(+:sum)
    for (int i = 0; i < n; i++) sum += a[i];
    printf("Sum = %f\n", sum);
    return 0;
}
```

---

### **The Memory/Disk Speed Argument**  
CPU speeds have increased much faster than memory/disk speeds (memory wall). This speed gap results in CPUs often waiting for data, underutilizing computational power. Parallel architectures can help mitigate this by overlapping computation and data access.

---

### **The Data Communication Argument**  
In distributed and parallel systems, data movement (communication) often becomes a bottleneck. Efficient parallel algorithms aim to minimize communication overhead.

---

## **1.2 Scope of Parallel Computing**

### **Applications in Engineering and Design**  
- Finite Element Analysis (FEA), Computational Fluid Dynamics (CFD), CAD.
- Example: Simulating airflow over wings concurrently at many points.

### **Scientific Applications**  
- Weather modeling, genomics, astrophysics simulations.
- Example: Running climate models on thousands of cores.

### **Commercial Applications**  
- Real-time analytics, financial modeling, databases.
- Example: Data mining large datasets using clusters.

### **Applications in Computer Systems**  
- Operating system scheduling, web servers, search engines.
- Example: Google search uses large-scale parallelism to index the web.

---

## **2.1 Implicit Parallelism: Trends in Microprocessor Architectures**

### **Pipelining and Superscalar Execution**  
- **Pipelining**: Overlaps instruction execution (like assembly lines).
- **Superscalar**: Multiple instructions issued per cycle.

**Example:**  
```asm
; Pipelined execution (conceptual, not real code)
LOAD R1, A
ADD R2, R1, R3
STORE R2, B
; Each instruction can be at a different pipeline stage simultaneously.
```

---

### **Very Long Instruction Word (VLIW) Processors**  
- Group multiple operations in a single wide instruction.
- Relies on compiler to find and schedule parallelism.

---

## **2.2 Limitations of Memory System Performance**

### **Improving Effective Memory Latency Using Caches**  
- **Caches**: Small, fast memory to hold frequently used data.
- Reduces average memory access time.

---

### **Impact of Memory Bandwidth**  
- Parallel systems need high bandwidth to avoid contention.
- Bandwidth limits can throttle performance.

---

### **Alternate Approaches for Hiding Memory Latency**  
- **Prefetching**: Load data before it’s needed.
- **Multithreading**: Switch to another thread while waiting for memory.

---

### **Tradeoffs of Multithreading and Prefetching**  
- **Multithreading**: Increases resource utilization, but adds complexity.
- **Prefetching**: Can waste bandwidth if predictions are wrong.

---

## **2.3 Dichotomy of Parallel Computing Platforms**

### **Control Structure of Parallel Platforms**  
- **Shared memory**: Multiple processors share a global address space.
- **Distributed memory**: Each processor has its own memory.

### **Communication Model of Parallel Platforms**  
- **Shared-memory**: Use of locks, semaphores, etc.
- **Message-passing**: Explicit send/receive (MPI).

---

## **2.4.1 Architecture of an Ideal Parallel Computer**  
- All processors equally access all memory and communicate instantly (theoretical).
- In practice, trade-offs exist due to hardware limitations.

---

# **UNIT 2: Shared Memory Parallel Programming**

## **7.1 Thread Basics**  
- **Threads**: Lightweight processes sharing memory space.
- Enable concurrent execution within a single process.

---

## **7.2 Why Threads?**  
- Efficient resource sharing, faster context switches.
- Used for multitasking, parallel computing.

---

## **7.10 OpenMP: a Standard for Directive Based Parallel Programming**

### **The OpenMP Programming Model**  
- Compiler directives to parallelize code in C/C++/Fortran.

**Example:**
```c
#pragma omp parallel for
for (int i = 0; i < n; i++) {
    a[i] = b[i] + c[i];
}
```

---

### **Specifying Concurrent Tasks in OpenMP**  
- `#pragma omp parallel sections` for task parallelism.

---

### **Synchronization Constructs in OpenMP**  
- `#pragma omp critical`, `#pragma omp barrier`, `#pragma omp atomic`.

---

### **Data Handling in OpenMP**  
- `shared`, `private` clauses control variable scope.
- **Reduction** clause for parallel accumulation.

---

### **OpenMP Library Functions**  
- `omp_get_thread_num()`, `omp_get_num_threads()`, etc.

---

### **Environment Variables in OpenMP**  
- `OMP_NUM_THREADS`, `OMP_SCHEDULE`, etc.

---

### **Explicit Threads versus OpenMP Based Programming**  
- **Explicit threads** (e.g., pthreads): Manual thread management.
- **OpenMP**: Higher-level, easier, less error-prone.

---

## **17 Shared Memory Programming**  
### **Introduction & Shared Memory Model**  
- All threads/processors access same address space.
- Requires synchronization to avoid race conditions.

### **PARALLEL for LOOPS**
- Parallelize loops via OpenMP or manual threads.

### **DECLARING PRIVATE VARIABLES**
```c
#pragma omp parallel for private(i)
for (int i = 0; i < n; i++) { /* ... */ }
```

### **CRITICAL SECTIONS**
```c
#pragma omp critical
{ /* only one thread at a time here */ }
```

### **Reductions**
```c
#pragma omp parallel for reduction(+:sum)
for (int i = 0; i < n; i++) sum += a[i];
```

### **PERFORMANCE IMPROVEMENTS**
- Minimize synchronization, maximize parallel work.

### **MORE GENERAL DATA PARALLELISM**
- Use `omp parallel for` for vector/matrix operations.

### **FUNCTIONAL PARALLELISM**
- Different threads do different tasks (sections).

---

# **UNIT 3: Message Passing and Distributed Memory**

## **2.4.3 Completely Connected Network, Linear Arrays, Meshes**  
- **Completely connected**: Each processor connects to every other.
- **Linear array**: Processors in a line.
- **Mesh**: Processors in 2D/3D grid.

---

## **6.1 Principles of Message-Passing Programming**
- Explicit data exchange between processes.
- No shared memory.

---

## **6.2 The Building Blocks: Send and Receive Operations**

### **Blocking Message Passing Operations**
- Sender/receiver waits until operation completes.

### **Non-Blocking Message Passing Operations**
- Initiate send/receive, then continue computation.

---

## **6.3 MPI: the Message Passing Interface**

### **Starting and Terminating the MPI Library**
```c
#include <mpi.h>
int main(int argc, char *argv[]) {
    MPI_Init(&argc, &argv);
    //...
    MPI_Finalize();
}
```

---

### **Communicators**
- Define groups of processes for communication (e.g., `MPI_COMM_WORLD`).

### **Getting Information**
```c
int rank, size;
MPI_Comm_rank(MPI_COMM_WORLD, &rank);
MPI_Comm_size(MPI_COMM_WORLD, &size);
```

---

### **Sending and Receiving Messages**
```c
MPI_Send(buffer, count, MPI_INT, dest, tag, MPI_COMM_WORLD);
MPI_Recv(buffer, count, MPI_INT, source, tag, MPI_COMM_WORLD, &status);
```

---

### **Example: Odd-Even Sort**  
See below in Unit 4.

---

## **6.5 Overlapping Communication with Computation**

### **Non-Blocking Communication Operations**
```c
MPI_Isend(...); MPI_Irecv(...); // Returns immediately
```

---

## **6.6 Collective Communication and Computation Operations**

### **Barrier**
```c
MPI_Barrier(MPI_COMM_WORLD);
```

### **Broadcast**
```c
MPI_Bcast(buffer, count, type, root, MPI_COMM_WORLD);
```

### **Reduction**
```c
MPI_Reduce(sendbuf, recvbuf, count, type, op, root, MPI_COMM_WORLD);
```

### **Prefix, Gather, Scatter, All-to-All**
- **Gather**: Many-to-one
- **Scatter**: One-to-many
- **All-to-All**: Each process sends to all others

---

#### **Example: One-Dimensional Matrix-Vector Multiplication**
```c
// Each process computes part of the result and then gathers results.
```

#### **Example: Single-Source Shortest-Path**
```c
// Parallel Dijkstra or Bellman-Ford using message passing.
```

---

# **UNIT 4: Parallel Algorithms and Case Studies**

## **6.3.5 Example: Odd-Even Sort (MPI)**
```c
// Odd-Even Transposition Sort with MPI (simplified)
for (int i = 0; i < n; i++) {
    if (i % 2 == 0) {
        // Even phase: even-ranked processes exchange with right neighbor
    } else {
        // Odd phase: odd-ranked processes exchange with right neighbor
    }
    // Exchange boundary elements using MPI_Send/MPI_Recv
}
```

---

## **6.6.9 Example: Single-Source Shortest-Path**
- Parallel BFS or Dijkstra using MPI (see below).

---

## **8.2 Matrix-Matrix Multiplication: A Simple Parallel Algorithm**
```c
// Parallel matrix multiplication using OpenMP
#pragma omp parallel for
for (int i = 0; i < N; i++)
    for (int j = 0; j < N; j++)
        for (int k = 0; k < N; k++)
            C[i][j] += A[i][k] * B[k][j];
```

---

## **A Naïve Breadth First Search Approach Incorporating Parallel Processing Technique For Optimal Network Traversal**

### **BREADTH FIRST-SEARCH**
```c
void BFS(int start) {
    queue<int> q;
    q.push(start);
    visited[start] = true;
    while (!q.empty()) {
        int u = q.front(); q.pop();
        for (int v : adj[u]) {
            if (!visited[v]) {
                visited[v] = true;
                q.push(v);
            }
        }
    }
}
```

---

### **PARALLEL BREADTH FIRST-SEARCH**
- Use parallelism for processing current frontier.
- OpenMP or MPI can be used for parallelizing.

---

### **OPENMP (Parallel BFS Example)**
```c
#pragma omp parallel for
for (int i = 0; i < frontier_size; i++) {
    int u = frontier[i];
    for (int v : adj[u]) {
        if (!visited[v]) {
            visited[v] = true;
            next_frontier.push_back(v);
        }
    }
}
```

---

### **WHY PARALLEL BFS?**
- BFS is communication-intensive but can be parallelized by processing all nodes at a level concurrently.
- Used in graph analytics, network analysis, shortest-path algorithms.

---

# **References**
1. [Book/Notes/Slides on Parallel Computing Principles]
2. [OpenMP Documentation](https://www.openmp.org/)
3. [Research papers on parallel BFS]
4. [Lecture slides by Yogish Sabharwal](https://sites.google.com/view/yogishsabharwal/moocs?authuser=0)

---

