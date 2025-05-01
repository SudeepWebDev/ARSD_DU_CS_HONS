# OpenMP: Specifying Concurrent Tasks

## 1. Directives for Concurrency

| Directive | Purpose                                                                              |
|-----------|--------------------------------------------------------------------------------------|
| `for`     | Splits loop iterations across threads (parallel iteration spaces)                    |
| `sections`| Assigns independent tasks to threads (parallel tasks, not based on iteration)        |

---

## 2. The `for` Directive

- **General Syntax:**

  ```c
  #pragma omp for [clause list]
      /* for loop */
  ```

- **Common Clauses:**  
  `private`, `firstprivate`, `lastprivate`, `reduction`, `schedule`, `nowait`, `ordered`

### 2.1. Data Handling Clauses

| Clause         | Purpose                                                               |
|----------------|-----------------------------------------------------------------------|
| private        | Each thread has its own uninitialized copy of listed variables        |
| firstprivate   | Each thread has its own copy, initialized to pre-parallel value       |
| lastprivate    | Value from last (serial order) iteration is copied back after loop    |
| reduction      | Combines local copies into a single result using a specified operator |

### 2.2. Parallelizing Loops Example

```c
#pragma omp parallel default(private) shared(npoints) reduction(+: sum) num_threads(8)
{
    sum = 0;
    #pragma omp for
    for (i = 0; i < npoints; i++) {
        // loop body
    }
}
```

- The loop is automatically split among threads.
- Loop index is private by default.
- Conversion from serial to parallel is often as simple as adding two directives.

---

## 3. Scheduling of Iterations

| Scheduling Class  | Syntax Example                | Description                                                                                                         |
|-------------------|------------------------------|---------------------------------------------------------------------------------------------------------------------|
| static            | schedule(static[, chunk])    | Evenly divides iterations in chunks, round-robin assignment                                                         |
| dynamic           | schedule(dynamic[, chunk])   | Chunks assigned as threads become idle (good for uneven workloads)                                                  |
| guided            | schedule(guided[, chunk])    | Chunk size decreases exponentially, minimizing idle time (good for "edge effect" in large jobs)                     |
| runtime           | schedule(runtime)            | Scheduling type and chunk size set by `OMP_SCHEDULE` environment variable, allowing runtime tuning                  |

- **Default:** If no scheduling specified, implementation decides.
- **Loop Restrictions:**  
  No `break` statement, control variable must be integer, standard increment/decrement logic.

---

## 4. Synchronization and `nowait` Clause

- **Default:** Implicit barrier at the end of each `for` or `sections` directive.
- **`nowait` clause:** Removes this barrier, allowing threads to proceed without waiting.
  
**Example:**

```c
#pragma omp parallel
{
    #pragma omp for nowait
    for (i = 0; i < nmax; i++)
        // process current list

    #pragma omp for
    for (i = 0; i < mmax; i++)
        // process past list
}
```

- Threads don't wait for all to finish the first loop before starting the second.

---

## 5. The `sections` Directive

- **Purpose:** Assign independent tasks (not loops) to threads.
- **Syntax:**

  ```c
  #pragma omp sections [clause list]
  {
      #pragma omp section
      { /* Task A */ }
      #pragma omp section
      { /* Task B */ }
      // ...
  }
  ```

- **Clauses:**  
  `private`, `firstprivate`, `lastprivate`, `reduction`, `nowait`
- **Behavior:** Each section typically assigned to a different thread.
- **No branching** in/out of section blocks allowed.

---

## 6. Merging Directives

- `parallel for` and `parallel sections` are syntactic shortcuts.
- **Equivalent forms:**

| Expanded Form                                              | Merged Form                                  |
|------------------------------------------------------------|-----------------------------------------------|
| #pragma omp parallel ...<br> #pragma omp for ...           | #pragma omp parallel for ...                  |
| #pragma omp parallel ...<br> #pragma omp sections ...      | #pragma omp parallel sections ...             |

---

## 7. Nested Parallelism

- **Nesting:** Allowed by writing multiple `parallel for` directives inside each other.
- **Example:** Nested parallelism in matrix multiplication

  ```c
  #pragma omp parallel for ...
  for (i = ...) {
      #pragma omp parallel for ...
      for (j = ...) {
          #pragma omp parallel for ...
          for (k = ...) {
              // computation
          }
      }
  }
  ```

- **By default:**  
  Nested parallelism is **disabled** (`OMP_NESTED = FALSE`), so inner parallel regions are serialized.
- **To enable:**  
  Set environment variable `OMP_NESTED = TRUE`.
- **Restrictions:**  
  Synchronization constructs (barriers, etc.) have limitations in nested regions (consult OpenMP manual).

---

## 8. Summary Table: Directives and Clauses

| Directive         | For Iterations | For Tasks | Data Handling Clauses           | Scheduling | `nowait` | Merging Allowed | Nested Parallelism |
|-------------------|---------------|-----------|-------------------------|------------|----------|----------------|-------------------|
| `for`             | Yes           | No        | Yes                     | Yes        | Yes      | Yes            | Yes               |
| `sections`        | No            | Yes       | Yes                     | No         | Yes      | Yes            | Yes               |
| `parallel`        | Yes           | Yes       | Yes                     | No         | No       | Yes            | Yes               |
