# Shared-Memory Programming (OpenMP): Key Notes

---

## 1. Introduction to Shared-Memory Programming

- **Historical Context**:
  - 1980s: Commercial multiprocessors (few CPUs) were very expensive.
  - Present: Small multiprocessor systems (2-4 CPUs) are affordable.
- **Programming Approaches**:
  - Parallel programming for multiprocessors can use MPI, but **shared-memory programming** (e.g., OpenMP) is often more efficient for such architectures.
- **OpenMP Overview**:
  - OpenMP: An API for parallel programming on multiprocessors.
  - Consists of compiler directives + support library functions.
  - Supported in Fortran, C, C++.
  - Suited for single multiprocessors as well as clusters of multi-CPU nodes.

---

## 2. Major OpenMP Directives and Functions

| Directive/Function      | Purpose                                                                                 |
|-------------------------|-----------------------------------------------------------------------------------------|
| `parallel`              | Marks a block to be executed in parallel by multiple threads                            |
| `for`                   | Precedes a loop whose iterations are distributed among threads                          |
| `parallel for`          | Combines `parallel` and `for`                                                           |
| `sections`              | Precedes blocks to be executed in parallel                                              |
| `parallel sections`     | Combines `parallel` and `sections`                                                      |
| `critical`              | Precedes a critical section (mutual exclusion)                                          |
| `single`                | Marks a block to be executed by a single thread                                         |
| `omp_get_num_procs`     | Returns number of CPUs in the system                                                    |
| `omp_get_num_threads`   | Returns number of threads active in the current parallel region                         |
| `omp_get_thread_num`    | Returns the thread ID of the calling thread                                             |
| `omp_set_num_threads`   | Sets the number of threads for parallel execution                                       |

---

## 3. The Shared-Memory Model

### 3.1 Model Characteristics

- **Hardware Abstraction**:
  - Multiple processors share access to a common memory space.
  - Synchronization and communication occur via shared variables.

- **Fork/Join Parallelism**:
  - Program starts with a single (master) thread.
  - At parallel regions, master thread *forks* new threads to execute code in parallel.
  - At the end of the parallel region, threads *join* and control returns to the master thread.

| Step               | Description                                                   |
|--------------------|---------------------------------------------------------------|
| Start              | Only master thread active                                     |
| Fork               | Master creates/awakens additional threads for parallel work   |
| Parallel Execution | Threads execute concurrently                                  |
| Join               | Extra threads terminate/suspend, control returns to master    |

- **Contrast with Message Passing Model**:
  - Shared-memory: Number of active threads changes dynamically (1 at start/end, more during parallel regions).
  - Message-passing: All processes are active throughout program execution.

---

## 4. Incremental Parallelization

- **Definition**: Transforming a sequential program to parallel by parallelizing one code block at a time.
- **Advantages**:
  - Profile the program, identify the most time-consuming blocks.
  - Parallelize blocks incrementally, starting with those that offer the most benefit.
  - Stop when further parallelization isn't justified by performance gains.
- **Contrast**:
  - Shared-memory model: Supports incremental parallelization.
  - Message-passing model: Requires a complete rewrite; no incremental path.

---

## 5. Fork/Join Diagram

- **Fork/Join Model**:
  - At program start: Only the master thread is active.
  - Parallel section: Master forks additional threads.
  - Serial section: Threads join, only master continues.

---

## 6. Summary Table: Shared-Memory vs. Message-Passing

| Aspect                | Shared-Memory Model (OpenMP)        | Message-Passing Model (MPI)         |
|-----------------------|-------------------------------------|-------------------------------------|
| Parallelism Pattern   | Fork/Join, dynamic thread counts    | All processes active throughout     |
| Data Access           | Shared variables in common memory   | Explicit messages, no shared memory |
| Incremental Parallel  | Supported                           | Not supported                       |
| Ease of Transformation| Incremental, gradual                | Requires total rewrite              |

---