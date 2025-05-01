# OpenMP: Critical Sections and Reductions

---

## 1. Critical Sections

### 1.1 Motivation

- Not all loops are "embarrassingly parallel".
- Example: Numerical integration using the rectangle rule involves updating a shared variable (`area`) in every iteration.
- If parallelized naively, multiple threads may update `area` simultaneously, causing a **race condition** and incorrect results.

| Term             | Description                                                                 |
|------------------|-----------------------------------------------------------------------------|
| Race Condition   | Program exhibits unpredictable behavior due to concurrent, unsynchronized access to shared data. |
| Critical Section | Code block that only one thread may execute at a time to avoid data races.  |

### 1.2 The `critical` Pragma

- Used to enforce **mutual exclusion** so only one thread can execute a block at a time.
- **Syntax:**

  ```c
  #pragma omp critical
  // code block
  ```

- **Example:**

  ```c
  #pragma omp parallel for private(x)
  for (i = 0; i < n; i++) {
      x = (i+0.5)/n;
      #pragma omp critical
      area += 4.0/(1.0 + x*x);
  }
  pi = area / n;
  ```

- **Downside:**  
  - Only one thread at a time can update `area`, introducing a sequential bottleneck.
  - By Amdahl's Law, this limits the achievable speedup from parallelization.

---

## 2. Reductions

### 2.1 Motivation and Usage

- Many parallel programs need to **accumulate** results (e.g., sum, product, min, max) from all threads.
- OpenMP provides a `reduction` clause to handle this efficiently and avoid critical sections.

### 2.2 The `reduction` Clause

| Syntax Example                           | Description                                 |
|-------------------------------------------|---------------------------------------------|
| `reduction(op: variable)`                 | `op` is the reduction operation, `variable` is the shared variable being reduced. |

- OpenMP creates **private copies** of the variable for each thread, combines them at the end.

- **Example with Sum:**

  ```c
  #pragma omp parallel for private(x) reduction(+:area)
  for (i = 0; i < n; i++) {
      x = (i+0.5)/n;
      area += 4.0/(1.0 + x*x);
  }
  pi = area / n;
  ```

### 2.3 Supported Reduction Operators (OpenMP, C/C++)

| Operator | Meaning             | Types          | Initial Value |
|----------|---------------------|---------------|--------------|
|   +      | Sum                 | float, int    | 0            |
|   *      | Product             | float, int    | 1            |
|   &      | Bitwise AND         | int           | all bits 1   |
|   |      | Bitwise OR          | int           | 0            |
|   ^      | Bitwise XOR         | int           | 0            |
|   &&     | Logical AND         | int           | 1            |
|   \|\|   | Logical OR          | int           | 0            |

---

## 3. Performance Comparison

### 3.1 Execution Time Example (Rectangle Rule for π, n = 100,000)

| Threads | Using `critical` (sec) | Using `reduction` (sec) |
|---------|------------------------|-------------------------|
| 1       | 0.0780                 | 0.0273                  |
| 2       | 0.1510                 | 0.0146                  |
| 3       | 0.3400                 | 0.0105                  |
| 4       | 0.3608                 | 0.0086                  |
| 5       | 0.4710                 | 0.0076                  |

- **Observation:**  
  - The `reduction` clause provides much better scaling and performance than using `critical` sections for accumulation.

---

## 4. Summary Table: OpenMP Techniques for Shared Updates

| Technique      | Correctness | Parallelism | Performance   | Use Case                        |
|----------------|-------------|-------------|---------------|----------------------------------|
| critical       | Yes         | Poor        | Bottleneck    | Any update needing mutual exclusion |
| reduction      | Yes         | Excellent   | High          | Accumulation (sum, product, etc.) |

---
