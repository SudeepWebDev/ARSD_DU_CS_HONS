# Notes: OpenMP Parallel for Loops and Private Variable Handling

---

## 1. Parallel for Loops in OpenMP

### 1.1 Why Use Parallel for Loops?
- Many inherently parallel operations in C are written as `for` loops.
- OpenMP allows easy parallelization of such loops using the `parallel for` directive.
- Example: Parallelizing a loop in the Sieve of Eratosthenes with no inter-iteration dependence.

### 1.2 Syntax: The `parallel for` Pragma

| Syntax Example              | Description                                  |
|-----------------------------|----------------------------------------------|
| `#pragma omp parallel for`  | Tells the compiler to execute the following for loop in parallel |

- Placed immediately before a `for` loop.
- The compiler handles thread creation, joining, and iteration scheduling.

### 1.3 Requirements for Parallelizing a Loop
- The loop's control clause must have a *canonical* shape (e.g., `for (i = start; i < end; i += inc)`).
- No statements that allow early exit (`break`, `return`, `exit`, `goto` to outside labels) in the loop body.
- `continue` is allowed.
- Compiler must determine the total number of iterations at runtime.

---

## 2. Execution Context and Variable Scope

### 2.1 Thread Execution Context
- Each thread has its own address space for:
  - Static variables
  - Heap-allocated data
  - Stack variables
- Variables can be:
  - **Shared**: Same address across threads, accessible by all.
  - **Private**: Unique address per thread, accessible only by the owning thread.
- **Default for `parallel for`:**
  - All variables are shared, except the loop index variable (which is private).

### 2.2 Controlling Number of Threads

| Method                           | Usage Example                 |
|-----------------------------------|------------------------------|
| Environment variable              | `OMP_NUM_THREADS`            |
| OpenMP function                   | `int omp_get_num_procs()`    |
| Set number of threads programmatically | `void omp_set_num_threads(int t)` |

---

## 3. Declaring Private Variables

### 3.1 The `private` Clause

- **Purpose:** Makes specified variables private to each thread in the parallel region.
- **Syntax:**  
  `private(variable_list)`
- **Behavior:**  
  - Each thread gets its own uninitialized copy.
  - Value is undefined on entry and exit of the parallel region.
- **Example:**
  ```c
  #pragma omp parallel for private(j)
  for (i = 0; i < BLOCK_SIZE; i++) {
      for (j = 0; j < n; j++)
          // work
  }
  ```

---

## 4. Other Private Variable Clauses

### 4.1 `firstprivate` Clause

- **Purpose:**  
  - Each thread's private variable is initialized to the value it had before entering the parallel region.
- **Syntax:**  
  `firstprivate(variable_list)`
- **Use Case:**  
  - When initialization outside the loop is expensive or needed within each thread.
- **Behavior:**  
  - Only one initialization per thread, not per iteration.
  - If a thread modifies the value, it persists across that thread's iterations.

### 4.2 `lastprivate` Clause

- **Purpose:**  
  - After the parallel loop, the master thread receives the value of the private variable from the *last* iteration (sequentially last).
- **Syntax:**  
  `lastprivate(variable_list)`
- **Use Case:**  
  - Need the value from the final iteration after the parallel loop ends.
- **Behavior:**  
  - Can be combined with `firstprivate` in the same pragma.
  - Variables can overlap, be distinct, or be partially overlapping between the two clauses.

---

## 5. Summary Table: Variable Scoping in OpenMP Parallel Loops

| Clause         | Initialization           | Value After Loop        | Scope    | Typical Use Case               |
|----------------|-------------------------|------------------------|----------|--------------------------------|
| private        | Undefined               | Undefined              | Per thread | Loop indices, inner temporaries |
| firstprivate   | Value before loop       | Last value per thread  | Per thread | Per-thread initialization      |
| lastprivate    | Undefined or firstprivate| Value from last iteration (to master) | Per thread/master | Capture last value after loop   |

---